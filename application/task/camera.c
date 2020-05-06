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
#include "camera.h"

/***********************************************
                    define
***********************************************/
//#ifdef configUSING_CAMERA

/***********************************************
                    typedef
***********************************************/

/***********************************************
               function prototypes
***********************************************/

/***********************************************
                   variable
***********************************************/

/***********************************************
                   function
***********************************************/
/**
  * @brief  vast_func.
  * @param
  * @retval
  */
static error_t camera_picture(camera_t *camera)
{
    error_t ret = 0;

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
static error_t camera_changed(camera_t *camera)
{
    error_t ret = 0;
    object_t *object = (object_t *)camera;
    object->notify(object);

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t camera_register(camera_t *camera)
{
    error_t ret = 0;

    object_register(&camera->object);
    sprintf((char *)camera->object.name, "camera");

    camera->get_picture   = camera_picture;
    camera->changed       = camera_changed;

    return ret;
}

/**
  * @}
  */
//#endif [>configUSING_CAMERA<]

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/




