/**
  ******************************************************************************
  * @file    CLI_Command.c
  * @author  chenzhipeng
  * @version V1.0.0
  * @date    23-July-2018
  * @brief   UsartTask
  ******************************************************************************
  * @attention
	*  CLI: command-line interface
  ******************************************************************************
  */
	
/** @addtogroup Template_Project
  * @{
  */ 
/*************************************
              include
*************************************/
#include <bsp.h>
#include <string.h>
#include <stdint.h>
#include "component/vast_cli.h"
#include "gpio.h"
#include <device/vast_ir.h>
#include <string.h>
#include "core/device.h"
#include "qpc_common.h"

/*************************************
              define
*************************************/

/**************************************
              typedef
**************************************/

/*************************************
         function prototypes
*************************************/
static void CLICmd_ResetCtrl(CLI_HandleTypeDef *pCli, int argc, char *argv[]);
//static void CLICmd_DebugCtrl(CLI_HandleTypeDef *pCli, int argc, char *argv[]);
//static void CLICmd_MemCtrl(CLI_HandleTypeDef *pCli, int argc, char *argv[]);
//static void CLICmd_LedCtrl(CLI_HandleTypeDef *pCli, int argc, char *argv[]);

/*************************************
              variable
*************************************/
extern const CLICmdTypedef CLICmd_GpioCtrl[];
extern const CLICmdTypedef cliCmdTableE2prom[];
extern const CLICmdTypedef cliCmdTableReg[];
//extern const CLICmdTypedef CLICmd_IRCtrl[];
//extern const CLICmdTypedef CLICmd_StoreCtrl[];

//const CLICmdTypedef CLI_CmdTableMain[] =
//{
//  {"cd"		, "goto dir", CLICmd_GotoTree, 0},
//  {"reg"	, "reg dir", 0, cliCmdTableReg},
//  {"gpio"	, "gpio dir", 0, CLICmd_GpioCtrl},
//  {"reset"	, "reset {iwdg/soft}", CLICmd_ResetCtrl, 0},
//  {"debug"	, "debug (sys/board/test) 0~5", CLICmd_DebugCtrl, 0},
//  {"mem"	, "mem {print/malloc/free} [size]", CLICmd_MemCtrl, 0},
//  {"eep"	, "e2prom dir", 0, cliCmdTableE2prom},
//  {"ir"		, "ir dir", 0, CLICmd_IRCtrl},
//  {"store"	, "store dir", 0, CLICmd_StoreCtrl},
//  {"led"	, "led {r/g} {on/off/normal/emcy}", CLICmd_LedCtrl, 0},
//
//  // last command must be all 0s.
//  {0, 0, 0, 0}
//};

CLI_CMD_EXPORT(reg		, "reg dir", 0, cliCmdTableReg);
CLI_CMD_EXPORT(gpio		, "gpio dir", 0, CLICmd_GpioCtrl);
CLI_CMD_EXPORT(reset	, "reset {iwdg/soft}", CLICmd_ResetCtrl, 0);
//CLI_CMD_EXPORT(debug	, "debug (sys/board/485/ctrl/cmd) 0~5", CLICmd_DebugCtrl, 0);
//CLI_CMD_EXPORT(mem		, "mem {print/malloc/free} [size]", CLICmd_MemCtrl, 0);
//CLI_CMD_EXPORT(eep		, "e2prom dir", 0, cliCmdTableE2prom);

/*************************************
              function
*************************************/
/**
  * @brief  CLICmd_DebugCtrl
  * @param  
  * @retval 
  */
//void CLICmd_DebugCtrl(CLI_HandleTypeDef *pCli, int argc, char *argv[])
//{
//}

//uint8_t *p[10] = {NULL};
///**
//  * @brief  CLICmd_DebugCtrl
//  * @param
//  * @retval
//  */
//void CLICmd_MemCtrl(CLI_HandleTypeDef *pCli, int argc, char *argv[])
//{
//	if(!stricmp(argv[1], "print"))
//	{
//		//vast_getmemtablestatus();
//	}
//	else if(!stricmp(argv[1], "malloc"))
//	{
//		uint8_t i = str2u32(argv[2]);
//		uint32_t size = str2u32(argv[3]);
//
//		if(p[i] == NULL)
//		{
//			//p[i] = vast_malloc(size);
//			p[i] = malloc(size);
//		}
//		else
//		{
//			printf("p[%d]:%p, p[%d]:%d\r\n", i, p[i], i, *p[i]);
//		}
//	}
//	else if(!stricmp(argv[1], "free"))
//	{
//		uint8_t i = str2u32(argv[2]);
//
//		if(p[i] == NULL)
//		{
//			printf("p[%d]:%p, p[%d]:%d\r\n", i, p[i], i, *p[i]);
//		}
//		else
//		{
//			//vast_free(p[i]);
//			free(p[i]);
//			p[i] = NULL;
//		}
//
//	}
//}

/**
  * @brief  CLICmd_IwdgCtrl
  * @param  
  * @retval 
  */
