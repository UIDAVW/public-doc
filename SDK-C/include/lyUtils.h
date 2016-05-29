#ifndef __LY_UTILS_H__
#define  __LY_UTILS_H__

#ifdef __cplusplus
extern "C"{
#endif

#define RESET_MSG_TYPE 6
#define RESET_MSG_SUB_ID 'r' //114
#define MSG_SUB_ID 'a' //97

#define BUFFER_MAX 256
typedef struct _myMsg
{
	long type;
	char buffer[BUFFER_MAX];
}myMsg;

int createMsgQueForMsg(unsigned char sub_id);

int getSN(char* sn);

int sync_time(char* srv_ip);

int checkNetStatus(char* net_interface_name);

unsigned long long getUSec();

#ifdef __cplusplus
}
#endif

#endif