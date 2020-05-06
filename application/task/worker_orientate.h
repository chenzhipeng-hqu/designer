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
#ifndef __WORKER_ORIENTATE_H__
#define __WORKER_ORIENTATE_H__


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
typedef struct _worker_orientate
{
    observer_t observer;

}worker_orientate_t;

/***********************************************
               function prototypes
***********************************************/
error_t worker_orientate_register(worker_orientate_t *worker);

/***********************************************
	      		    inline
***********************************************/

/***********************************************
                   variable
***********************************************/


#ifdef __cplusplus
}
#endif

#endif /* __WORKER_ORIENTATE_H__ */
/**
  * @}
  */


/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/