void CLICmd_ResetCtrl(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
  uint32_t ts;
  uint32_t cnt;
  if(argc == 2)
  {
		if(!stricmp(argv[1], "iwdg"))
		{
			cnt = 0;
			ts = HAL_GetTick();
			LL_IWDG_ReloadCounter(IWDG);
			do
			{
				while(HAL_GetTick() - ts < cnt);
				printf("(%d) ", (unsigned int)(HAL_GetTick() - ts));
				cnt += 10;
			}while(1);
		}
		else if(!stricmp(argv[1], "soft"))
		{
			NVIC_SystemReset();
		}
  }
}

//------------------------------------------------------------------------------
//-   common command functions.
//------------------------------------------------------------------------------
void cliCmdReadRegByte(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
  volatile uint8_t *addr;
  uint32_t len = 1;
  uint32_t idx;
  if(argc > 1)
  {
    addr = (uint8_t *)hex2u32(argv[1]);
    if(argc > 2)
    {
      len = str2u32(argv[2]);
      if(len < 1)
      {
        len = 1;
      }
    }

    for(idx = 0; idx < len; idx++)
    {
      if((idx & 0x07) == 0)
      {
        pCli->Init.Write("\r\n[0x%08X]", addr + idx);
      }
      pCli->Init.Write(" 0x%02X", *(addr + idx));
    }
    pCli->Init.Write("\r\n");
  }
}

void cliCmdWriteRegByte(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
  volatile uint8_t *addr;
  uint8_t value;
  if(argc > 2)
  {
    addr = (uint8_t *)hex2u32(argv[1]);
    value = hex2u32(argv[2]);

    *addr = value;
    pCli->Init.Write("[0x%08X] = 0x%02X\r\n", addr, *addr);
  }
}

void cliCmdReadReg(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
  volatile uint32_t *addr;
  uint32_t len = 1;
  uint32_t idx;
  if(argc > 1)
  {
    addr = (uint32_t *)(hex2u32(argv[1]) & 0xfffffffc);
    if(argc > 2)
    {
      len = str2u32(argv[2]);
      if(len < 1)
      {
        len = 1;
      }
    }

    for(idx = 0; idx < len; idx++)
    {
      if((idx & 0x03) == 0)
      {
        pCli->Init.Write("\r\n[0x%08X]", addr + idx);
      }
      pCli->Init.Write(" 0x%08X", *(addr + idx));
    }
    pCli->Init.Write("\r\n");
  }
}

void cliCmdWriteReg(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
  volatile uint32_t *addr;
  uint32_t value;
  if(argc > 2)
  {
    addr = (uint32_t *)(hex2u32(argv[1]) & 0xfffffffc);
    value = hex2u32(argv[2]);

    *addr = value;
    pCli->Init.Write("[0x%08X] = 0x%08X\r\n", addr, *addr);
  }
}


/**
  * @brief  CLICmd_GpioCtrl
  * @param
  * @retval
  */
const CLICmdTypedef cliCmdTableReg[] =
{
	{"rb"		, "read reg:rb 0xAddr len(Byte)", cliCmdReadRegByte, 0},
	{"wb"		, "write reg:wb 0xAddr 0xVal(Byte)", cliCmdWriteRegByte, 0},
	{"r"		, "read reg:r 0xAddr len(Word)", cliCmdReadReg, 0},
	{"w"		, "write reg:w 0xAddr 0xVal(Word)", cliCmdWriteReg, 0},
	{0, 0, 0, 0}
};
//------------------------------------------------------------------------------
//-   custom command functions. GPIO
//------------------------------------------------------------------------------
//pio (a-k) (0-f) (i/oo/op/fo/fp/a) (n/u/d) [0-16]
void cliCmdGpioFun(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
  uint32_t index;
  GPIO_InitTypeDef GPIO_InitStruct;
  uint8_t altFun = 0;
  char gpio;
  char mode;
  char pullType;
  char outType;
  
  if(argc > 4)
  {
    gpio = argv[1][0];
    index = hex2u32(argv[2]);
    mode = argv[3][0];
    outType = argv[3][1];
    pullType = argv[4][0];
    if(argc > 5)
    {
      altFun = str2u32(argv[5]);
    }

    if(gpio >= 'a')
    {
      gpio = gpio - 'a';
    }
    else
    {
      gpio = gpio - 'A';
    }

    //GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.Pin = 1<<index;
    switch(mode)
    {
    case 'i':
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      break;
    case 'o':
      if(outType == 'p')
      {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
      }
      else
      {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
      }
      break;
    case 'f':
      if(outType == 'p')
      {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      }
      else
      {
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
      }
      break;
    case 'a':
      GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
      break;
    }
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    switch(pullType)
    {
    case 'n':
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      break;
    case 'u':
      GPIO_InitStruct.Pull = GPIO_PULLUP;
      break;
    case 'd':
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
      break;
    }
    GPIO_InitStruct.Alternate = altFun;
    
    HAL_GPIO_Init((GPIO_TypeDef *)(GPIOA_BASE+(0x0400*gpio)), &GPIO_InitStruct);
    pCli->Init.Write("GPIO-%c-%d set.\r\n", gpio+'A', (unsigned int)index);
  }
}

