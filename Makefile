PROJECT := minimal
BUILD_DIR ?= build

CFLAGS += -Wall -Wextra -g -Wno-format


SRCS = \
       minimal.c \
       startup.c \
       with-libc.c \
       uart.c \

#INCLUDES += .

include ./common.mk
