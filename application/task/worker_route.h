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
#ifndef __WORKER_TOURE_H__
#define __WORKER_TOURE_H__


#ifdef __cplusplus
 extern "C" {
#endif

/***********************************************
                    include
***********************************************/
#include "vast_config.h"
#include "vast_common.h"
#include "component/observer.h"

/***********************************************
                    define
***********************************************/

/***********************************************
                    typedef
***********************************************/
typedef struct _worker_route
{
    observer_t observer;

}worker_route_t;

/***********************************************
               function prototypes
***********************************************/
error_t worker_route_register(worker_route_t *worker);

/***********************************************
	      		    inline
***********************************************/

/***********************************************
                   variable
***********************************************/


#ifdef __cplusplus
}
#endif

#endif /* __WORKER_TOURE_H__ */
/**
  * @}
  */


/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/

