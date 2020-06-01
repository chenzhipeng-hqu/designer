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
#ifndef __WORKER_TOURE_H__
#define __WORKER_TOURE_H__


#ifdef __cplusplus
 extern "C" {
#endif

/***********************************************
                    include
***********************************************/
#include "vast_config.h"
#include "vast_common.h"

/***********************************************
                    define
***********************************************/

/***********************************************
                    typedef
***********************************************/
/*抽象游戏者  代理*/
typedef struct _IGamePlayer IGamePlayer;
struct _IGamePlayer
{
    error_t (*login)(char *pName, char *pPassword, void *);
    error_t (*killBoss)(void *);
    error_t (*upgrade)(void *);
    error_t (*DeleteIGamePlayer)(void *);
};
/*游戏者   具体*/
typedef struct _GamePlayer GamePlayer;
struct _GamePlayer
{
    IGamePlayer gmplayer;   /*继承抽象游戏者*/
    char acName[10];        /*游戏者姓名*/
    //error_t (*DeleteGamePlayer)(GamePlayer *pGamePlayer);
    error_t (*DeleteGamePlayer)(void *);
};

/*普通代理的代理者*/
typedef struct _GamePlayerProxy GamePlayerProxy;
struct _GamePlayerProxy
{
    IGamePlayer gmplayer;   /*继承抽象游戏者*/
    GamePlayer *pGamePlayer; /*被代理者*/
    //error_t (*DeleteGamePlayerProxy)(GamePlayerProxy *pGamePlayerProxy);
    error_t (*DeleteGamePlayerProxy)(void *);
};

/***********************************************
               function prototypes
***********************************************/
extern GamePlayerProxy *CreateProxy(char *pName);

/***********************************************
	      		    inline
***********************************************/

/***********************************************
                   variable
***********************************************/


#ifdef __cplusplus
}
#endif

#endif /* __WORKER_TOURE_H__ */
/**
  * @}
  */


/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/

