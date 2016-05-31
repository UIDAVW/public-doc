
// win_sdk_demoDlg.h : ͷ�ļ�
//

#pragma once
#include "PlayWindowDialog.h"
#include "afxwin.h"

#include "CloudPlatformAPI.h"

class PlatMsgHandler : public LYCloud::PlatformMsgCallBack
{
public:
	void handleMsg(const char* aMessage)
	{
		if(NULL == aMessage)
		{
			printf("");
			return ;
		}

		//handle your message
	};
};

// Cwin_sdk_demoDlg �Ի���
class Cwin_sdk_demoDlg : public CDialogEx
{
// ����
public:
	Cwin_sdk_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WIN_SDK_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticUrl();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonMute();
	afx_msg void OnBnClickedButtonRecord();

private:
	PlayWindowDialog			m_objPlayHwnd;
	bool						m_muteFlag;
	bool						m_recordFlag;
	bool						m_playRecordFlag;
	PlatMsgHandler				m_PlatMsgHandler;
public:
	CEdit						m_EditText;
	CButton						m_play;
	CButton						m_stop;
	CButton						m_mute;
	CButton						m_record;
	afx_msg void OnBnClickedButtonSnapshot();
	afx_msg void OnBnClickedButtonPlayRecord();
	afx_msg void OnBnClickedButton1GetStreaminfo();
};
