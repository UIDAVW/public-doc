PWD     	:= $(shell pwd)
BIN			:= lyDeviceDemo
TARGET      ?= arm-linux
CROSS_COMPILE   ?= $(TARGET)-
CPP     	:= $(CROSS_COMPILE)g++
CC      	:= $(CROSS_COMPILE)gcc
STRIP		:= $(CROSS_COMPILE)strip
SRC_DIR		:= ./src
INCLUDE_DIR	:= ./include
LIB_DIR		:= ./lib
INCLUDE		+= -I$(INCLUDE_DIR)
INCLUDE		+= -I$(INCLUDE_DIR)/lingyang
POST_BIN	:= \cp $(BIN) /root/work/nfsroot/360

LDFLAG_COMMON	:= -lpthread -lm -lz -lssl -lcrypto -ldl
LDFLAG_LY		:= -Wl,-rpath=. -lPusher -lTopvdnSDK

CFLAGS		:= -Wall -g -O2 $(INCLUDE)
LDFLAGS		:= -Wl,--as-needed -L$(LIB_DIR) $(LDFLAG_LY) $(LDFLAG_COMMON)


$(BIN) : $(SRC_DIR)/main.o $(SRC_DIR)/pushMedia.o $(SRC_DIR)/aacUtil.o $(SRC_DIR)/h264Util.o $(SRC_DIR)/lyUtils.o
	#if use $(CC),please link libstdc++.so
	$(CPP) $^ -o $@ $(LDFLAGS)
	$(STRIP) $(BIN)
	$(POST_BIN)

main.o : 
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c -o  main.o
pushMedia.o : 
	$(CC) $(CFLAGS) $(SRC_DIR)/pushMedia.c -o  pushMedia.o
aacUtil.o : 
	$(CC) $(CFLAGS) $(SRC_DIR)/aacUtil.c -o  aacUtil.o
h264Util.o : 
	$(CC) $(CFLAGS) $(SRC_DIR)/h264Util.c -o  h264Util.o
lyUtils.o : 
	$(CC) $(CFLAGS) $(SRC_DIR)/lyUtils.c -o  lyUtils.o
	
clean:
	rm -f ./src/*.o
	rm $(BIN)