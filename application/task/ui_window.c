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
#include "ui_window.h"

/***********************************************
                    define
***********************************************/
//#ifdef configUSING_UI_WINDOW

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
error_t ui_window_update_robot(observer_t *observer, const object_t *object)
{
    error_t ret = 0;
    robot_t *robot = (robot_t *)object;
    printf("%s position:%d\r\n", __FUNCTION__, robot->get_position(robot));
    printf("%s speed:%d\r\n", __FUNCTION__, robot->get_speed(robot));

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t ui_window_update_camera(observer_t *observer, const object_t *object)
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
error_t ui_window_update(observer_t *observer, const object_t *object)
{
    error_t ret = 0;

    static error_t (*const update_func[])(observer_t *observer, const object_t *object) = {
        &ui_window_update_robot,
        &ui_window_update_camera,
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
error_t ui_window_display(struct _ui_window* ui_window)
{
    error_t ret = 0;
    printf("%s\r\n", __FUNCTION__);

    return ret;
}

/**
  * @brief  vast_func.
  * @param
  * @retval
  */
error_t ui_window_register(ui_window_t *ui)
{
    error_t ret = 0;
    ui->observer.update = ui_window_update;
    ui->display = ui_window_display;
    sprintf((char *)ui->observer.name, "ui");


    return ret;
}

/**
  * @}
  */
//#endif [>configUSING_ROBOT<]

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/




