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
#include "core/list.h"

#include "game_player.h"

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

LIST_HEAD(list);
/***********************************************
                   function
***********************************************/
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

    /*定义一个代理者*/
    IGamePlayer *pPlayProxy = (IGamePlayer *)CreateProxy("zhangsan"); //转换为抽象类， 即场景只依赖于抽象类

    /*开始打游戏，记下时间戳*/
    printf("game start time is : 2014-1-21 9:00\n");

    /*代理登录*/
    pPlayProxy->login("zhangsan", "password", pPlayProxy);

    /*代理打怪*/
    pPlayProxy->killBoss(pPlayProxy);

    /*代理升级*/
    pPlayProxy->upgrade(pPlayProxy);
    /*游戏结束*/
    printf("game end time is :2014-1-21 10:00");

    /*释放资源*/
    pPlayProxy->DeleteIGamePlayer(pPlayProxy);

    printf("finish!.\r\n");
    
    return 0;
}

/**
  * @}
  */

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/
