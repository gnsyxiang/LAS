# ===============================================================
# Filename: Makefile
# -------------------------------
# Copyright(C),
# Author: zhenquan.qiu
# Version: V1.0.0
# Last modified: 31/08 2017 17:29
# Description:
#
# Change Log:
# NO.	Author		    Date		Modified
# 00	zhenquan.qiu	31/08 2017
# ===============================================================

ROOT := $(shell pwd)
RM := $(Q)rm -rf

TARGET := hello

MAIN_VERSION := 1
SUB_VERSION := 0
BUG_VERSION := 0

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
CFLAGS := -fPIC
CFLAGS += -Wall
CFLAGS += -c
CFLAGS += -I.

# -------
# ldflags
# -------
SO_NAME := -Wl,-soname,lib$(TARGET).so.$(MAIN_VERSION)

LDFLAGS := -shared $(SO_NAME)

# -------
# c files
# -------
C_SRC := $(wildcard *.c)
O_SRC := $(patsubst %.c, %.o, $(C_SRC))

all: $(TARGET)
	ln -s lib$(TARGET).so.$(MAIN_VERSION).$(SUB_VERSION).$(BUG_VERSION) lib$(TARGET).so
	ln -s lib$(TARGET).so.$(MAIN_VERSION).$(SUB_VERSION).$(BUG_VERSION) lib$(TARGET).so.$(MAIN_VERSION)

$(TARGET):
	$(CC) $(CFLAGS) $(C_SRC)
	$(CC) $(LDFLAGS) $(O_SRC)  -o lib$(TARGET).so.$(MAIN_VERSION).$(SUB_VERSION).$(BUG_VERSION)

clean:
	$(RM) $(O_SRC)
	$(RM) lib$(TARGET).so
	$(RM) lib$(TARGET).so.$(MAIN_VERSION)
	$(RM) lib$(TARGET).so.$(MAIN_VERSION).$(SUB_VERSION).$(BUG_VERSION)

debug:
	echo $(C_SRC)
	echo $(O_SRC)

