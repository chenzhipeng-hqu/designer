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
#include "worker_route.h"

/***********************************************
                    define
***********************************************/
//#ifdef configUSING_WORKER_ROUTE

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
error_t worker_route_update_robot(observer_t *observer, const object_t *object)
{
    error_t ret = 0;
    robot_t *robot = (robot_t *)object;
    printf("%s position:%d\r\n", __FUNCTION__, robot->get_position(robot));
    printf("%s joint_angle:%d\r\n", __FUNCTION__, robot->get_joint_angle(robot));

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t worker_route_update(observer_t *observer, const object_t *object)
{
    error_t ret = 0;

    static error_t (*const update_func[])(observer_t *observer, const object_t *object) = {
        &worker_route_update_robot,
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
error_t worker_route_register(worker_route_t *worker)
{
    error_t ret = 0;
    worker->observer.update = worker_route_update;
    sprintf((char *)worker->observer.name, "route");


    return ret;
}

/**
  * @}
  */
//#endif [>configUSING_ROBOT<]

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/




