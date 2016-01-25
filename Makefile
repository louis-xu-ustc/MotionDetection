##
# Makefile
#

#define compile options
CC=gcc
LD=gcc
CFLAGS=-Wall -O3

#define head files directory and library
INC_DIR=-Iinclude
LIB_DIR=
#LIB_DIR=-Llib -L/usr/local/lib -Lsrc/lib

#define code directory
SRC_DIR=src
VPATH=$(SRC_DIR)

#find out all the .c and .o files
SRC_FILES=$(foreach n, $(VPATH), $(wildcard $(n)/*.c))
OBJ_FILES=$(SRC_FILES:.c=.o)

#relocate all .o files to the corresponding directory
OUTPUT_DIR:=out
OUTPUT_OBJS=$(addprefix $(OUTPUT_DIR)/, $(subst $(SRC_DIR)/, ,$(OBJ_FILES)))

#genete directory for output files
$(shell mkdir -p "$(OUTPUT_DIR)")

#target
TARGET=motion

#link
$(TARGET):$(OUTPUT_OBJS)
	$(LD) $(OUTPUT_OBJS) -o $@ $(LIB_DIR)

#compile
$(OUTPUT_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR)

#clean
.PHONY:clean
clean:
	@rm -rf $(OUTPUT_DIR)/*
	@rm -rf $(TARGET)
	@echo "Clean done!"


