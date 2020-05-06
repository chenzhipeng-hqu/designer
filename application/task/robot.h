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
#ifndef __ROBOT_H__
#define __ROBOT_H__


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
typedef struct _robot
{
    object_t object;

    error_t (*get_position)(struct _robot *robot);
    error_t (*get_joint_angle)(struct _robot *robot);
    error_t (*get_speed)(struct _robot *robot);
    error_t (*changed)(struct _robot *robot);
}robot_t;

/***********************************************
               function prototypes
***********************************************/
error_t robot_register(robot_t *robot);

/***********************************************
	      		    inline
***********************************************/

/***********************************************
                   variable
***********************************************/


#ifdef __cplusplus
}
#endif

#endif /* __ROBOT_H__ */
/**
  * @}
  */


/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/

