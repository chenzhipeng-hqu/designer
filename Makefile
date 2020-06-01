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

export PRJ_ROOT ?= $(shell pwd)

export TOOL_PATH := 
export ARM_PREFIX := $(TOOL_PATH)
export CC := $(ARM_PREFIX)gcc
export CXX := $(ARM_PREFIX)g++
export LD := $(ARM_PREFIX)ld
export OBJCOPY := $(ARM_PREFIX)objcopy
export OBJDUMP := $(ARM_PREFIX)objdump
export STRIP := $(ARM_PREFIX)strip
export AR := $(ARM_PREFIX)ar
export RANLIB := $(ARM_PREFIX)ranlib
export ARCH := $(uname -s)
export LINUX := "Linux"
export BUILD_ROOT ?= build/

CUR_ROOT := $(shell pwd)
CURR_ROOT := $(subst $(PRJ_ROOT)/,,$(CUR_ROOT)/)

include prj.mak


BUILD_PATH_UP := $(shell echo $(CURR_ROOT) | sed 's,[^/]\+,..,g')

BUILD_PATH := ./$(BUILD_PATH_UP)$(BUILD_ROOT)$(CURR_ROOT)

BUILD_GEN_PATH := $(BUILD_PATH)

TARGET_BIN := $(BUILD_PATH_UP)$(BUILD_ROOT)$(TARGET)

SRCS_C := $(filter %.c,$(SRCS))
SRCS_ASM := $(filter %.s,$(SRCS))
SRCS_CXX := $(filter %.cpp,$(SRCS))
OBJS := $(addprefix $(BUILD_GEN_PATH),$(strip $(SRCS_C:.c=.obj) $(SRCS_ASM:.s=.obj) $(SRCS_CXX:.cpp=.obj)))
DEPS := $(OBJS:.obj=.dep)

CFLAGS += $(DEFS) $(INCS) -O2
CFLAGS += -fPIC
CFLAGS += -Wundef -Wall
#CFLAGS += -Werror
#LDFLAGS += -Wl,-gc-sections -Wl,-Map=$(TARGET_MAP)
LDFLAGS += -lpthread -lrt -ldl


.PHONY: all clean


all: $(TARGET_BIN)


$(TARGET_BIN): $(OBJS) $(LIBS)
	@$(CXX) $(LDFLAGS) $^ -o $@
	@echo [build] $@ OK!
	
$(LIBS)::
	@$(MAKE) -C $(PRJ_ROOT)/$(LIBS_PATH)/$(*F)

clean:
	-rm -rf $(BUILD_PATH)

$(BUILD_GEN_PATH)%.obj: %.cpp
	@echo "cc $<"
	@if [ ! -d $(@D) ]; then mkdir -p "$(@D)"; fi
	@$(CXX) $(CFLAGS) -c $< -o $@  -MMD -MT "$@" -MF $(@:.obj=.dep)

$(BUILD_GEN_PATH)%.obj: %.s
	@echo "cc $<"
	@if [ ! -d $(@D) ]; then mkdir -p "$(@D)"; fi
	@$(CC) $(CFLAGS) -c $< -o $@  -MMD -MT "$@" -MF $(@:.obj=.dep)
	
$(BUILD_GEN_PATH)%.obj: %.c
	@echo "cc $<"
	@if [ ! -d $(@D) ]; then mkdir -p "$(@D)"; fi
	@$(CC) $(CFLAGS) -c $< -o $@  -MMD -MT "$@" -MF $(@:.obj=.dep)
	
$(BUILD_GEN_PATH)%.dep:

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

show:
	@echo PRJ_ROOT = $(PRJ_ROOT)
	@echo CUR_ROOT = $(CUR_ROOT)
	@echo CURR_ROOT = $(CURR_ROOT)
	@echo BUILD_PATH_UP = $(BUILD_PATH_UP)
	@echo BUILD_PATH = $(BUILD_PATH)
	@echo BUILD_ROOT = $(BUILD_ROOT)
	@echo BUILD_GEN_PATH = $(BUILD_GEN_PATH)
	@echo TARGET_BIN = $(TARGET_BIN)
	@echo SRCS_C = $(SRCS_C)
	@echo SRCS_ASM = $(SRCS_ASM)
	@echo OBJS = $(OBJS)
	@echo DEPS = $(DEPS)
	@echo LIBS = $(LIBS)



