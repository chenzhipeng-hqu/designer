/**
 ******************************************************************************
 * @file    xxx.c
 * @author  chenzhipeng
 * @version V1.0.0
 * @date    29-Jun-2019
 * @brief
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */

/** @addtogroup Project
  * @{
  */

/***********************************************
                    include
***********************************************/
#include <bsp.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "core/list.h"
#include "core/kfifo.h"
#include "core/heap.h"
#include "core/init.h"
#include "core/device.h"
#include "core/softtimer.h"
#include "component/vast_cli.h"
//#include "component/vast_log.h"
#include "core/croutine.h"

/***********************************************
                    define
***********************************************/
#define		USE_KFIFO				1
#define		USE_VAST_UART			1
#define		USE_LL_UART				1
//#define		KFIFO_BUFFER_SIZE		(128U)

/***********************************************
                    typedef
***********************************************/
typedef struct _msg_t
{
	list_t		entry;
	data_t		data;
}msg_t;


/***********************************************
               function prototypes
***********************************************/

/***********************************************
                   variable
***********************************************/
#if USE_VAST_UART == 1
	device_t *uart_dev = NULL;
#else
	#if	USE_LL_UART == 1

	#else
		extern DMA_HandleTypeDef hdma_usart1_rx;
		extern DMA_HandleTypeDef hdma_usart1_tx;
		extern UART_HandleTypeDef huart1;
	#endif
#endif

static LIST_HEAD(uart_tx_list);

static CLI_HandleTypeDef	hcli;

#if (USE_KFIFO == 1)
	static DECLARE_KFIFO(cli_rx_fifo, uint8_t, KFIFO_RX_BUFFER_SIZE);
#endif

/***********************************************
                   function
***********************************************/
/**
  * @brief  postToDebugLog.
  * @param
  * @retval
  */
char SendBuf[256] = {0};

#if	USE_VAST_UART == 1
#else
static uint8_t tx_buff[128] = {0};
#endif

size_t postToVPrint(const char *format, va_list arg)
{
	char inv = 0;
	int len = 0;

	len = vsnprintf(SendBuf, sizeof(SendBuf), format, arg);
#if	USE_VAST_UART == 1
	device_write(uart_dev, 0, SendBuf, len);
#else
	if((list_empty(&uart_tx_list))
		#if USE_LL_UART == 1
			& (LL_USART_IsActiveFlag_TXE(USART1))) {
		#else
			& (huart1.gState == HAL_UART_STATE_READY)) {
		#endif

		memcpy(tx_buff, SendBuf, len);

		#if USE_LL_UART == 1
			LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_7, (uint32_t)tx_buff);
			LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_7, len);
			LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_7);
		#else
			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)tx_buff, len);
		#endif
	} else {
		while(1) {
			msg_t *pMsgPush = NULL;
			pMsgPush = (msg_t *)vast_malloc(sizeof(msg_t)+len);

			if(pMsgPush != NULL) {
				pMsgPush->data.len = len;
				memcpy(pMsgPush->data.buf, SendBuf, pMsgPush->data.len);
				list_add(&(pMsgPush->entry), &uart_tx_list);
				break;
			} else if (inv == 0) {
				inv = 1;
			#if USE_LL_UART == 1
				NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
			#else
				HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
			#endif
			} else {
				if((!list_empty(&uart_tx_list))
					#if USE_LL_UART == 1
						& (LL_USART_IsActiveFlag_TXE(USART1))) {
					#else
						& (huart1.gState == HAL_UART_STATE_READY)) {
					#endif

					msg_t *pMsgPop = NULL;
					pMsgPop = list_last_entry(&uart_tx_list, msg_t, entry);
					memcpy(tx_buff, pMsgPop->data.buf, pMsgPop->data.len);

					#if USE_LL_UART == 1
						LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_7, (uint32_t)tx_buff);
						LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_7, pMsgPop->data.len);
						LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_7);
					#else
						HAL_UART_Transmit_DMA(&huart1, (uint8_t *)tx_buff, pMsgPop->data.len);
					#endif
					list_del(&pMsgPop->entry);
					vast_free(pMsgPop);
				}
			}
		}
	}
