/*****************************************************************************
* Product: "DPP" example on STM32F4-Discovery board, cooperative QV kernel
* Last Updated for Version: 6.5.0
* Date of the Last Update:  2019-05-09
*
*                    Q u a n t u m  L e a P s
*                    ------------------------
*                    Modern Embedded Software
*
* Copyright (C) 2005-2019 Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* https://www.state-machine.com
* mailto:info@state-machine.com
*****************************************************************************/
#include <core/init.h>
//#include <core/softtimer.h>
//#include "core/device.h"
//#include <core/croutine.h>
//#include <qpc.h>
/*#include "stm32f4xx.h"  [> CMSIS-compliant header file for the MCU used <]*/
//#include "stm32f4xx_ll_usart.h"
//#include "stm32f4xx_ll_iwdg.h"
//#include "qpc_common.h"
/*#include "main.h"*/
#include "bsp.h"
/*#include "lwip.h"*/
//#include "cm_backtrace.h"

#define LOG_TAG    "bsp"
#include <elog.h>

/* add other drivers if necessary... */

/* ISRs defined in this BSP ------------------------------------------------*/
//void SysTick_Handler(void);
/*MAJOR*/
/*MINOR*/
/*REVISION*/
const char SW_VERSION[] = "0.0.1";
const char HW_VERSION[] = "ATS9_D";
const char MANUFACTURER[] = "CVTE";
const char buildDate[] = __DATE__;
const char buildTime[] = __TIME__;

/* Local-scope defines -----------------------------------------------------*/


/**
 * @brief configures IWDG and enable watchdog.
 * @param None
 * @retval None
 */
static int startCheck(void)
{
//	int ret = 0;
  /*##-1- Check if the system has resumed from IWDG reset ####################*/
	if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
	{
		/* Clear reset flags */
		__HAL_RCC_CLEAR_RESET_FLAGS();
//		ret = RCC_FLAG_PORRST;
		printf("\r\nReboot from POR/PDR reset!\r\n");
	}
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST) != RESET)
  {
    /* Clear reset flags */
    __HAL_RCC_CLEAR_RESET_FLAGS();
//		ret = RCC_FLAG_LPWRRST;
		printf("\r\nReboot from Low-power reset!\r\n");
  }
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
  {
    /* Clear reset flags */
    __HAL_RCC_CLEAR_RESET_FLAGS();
//		ret = RCC_FLAG_WWDGRST;
		printf("\r\nReboot from WWDG reset!\r\n");
  }
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) != RESET)
  {
    /* Clear reset flags */
    __HAL_RCC_CLEAR_RESET_FLAGS();
//		ret = RCC_FLAG_SFTRST;
		printf("\r\nReboot from Software reset!\r\n");
  }
  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) != RESET)
  {
    /* Clear reset flags */
    __HAL_RCC_CLEAR_RESET_FLAGS();
//		ret = RCC_FLAG_BORRST;
		printf("\r\nReboot from BOR reset!\r\n");
  }
	else if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
	{
	  __HAL_RCC_CLEAR_RESET_FLAGS();
//		ret = RCC_FLAG_IWDGRST;
		printf("\r\nReboot from IWDG reset!\r\n");
	}
	  else if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
	  {
	    __HAL_RCC_CLEAR_RESET_FLAGS();
//		ret = RCC_FLAG_PINRST;
		printf("\r\nReboot from NRST reset!\r\n");
	  }
  else
  {
//		ret = 0;
		printf("\r\nBoot OK. this is application.\r\n");
  }

  /* Enable the LSI oscillator */
  __HAL_RCC_LSI_ENABLE();
  /* Wait till LSI is ready */
  while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET)
  {
  }
#if(MCU_DBG_IWDG_FREEZE)
  __HAL_DBGMCU_FREEZE_IWDG();
#else
  //__HAL_DBGMCU_UNFREEZE_IWDG();// default mode.
#endif

  printf("HCLK=%ldMHz, Tick=%ldms, V%s:[%s %s]\r\n", HAL_RCC_GetHCLKFreq()/1000000, HAL_GetTick(), SW_VERSION, buildDate, buildTime);
  //printf("UID:0x%08lx %08lx %08lx\r\n", *(__IO uint32_t *)(UID_BASE+8), *(uint32_t *)(UID_BASE+4), *(uint32_t *)(UID_BASE+0));
  //printf("FLASHSIZE_BASE:%dKB\r\n", *(uint16_t *)FLASHSIZE_BASE);
  //printf("PACKAGE_BASE:%d\r\n", *(uint8_t *)PACKAGE_BASE);
  printf("bss_start:%p, bss_end:%p\r\n", &__bss_start__, &__bss_end__);
  printf("heap_start:%p, heap_end:%p\r\n", (int *)HEAP_BEGIN, (int *)HEAP_END);
  printf("sstack:%p, estack:%p\r\n", &_sstack, &_estack);

	return 0;
}
//postcore_initcall(startCheck);



/**
 * @brief configures IWDG and enable watchdog.
 * @param None
 * @retval None
 */
int vast_bsp_init(void)
{
    /*vast_uart_bsp_init();*/

/*#ifdef VAST_USING_MEMHEAP_AS_HEAP*/
    /*vast_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);*/
/*#endif*/
    /*startCheck();*/

    return 0;
}

//core_initcall(vast_bsp_init);

