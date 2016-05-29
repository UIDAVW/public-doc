#ifndef __RECORD_UTIL__
#define __RECORD_UTIL__

/*
����h264�ļ��Ĵ洢��ʽ��sps,pps,sei,i,p...p,sps,pps.......ÿ��nalu����ǰ�����ĸ��ֽڵ���ʼ�롣
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define READ_ONCE 128*1024 //Ӧ�ô���������Ƶ֡�Ĵ�С

typedef struct _h264Helper
{
	char* buffer;
	char* data;
	int   bufferSize;
	int   frameSize;
	int   offset;
	int   startCodeLen;
	int	  naluType;
	int   sendDoneFlag;
	FILE* fp;
	char  readFileEof;
	char  readFileFlag;
}h264Helper;

#ifdef __cplusplus
extern "C"{
#endif

int h264HelperInit(h264Helper* helper,char* fileName);

int h264HelperFree(h264Helper* helper);

int getH264Frame(h264Helper* helper);

#ifdef __cplusplus
}
#endif

#endif