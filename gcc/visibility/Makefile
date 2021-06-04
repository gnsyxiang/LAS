# ===============================================================
# Filename: Makefile
# -------------------------------
# Copyright(C),
# Author: zhenquan.qiu
# Version: V1.0.0
# Last modified: 21/09 2017 14:22
# Description:
#
# Change Log:
# NO.	Author		    Date		Modified
# 00	zhenquan.qiu	21/09 2017
# ===============================================================

ROOT := $(shell pwd)
OBJ_DIR ?= objs
LIB_DIR ?= ../../lib
INC_DIR ?= ../../include

Q := @
RM := $(Q)rm -rf

MAJOR_VERSION := 1
MINOR_VERSION := 0
BUG_VERSION := 0

TARGET := visibility
TARGET_SO := lib$(TARGET).so.$(MAJOR_VERSION).$(MINOR_VERSION).$(BUG_VERSION)

MSG_LIB := LIB_COPY

# --------
# compiler
# --------
GCC_PATH := ~/Desktop/mips-gcc520-32bit/bin
GCC_NAME := mips-linux-gnu-

# CROSS_TOOL := $(GCC_PATH)/$(GCC_NAME)

CC := $(CROSS_TOOL)gcc

# ------
# cflags
# ------
CFLAGS := -Wall -I. -fPIC

MSG_CC := CC

# -------
# ldflags
# -------
SO_NAME := -Wl,-soname,lib$(TARGET).so.$(MAJOR_VERSION)

LDFLAGS := $(SO_NAME) -shared

MSG_LD := LD


# -------
# h files
# -------
INC_C := $(TARGET).h

MSG_INC := INC_COPY
# -------
# c files
# -------
SRC_C := $(wildcard *.c)
OBJ_C := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_C))
DEP_C := $(patsubst %.c, $(OBJ_DIR)/%.d, $(SRC_C))
DEPS  ?= $(DEP_C)
OBJS  ?= $(OBJ_C)

all: $(TARGET_SO) copy-lib copy-inc

$(TARGET_SO): $(OBJS)
	$(Q)echo $(MSG_LD) $<
	$(Q)$(CC) $(LDFLAGS) $(OBJS)  -o $(TARGET_SO)

	$(Q)ln -s $(TARGET_SO) lib$(TARGET).so
	$(Q)ln -s $(TARGET_SO) lib$(TARGET).so.$(MAJOR_VERSION)

copy-lib:
	$(Q)echo $(MSG_LIB)
	$(Q)mkdir -p $(LIB_DIR)
	$(Q)cp -a $(TARGET_SO) $(LIB_DIR)
	$(Q)cp -a lib$(TARGET).so $(LIB_DIR)
	$(Q)cp -a lib$(TARGET).so.$(MAJOR_VERSION) $(LIB_DIR)

copy-inc:
	$(Q)echo $(MSG_INC)
	$(Q)mkdir -p $(INC_DIR)
	$(Q)cp -a $(INC_C) $(INC_DIR)
#
# make *.c
#
$(OBJ_C): $(OBJ_DIR)/%.o : %.c
	$(Q)mkdir -p $(dir $@)
	$(Q)echo $(MSG_CC) $<
	$(Q)$(CC) -c $(CFLAGS) $< -o $@

$(DEP_C): $(OBJ_DIR)/%.d : %.c
	$(Q)mkdir -p $(dir $@);
	$(Q)$(CC) -MM $(CFLAGS) -MT $(@:%.d=%.o) $< >$@

sinclude $(DEPS)

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(TARGET)
	$(RM) lib$(TARGET).so
	$(RM) lib$(TARGET).so.$(MAJOR_VERSION)
	$(RM) $(TARGET_SO)

distclean: clean
	$(RM) $(OBJ_DIR)

debug:
	echo $(INC_C)

.PHONY: all clean distclean debug

