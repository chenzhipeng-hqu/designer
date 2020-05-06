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

/***********************************************
                    define
***********************************************/
//#ifdef configUSING_ROBOT

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
static error_t robot_position(robot_t *robot)
{
    error_t ret = 0;

    return ret;
}
/**
  * @brief  vast_func.
  * @param
  * @retval
  */
static error_t robot_joint_angle(robot_t *robot)
{
    error_t ret = 0;

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
static error_t robot_speed(robot_t *robot)
{
    error_t ret = 0;

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
static error_t robot_changed(robot_t *robot)
{
    error_t ret = 0;
    object_t *object = (object_t *)robot;
    object->notify(object);

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t robot_register(robot_t *robot)
{
    error_t ret = 0;

    object_register(&robot->object);
    sprintf((char *)robot->object.name, "robot");

    robot->get_position    = robot_position;
    robot->get_joint_angle = robot_joint_angle;
    robot->get_speed       = robot_speed;
    robot->changed         = robot_changed;

    return ret;
}

/**
  * @}
  */
//#endif [>configUSING_ROBOT<]

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/