#endif

	if(inv) {
	#if USE_LL_UART == 1
		NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));
	#else
		HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 5, 0);
	#endif
	}
	return len;
}

int16_t __attribute__((format(printf, 1, 2))) postToLog(const char *format, ... )
{
	va_list arg;
	int len = 0;

	va_start(arg, format);
//	len = vsnprintf(SendBuf, sizeof(SendBuf), format, arg);
	len = postToVPrint(format, arg);
	va_end(arg);

	return len;
}


/**
  * @brief  CliProcess_uart1.
  * @param
  * @retval
  */
static uint8_t CliProcess_uart1 (CLI_HandleTypeDef *pCli, CLI_SEL_FUNCx selFunc)
{
	uint8_t ret = 0;

	switch(selFunc)
	{
		case CLI_FUNC_INIT :
		{
		#if USE_VAST_UART == 1
			uart_dev = device_find("uart1");
			//device_open(uart_dev, DEVICE_FLAG_INT_RX | DEVICE_FLAG_INT_TX | DEVICE_FLAG_FASYNC);
			device_open(uart_dev, DEVICE_FLAG_DMA_RX | DEVICE_FLAG_DMA_TX | DEVICE_FLAG_FASYNC);
		#else
            #if (USE_KFIFO == 1)
                INIT_KFIFO(cli_rx_fifo);
                //kfifo_dma_in_prepare(&cli_rx_fifo, cli_rx_fifo.kfifo.esize - data);
                #if USE_LL_UART == 1
                    LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_7, LL_USART_DMA_GetRegAddr(USART1));

                    /* (5) Enable DMA transfer complete/error interrupts  */
                    LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_7);
                    LL_DMA_EnableIT_TE(DMA2, LL_DMA_STREAM_7);

                    /* Enable DMA TX Interrupt */
                    LL_USART_EnableDMAReq_TX(USART1);

                    LL_USART_EnableIT_IDLE(USART1);

                    /* Enable DMA RX Interrupt */
                    LL_USART_EnableDMAReq_RX(USART1);

                    LL_DMA_ConfigAddresses(DMA2, LL_DMA_STREAM_2,
                                                LL_USART_DMA_GetRegAddr(USART1),
                                                (uint32_t)cli_rx_fifo.buf,
                                                LL_DMA_GetDataTransferDirection(DMA2, LL_DMA_STREAM_2));

                    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_2, kfifo_size(&cli_rx_fifo));

                    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);
                #else
                    HAL_UART_Receive_DMA(&huart1, (uint8_t *)cli_rx_fifo.buf, kfifo_size(&cli_rx_fifo));
                #endif
            #endif
		#endif
			break;
		}
		case CLI_FUNC_TX_POP :
		{
		#if	USE_VAST_UART == 1

		#else
			if((!list_empty(&uart_tx_list))
			#if USE_LL_UART == 1
				& (LL_USART_IsActiveFlag_TXE(USART1))) {
			#else
				& (huart1.gState == HAL_UART_STATE_READY)) {
			#endif
				msg_t *pMsgPop = NULL;
				pMsgPop = list_last_entry(&uart_tx_list, msg_t, entry);
				memcpy(tx_buff, pMsgPop->data.buf, pMsgPop->data.len);
			#if USE_LL_UART == 1
				LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_7, (uint32_t)tx_buff);
				LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_7, pMsgPop->data.len);
				LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_7);
			#else
				HAL_UART_Transmit_DMA(&huart1, (uint8_t *)tx_buff, pMsgPop->data.len);
			#endif
				list_del(&pMsgPop->entry);
				vast_free(pMsgPop);
			}

		#endif
			break;
		}
		case CLI_FUNC_RX_PUSH :
		{
			break;
		}
		case CLI_FUNC_RX_POP :
		{
		#if USE_VAST_UART == 1
			device_read(uart_dev, 0, &ret, 1);
		#else
		#if (USE_KFIFO == 1)
			if(!kfifo_is_empty(&cli_rx_fifo))
			{
				kfifo_out(&cli_rx_fifo, &ret, 1);
				//kfifo_get(&cli_rx_fifo, &ret);
			}
		#endif

//			extern void shell_get_chr(char ch);
//			if (ret != 0) {
//				shell_get_chr(ret);
//				ret = 0;
//			}
		#endif

			break;
		}
		default:
		{
			//printf("%s %d, err cli func!\r\n", __FUNCTION__, __LINE__);
			break;
		}
	}

	return ret;
}

