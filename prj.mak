################################################################################
# Copyright (C) 2017 Maker-ray Co.,Ltd. All rights reserved.
#  __  __       _                                  
# |  \/  | __ _| | _____ _ __      _ __ __ _ _   _ 
# | |\/| |/ _` | |/ / _ \ '__|____| '__/ _` | | | |
# | |  | | (_| |   <  __/ | |_____| | | (_| | |_| |
# |_|  |_|\__,_|_|\_\___|_|       |_|  \__,_|\__, |
#                                            |___/ 
# 
# $FileName: Makefile
# $Date: 2017-08-31
# $Author: xwk
# $Note:
#   
################################################################################

TARGET := test

################ define ################
DEFS += 


################ source ################

SRCS += application/port/easylogger/elog_port.c
SRCS += application/task/main.c
SRCS += application/task/game_player.c
#SRCS += application/task/robot.c
#SRCS += application/task/camera.c
#SRCS += application/task/worker_route.c
#SRCS += application/task/worker_orientate.c
#SRCS += application/task/ui_window.c
#SRCS += kfifo.c
#SRCS += utils.c

################ library ################

LIBS += 

LIBS_PATH += lib


################ include ################

INCS += -I./application
INCS += -I./application/bsp
INCS += -I./application/port
INCS += -I./application/port/easylogger
INCS += -I./application/port/qpc
INCS += -I./application/port/shell
INCS += -I./application/task

################ vast ################
#include vast/prj.mak
INCS += -I./vast

SRCS += vast/core/utils.c
#SRCS += vast/component/observer.c

INCS += -I./vast/third/EasyLogger/easylogger/inc
SRCS += vast/third/EasyLogger/easylogger/src/elog.c
SRCS += vast/third/EasyLogger/easylogger/src/elog_async.c
SRCS += vast/third/EasyLogger/easylogger/src/elog_buf.c
SRCS += vast/third/EasyLogger/easylogger/src/elog_utils.c


################ all .c in SRCS_DIRS  ################
SRCS += $(foreach dir,$(SRCS_DIRS),$(wildcard $(dir)/*.c))

# Obj dict gen


