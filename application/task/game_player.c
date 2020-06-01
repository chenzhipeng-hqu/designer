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
#include "game_player.h"

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
  * @brief xxx 
  * @param
  * @retval
  */
static error_t login(char *pName, char *pPassword, void *pGamePlayer)
{
    error_t ret = 0;
    printf("user :%s is login in !\n", pName);
    return ret;
}

/**
  * @brief xxx 
  * @param
  * @retval
  */
static error_t killBoss(void *pGamePlayer)
{
    error_t ret = 0;
    printf("%s is killing the boss! \n", ((GamePlayer *)pGamePlayer)->acName);
    return ret;
}

static error_t upgrade(void *pGamePlayer)
{
    error_t ret = 0;
    printf("%s is upgrading !\n", ((GamePlayer *)pGamePlayer)->acName);
    return ret;
}

static error_t DeleteGamePlayer(void *data)
{
    error_t ret = 0;
    GamePlayer *pGamePlayer = (GamePlayer *)data;
    if(pGamePlayer)
    {
        free(pGamePlayer);
        pGamePlayer = NULL;
    }
    return ret;
}

/**
  * @brief xxx 
  * @param
  * @retval
  */
static GamePlayer *CreateGamePlayer(IGamePlayer *pIGamePlayer, char *pName)
{
    GamePlayer *pGamePlayer = NULL;
    if(!pIGamePlayer)
    {
        return NULL;
    }
    else
    {
        pGamePlayer = (GamePlayer *)malloc(sizeof(GamePlayer));
        if(!pGamePlayer)
        {
            return NULL;
        }
        memset(pGamePlayer, 0, sizeof(GamePlayer));
        strcpy(pGamePlayer->acName, pName);
        pGamePlayer->DeleteGamePlayer = DeleteGamePlayer;
        pGamePlayer->gmplayer.login = login;
        pGamePlayer->gmplayer.killBoss = killBoss;
        pGamePlayer->gmplayer.upgrade = upgrade;
        pGamePlayer->gmplayer.DeleteIGamePlayer = pGamePlayer->DeleteGamePlayer;
        return pGamePlayer;
    }
}


/**
  * @brief xxx 
  * @param
  * @retval
  */
static error_t  ProxykillBoss(void * pGamePlayerProxy)
{
    error_t ret = 0;
    ((GamePlayerProxy *)pGamePlayerProxy)->pGamePlayer->gmplayer.killBoss(((GamePlayerProxy *)pGamePlayerProxy)->pGamePlayer);    /*代理执行被代理者的方法*/
    return ret;
}

static error_t  Proxylogin(char *pName, char *pPassword, void *pGamePlayerProxy)
{
    error_t ret = 0;
    ((GamePlayerProxy *)pGamePlayerProxy)->pGamePlayer->gmplayer.login(pName, pPassword, pGamePlayerProxy);
    return ret;
}

static error_t Proxyupgrade(void *pGamePlayerProxy)
{
    error_t ret = 0;
    ((GamePlayerProxy *)pGamePlayerProxy)->pGamePlayer->gmplayer.upgrade(((GamePlayerProxy *)pGamePlayerProxy)->pGamePlayer);
    return ret;
}

static error_t  DeleteGamePlayerProxy(void *data)
//static error_t  DeleteGamePlayerProxy(GamePlayerProxy *pGamePlayerProxy)
{
    GamePlayerProxy *pGamePlayerProxy = (GamePlayerProxy *)data;
    error_t ret = 0;
    if(pGamePlayerProxy->pGamePlayer)
    {
        pGamePlayerProxy->pGamePlayer->DeleteGamePlayer(pGamePlayerProxy->pGamePlayer);
    }
    if(pGamePlayerProxy)
    {
        free(pGamePlayerProxy);
        pGamePlayerProxy = NULL;
    }
    return ret;
}

/**
  * @brief xxx 
  * @param
  * @retval
  */
GamePlayerProxy *CreateProxy(char *pName)
{
    GamePlayerProxy *pGamePlayerProxy = NULL;


    pGamePlayerProxy = (GamePlayerProxy *)malloc(sizeof(GamePlayerProxy));
    if(!pGamePlayerProxy)
    {
        return NULL;
    }
    memset(pGamePlayerProxy, 0, sizeof(GamePlayerProxy));


    pGamePlayerProxy->pGamePlayer = CreateGamePlayer(
            (IGamePlayer *)pGamePlayerProxy, pName);  /*创建被代理者*/


    pGamePlayerProxy->DeleteGamePlayerProxy = DeleteGamePlayerProxy;
    pGamePlayerProxy->gmplayer.login = Proxylogin;
    pGamePlayerProxy->gmplayer.killBoss = ProxykillBoss;
    pGamePlayerProxy->gmplayer.upgrade = Proxyupgrade;
    pGamePlayerProxy->gmplayer.DeleteIGamePlayer = pGamePlayerProxy->DeleteGamePlayerProxy;
    return pGamePlayerProxy;
}

/*[>场景<]*/
/*void main()*/
/*{*/
    /*[>定义一个代理者<]*/
    /*IGamePlayer *pPlayProxy = (IGamePlayer *)CreateProxy("zhangsan"); //转换为抽象类， 即场景只依赖于抽象类*/


    /*[>开始打游戏，记下时间戳<]*/
    /*printf("game start time is : 2014-1-21 9:00\n");*/


    /*[>代理登录<]*/
    /*pPlayProxy->login("zhangsan", "password", pPlayProxy);*/


    /*[>代理打怪<]*/
    /*pPlayProxy->killBoss(pPlayProxy);*/


    /*[>代理升级<]*/
    /*pPlayProxy->upgrade(pPlayProxy);*/
    /*[>游戏结束<]*/
    /*printf("game end time is :2014-1-21 10:00");*/


    /*[>释放资源<]*/
    /*pPlayProxy->DeleteIGamePlayer(pPlayProxy);*/
/*}*/

/**
  * @}
  */
//#endif [>configUSING_ROBOT<]

/*************** (C) COPYRIGHT chenzhipeng *******END OF FILE******/