/**
  * @brief  cli_tmr_cb.
  * @param
  * @retval
  */
static void cli_tmr_cb(struct soft_timer * st)
{
    st->expires = jiffies + pdMS_TO_TICKS(10);
    soft_timer_add(st);

    CLI_Handle(&hcli);
}

static struct soft_timer cli_tmr =
{
    .expires = (INITIAL_JIFFIES) + pdMS_TO_TICKS(1000),
    .cb = cli_tmr_cb,
};

//static void shell_task_cb(struct task_ctrl_blk *tcb, ubase_t data)
//{
	//tSTART(tcb);

	//for(;;) {
		//CLI_Handle((CLI_HandleTypeDef*)data);
		//task_delay(tcb, 10);
	//}
	//tEND();
//}

/**
  * @brief  vast_cli_bspInit
  * @param
  * @retval
  */
static int vast_cli_bspInit(void)
{

	hcli.Init.Write = postToLog;
	hcli.pCLIProcess = CliProcess_uart1;
	CLI_Initialize(&hcli);

    soft_timer_add(&cli_tmr);

    //static tcb_t shell_tcb;
    //task_create(&shell_tcb, shell_task_cb, (ubase_t)&hcli);

	return 0;
}

arch_initcall(vast_cli_bspInit);

/**
  * @brief  vast_cli_bspRev
  * @param
  * @retval
  */
void vast_cli_bspRev(volatile uint8_t data)
{
	static volatile uint32_t old_cnt = KFIFO_RX_BUFFER_SIZE;
#if (USE_KFIFO == 1)
//	kfifo_dma_in_finish(&cli_rx_fifo, cli_rx_fifo.kfifo.esize - data);
	if(old_cnt < data)
	{
		old_cnt += cli_rx_fifo.kfifo.mask + 1;
	}
//	cli_rx_fifo.kfifo.in += (old_cnt - data);
	kfifo_add_in(&cli_rx_fifo, old_cnt - data);
	old_cnt = data;
#endif
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
#if	USE_VAST_UART == 1

#elif USE_LL_UART == 1

#else
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_RxCpltCallback could be implemented in the user file
   */
#if (USE_KFIFO == 1)
//	kfifo_dma_in_finish(&cli_rx_fifo, cli_rx_fifo.kfifo.esize - data);
//	cli_rx_fifo.kfifo.in += cli_rx_fifo.kfifo.mask;
#endif
}
#endif

/**
  * @brief  vast_cli_bspRev
  * @param
  * @retval
  */
void vast_cli_handle(void)
{
	CLI_Handle(&hcli);
}
#if	USE_VAST_UART == 1

#else
/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
#if USE_LL_UART == 1
	if(LL_USART_IsActiveFlag_IDLE(USART1))
	{
		LL_USART_ClearFlag_IDLE(USART1);
		vast_cli_bspRev((uint8_t)LL_DMA_GetDataLength(DMA2, LL_DMA_STREAM_2));
	}
#else
	if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE)!= RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		vast_cli_bspRev((uint8_t)__HAL_DMA_GET_COUNTER(huart1.hdmarx));
	}
  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
	#endif

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */
#if USE_LL_UART == 1

#else
  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */
#endif
  /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

#if USE_LL_UART == 1
    if(LL_DMA_IsActiveFlag_TC7(DMA2))
    {
        LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_7);
        //LL_DMA_ClearFlag_GI7(uart2.tx_dma.DMAx);
        LL_DMA_ClearFlag_TC7(DMA2);

        /* Call function Transmission complete Callback */
    }
    else if(LL_DMA_IsActiveFlag_TE7(DMA2))
    {
        LL_DMA_ClearFlag_TE7(DMA2);
        /* Call Error function */
        //USART_TransferError_Callback();
    }
#else
  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */
#endif
  /* USER CODE END DMA2_Stream7_IRQn 1 */
}
#endif

/**
  * @}
  */

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/



