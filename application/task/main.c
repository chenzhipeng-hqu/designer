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
#include "vast_common.h"
#include "component/observer.h"
#include "camera.h"
#include "robot.h"
#include "worker_route.h"
#include "worker_orientate.h"
#include "ui_window.h"
#include "core/list.h"

#define     LOG_TAG     "main"
#include "elog.h"

/***********************************************
                    define
***********************************************/

/***********************************************
                    typedef
***********************************************/
typedef struct
{
    int data;
    list_t entry;
}data_list_t;

/***********************************************
               function prototypes
***********************************************/

/***********************************************
                   variable
***********************************************/
robot_t robot = {0};
camera_t camera = {0};
worker_route_t worker_route = {0};
worker_orientate_t worker_orientate = {0};

LIST_HEAD(list);
/***********************************************
                   function
***********************************************/
/**
  * @brief  main.
  * @param
  * @retval
  */
void list_test(void)
{
    for (uint8_t i=0; i<5; i++) {
        data_list_t *data = malloc(sizeof(data_list_t));
        data->data = i;
        list_add_tail(&data->entry, &list);
    }

	data_list_t *iter, *n;

	list_for_each_entry_safe(iter, n, &list, entry)
	{
        printf("data=%d\r\n", iter->data);
	}

    
}
/**
  * @brief  main.
  * @param
  * @retval
  */
int main(int argc, char *argv[])
{
    //list_test();
    
    extern int elog_initilize(void);
    elog_initilize();

    log_e("hello world.");
    log_w("hello world.");
    log_i("hello world.");
    ui_window_t *ui_window = NULL;

    robot_register(&robot);
    camera_register(&camera);

    worker_route_register(&worker_route);
    worker_orientate_register(&worker_orientate);

    ui_window = (ui_window_t *)malloc(sizeof(ui_window_t));
    assert(ui_window != NULL);
    ui_window_register(ui_window);

    bind_observer_to_object((observer_t *)&worker_route, (object_t *)&robot);
    bind_observer_to_object((observer_t *)&worker_orientate, (object_t *)&robot);
    bind_observer_to_object((observer_t *)&worker_orientate, (object_t *)&camera);
    bind_observer_to_object((observer_t *)ui_window, (object_t *)&robot);
    bind_observer_to_object((observer_t *)ui_window, (object_t *)&camera);

    robot.changed(&robot);
    camera.changed(&camera);
    ui_window->display(ui_window);

    printf("\r\nunbind worker_orientate from camera\r\n");
    unbind_observer_from_object((observer_t *)&worker_orientate, (object_t *)&camera);
    robot.changed(&robot);
    camera.changed(&camera);
    ui_window->display(ui_window);

    free(ui_window);
    printf("finish!.\r\n");
    
    return 0;
}

/**
  * @}
  */

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/
