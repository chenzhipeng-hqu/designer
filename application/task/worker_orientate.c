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
#include "robot.h"
#include "camera.h"
#include "worker_orientate.h"

/***********************************************
                    define
***********************************************/
//#ifdef configUSING_WORKER_ORIENTATE

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
error_t worker_orientate_update_robot(observer_t *observer, const object_t *object)
{
    error_t ret = 0;
    robot_t *robot = (robot_t *)object;
    printf("%s position:%d\r\n", __FUNCTION__, robot->get_position(robot));

    return ret;
}
/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t worker_orientate_update_camera(observer_t *observer, const object_t *object)
{
    error_t ret = 0;
    camera_t *camera = (camera_t *)object;
    printf("%s picture:%d\r\n", __FUNCTION__, camera->get_picture(camera));

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t worker_orientate_update(observer_t *observer, const object_t *object)
{
    error_t ret = 0;

    static error_t (*const update_func[])(observer_t *observer, const object_t *object) = {
        &worker_orientate_update_robot,
        &worker_orientate_update_camera,
    };

    for (uint8_t i=0; i<sizeof(update_func)/sizeof(update_func[0]); i++) {
        if (observer->list[i] == object) {
            update_func[i](observer, object);
            break;
        }
    }

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t worker_orientate_register(worker_orientate_t *worker)
{
    error_t ret = 0;
    worker->observer.update = worker_orientate_update;
    sprintf((char *)worker->observer.name, "orientate");


    return ret;
}

/**
  * @}
  */
//#endif [>configUSING_ROBOT<]

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/




