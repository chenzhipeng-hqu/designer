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
#ifndef __CAMERA_H__
#define __CAMERA_H__


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
typedef struct _camera
{
    object_t object;

    error_t (*get_picture)(struct _camera *camera);
    error_t (*changed)(struct _camera *camera);
}camera_t;

/***********************************************
               function prototypes
***********************************************/
error_t camera_register(camera_t *camera);

/***********************************************
	      		    inline
***********************************************/

/***********************************************
                   variable
***********************************************/


#ifdef __cplusplus
}
#endif

#endif /* __CAMERA_H__ */
/**
  * @}
  */


/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/

