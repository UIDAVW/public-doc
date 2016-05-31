#pragma once
#include "afxwin.h"
#include "StreamPlayerAPI.h"

#include <string>

class PlayerMsgNotify : public LYCloud::PlayerMsgCallBack
{
public:
	void handleMsg(const int & event_id , void * data)
	{
		if(data != NULL)
			printf("callback msg:%s , %d\n",data,event_id);

		printf("handle empty msg\n");
	}
};

class PlayWindowDialog :public CDialog
{
public:
	PlayWindowDialog(void);
	PlayWindowDialog(CWnd * p_ParentHwnd);
	~PlayWindowDialog(void);
private:
	std::string getCurrentFileDir();

public:
	void setParentHwnd(CWnd * p_ParentHwnd);
	bool init();

public:
	int startPlay(const std::string & url);
	void stopPlay();
	void mute();
	void unmute();
	int snapshot();
	int startLocalRecord();
	void stopLocalRecord();

	void getStreamInfoTest();

private:
	CWnd *				m_HParentHwnd;
	StreamPlayer		m_objStreamPlayer;
	PlayerMsgNotify		m_objMsgHandler;
};