//p (a-k) (0-f) [1/0]
void cliCmdGpioPort(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
  uint16_t index;
  uint8_t value;
  char gpio;
  
  if(argc > 2)
  {
    gpio = argv[1][0];
    index = hex2u32(argv[2]);
    if(argc > 3)
    {
      value = argv[3][0] - '0';
    }
    else
    {
      value = 0xff;
    }

    if(gpio >= 'a')
    {
      gpio = gpio - 'a';
    }
    else
    {
      gpio = gpio - 'A';
    }

    if(index > 15)
    {
      index = 15;
    }
    
    if(argc > 3)
    {
      HAL_GPIO_WritePin((GPIO_TypeDef *)(GPIOA_BASE+(0x0400*gpio)), 1<<index, (GPIO_PinState)(value));
    }
    else
    {
      value = HAL_GPIO_ReadPin((GPIO_TypeDef *)(GPIOA_BASE+(0x0400*gpio)), 1<<index);
    }
    pCli->Init.Write("GPIO-%c-%d = %d.\r\n", gpio+'A', index, value);
  }
}

/**
  * @brief  CLICmd_GpioCtrl
  * @param  
  * @retval 
  */
const CLICmdTypedef CLICmd_GpioCtrl[] =
{
  //{"pio", "pin set in/out{}/altfun{}<>/analog none/pullUp/pullDown funNum {openDrain/pushPull}:\r\n\tpio (a-k) (0-f) (i/oo/op/fo/fp/a) (n/u/d) [0-16]", cliCmdGpioFun, 0},
  {"pio", "pio (a-k) (0-f) (i/oo/op/fo/fp/a) (n/u/d) [0-16]", cliCmdGpioFun, 0},
  {"p", "set/get port:p (a-k) (0-f) [1/0]", cliCmdGpioPort, 0},
  // last command must be all 0s.
  {0, 0, 0, 0}
};

//------------------------------------------------------------------------------
//-   custom command functions. store
//------------------------------------------------------------------------------

void CLICmd_fault_test_by_div0(void) {
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR
    int x, y, z;

    *SCB_CCR |= (1 << 4); /* bit4: DIV_0_TRP. */

    x = 10;
    y = 0;
    z = x / y;
    printf("z:%d\n", z);
}
CLI_CMD_EXPORT(cmback	, "{div0}", CLICmd_fault_test_by_div0, 0);

#define BUFFER_SIZE    36
//#define BUFFER_SIZE    4
void CLICmd_crc_test(CLI_HandleTypeDef *pCli) {
    const uint8_t aDataBuffer[BUFFER_SIZE] =
    {
        0x21, 0x10, 0x00, 0x00, 0x63, 0x30, 0x42, 0x20, 0xa5, 0x50, 0x84, 0x40,
        0xe7, 0x70, 0xc6, 0x60, 0x4a, 0xa1, 0x29, 0x91, 0x8c, 0xc1, 0x6b, 0xb1,
        0xce, 0xe1, 0xad, 0xd1, 0x31, 0x12, 0xef, 0xf1, 0x52, 0x22, 0x73, 0x32,
    };

    /* Expected CRC Value */
    uint32_t uwExpectedCRCValue = 0xFF813A5C;

    register uint32_t data = 0;
    register uint32_t index = 0;

    LL_CRC_ResetCRCCalculationUnit(CRC);
    //LL_CRC_DeInit(CRC);

    /* Compute the CRC of Data Buffer array*/
    for (index = 0; index < (BUFFER_SIZE / 4); index++)
    {
        data = (uint32_t)((aDataBuffer[4 * index + 3] << 24) | (aDataBuffer[4 * index + 2] << 16) | (aDataBuffer[4 * index + 1] << 8) | aDataBuffer[4 * index]);
        LL_CRC_FeedData32(CRC, data);
    }

    __IO uint32_t uwCRCValue = LL_CRC_ReadData32(CRC);

    if (uwCRCValue != uwExpectedCRCValue)
    {
		pCli->Init.Write("err crc: cal: %#x, expect: %#x\r\n", uwCRCValue, uwExpectedCRCValue);
    }
    else
    {
		pCli->Init.Write("ok crc: %#x\r\n", uwCRCValue);
    }

	pCli->Init.Write("crc: %#x\r\n", mtd_crc32(0, (const char *)aDataBuffer, BUFFER_SIZE));

}
//CLI_CMD_EXPORT(crc	, "{test}", CLICmd_crc_test, 0);

/**
 *   * @brief  CLICmd_Print
 *     * @param  
 *       * @retval 
 *         */
void CLICmd_DevList(CLI_HandleTypeDef *pCli, int argc, char *argv[])
{
    struct list_head *iter;

    list_for_each(iter, object_lists())
    {
        //if (iter) {
            struct object *o = container_of(iter, struct object, entry);
            pCli->Init.Write("%s  ", o->name);
        //}
    }
    pCli->Init.Write("\r\n");
}
CLI_CMD_EXPORT(list_dev, "print dev list", CLICmd_DevList, 0);

/************************ (C) COPYRIGHT chenzhipeng *****END OF FILE****/

	
