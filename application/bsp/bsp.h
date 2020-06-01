/**
 ******************************************************************************
 * @file    xxx.h
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

/* Define to prevent recursive inclusion */
#ifndef __VAST_BSP_H__
#define __VAST_BSP_H__

#ifdef __cplusplus
 extern "C" {
#endif

/***********************************************
                    include
***********************************************/
//#include "stm32f407xx.h"

/***********************************************
                    define
***********************************************/

/***********************************************
                    typedef
***********************************************/

/***********************************************
               function prototypes
***********************************************/
extern int vast_bsp_init(void);
extern int vast_uart_bsp_init(void);


/***********************************************
	      		    inline
***********************************************/


/***********************************************
                   variable
***********************************************/
extern const char SW_VERSION[];
extern const char HW_VERSION[];
extern const char MANUFACTURER[];

extern const char buildDate[];
extern const char buildTime[];

#ifdef __cplusplus
}
#endif

#endif /* __VAST_BSP_H__ */
/**
  * @}
  */


/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/


