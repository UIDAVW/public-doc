
// win_sdk_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "win_sdk_demo.h"
#include "win_sdk_demoDlg.h"
#include "afxdialogex.h"

#include <io.h>
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void InitConsoleWindow()
{
	int nCrt = 0;
	FILE* fp;
	AllocConsole();
	nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	fp = _fdopen(nCrt, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cwin_sdk_demoDlg �Ի���



Cwin_sdk_demoDlg::Cwin_sdk_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cwin_sdk_demoDlg::IDD, pParent)
	,m_objPlayHwnd(this)
	,m_muteFlag(false)
	,m_recordFlag(false)
	,m_playRecordFlag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_objPlayHwnd.setParentHwnd(this);
}

void Cwin_sdk_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URLTEXT, m_EditText);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_play);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stop);
	DDX_Control(pDX, IDC_BUTTON_MUTE, m_mute);
	DDX_Control(pDX, IDC_BUTTON_RECORD, m_record);
}

BEGIN_MESSAGE_MAP(Cwin_sdk_demoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC_URL, &Cwin_sdk_demoDlg::OnStnClickedStaticUrl)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &Cwin_sdk_demoDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &Cwin_sdk_demoDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_MUTE, &Cwin_sdk_demoDlg::OnBnClickedButtonMute)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, &Cwin_sdk_demoDlg::OnBnClickedButtonRecord)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, &Cwin_sdk_demoDlg::OnBnClickedButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_RECORD, &Cwin_sdk_demoDlg::OnBnClickedButtonPlayRecord)
	ON_BN_CLICKED(IDC_BUTTON1_GET_STREAMINFO, &Cwin_sdk_demoDlg::OnBnClickedButton1GetStreaminfo)
END_MESSAGE_MAP()


// Cwin_sdk_demoDlg ��Ϣ�������

BOOL Cwin_sdk_demoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CloudPlatform * pPlatform = CloudPlatform::getInstance();
//	pPlatform->startCloudService(token,config,m_PlatMsgHandler,"");

	CRect rect;
	GetWindowRect(&rect);
	CRect rect_sub;
	rect_sub.left = 0;
	rect_sub.top = 0;
	rect_sub.right = 720;
	rect_sub.bottom = 480;
	m_objPlayHwnd.Create(IDD_DIALOG_PLAY, this);
	//m_objPlayHwnd.
	m_objPlayHwnd.MoveWindow(&rect_sub);
	m_objPlayHwnd.ShowWindow(SW_SHOW);
	m_objPlayHwnd.init();
	//CString cstr("rtmp://rtmp6.public.topvdn.cn/live/1003136_3356491776_1462959841_f0b918d7d6f6a26de8646838a18baac1");
	CString cstr("topvdn://rtmp6.public.topvdn.cn:1935?protocolType=2&connectType=2&token=1003136_3356491776_1463644682_17ca4d39866b0c9332c2b3b9dccb73d6");
	//CString cstr("topvdn://rtmp6.public.topvdn.cn:1935?protocolType=3&token=1003136_3356491776_1463644682_17ca4d39866b0c9332c2b3b9dccb73d6&begin=1463555590&end=1463556590");
	m_EditText.SetWindowText(cstr);

	InitConsoleWindow();
	printf("Initialize console !\n");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cwin_sdk_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cwin_sdk_demoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cwin_sdk_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen<= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	std::string strTemp(pszDst);
	delete [] pszDst;
	return strTemp;
}

void Cwin_sdk_demoDlg::OnStnClickedStaticUrl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Cwin_sdk_demoDlg::OnBnClickedButtonPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cUrl;
	m_EditText.GetWindowText(cUrl);
	std::string url = WChar2Ansi(cUrl.GetBuffer(cUrl.GetLength()));
	m_play.EnableWindow(FALSE);
	int nRet = m_objPlayHwnd.startPlay(url);
	if(nRet != 0)
	{
		AfxMessageBox(_T("����Ƶʧ�ܣ�"));
	}
	m_stop.EnableWindow(TRUE);
	cUrl.ReleaseBuffer(cUrl.GetLength());
}


void Cwin_sdk_demoDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_objPlayHwnd.stopPlay();
	m_stop.EnableWindow(FALSE);
	m_play.EnableWindow(TRUE);
	m_mute.SetWindowTextW(_T("��������"));
	m_muteFlag = true;
}


void Cwin_sdk_demoDlg::OnBnClickedButtonMute()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_muteFlag)
	{
		m_objPlayHwnd.mute();
		m_mute.SetWindowTextW(_T("��������"));
		m_muteFlag = true;
	}
	else
	{
		m_objPlayHwnd.unmute();
		m_mute.SetWindowTextW(_T("����"));
		m_muteFlag = false;
	}
}


void Cwin_sdk_demoDlg::OnBnClickedButtonRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_recordFlag)
	{
		m_objPlayHwnd.startLocalRecord();
		m_record.SetWindowTextW(_T("ֹͣ¼��"));
		m_recordFlag = true;
	}
	else
	{
		m_objPlayHwnd.stopLocalRecord();
		m_record.SetWindowTextW(_T("����¼��"));
		m_recordFlag = false;
	}
}


void Cwin_sdk_demoDlg::OnBnClickedButtonSnapshot()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_objPlayHwnd.snapshot() != 0)
		AfxMessageBox(_T("��ͼʧ��"));
}


void Cwin_sdk_demoDlg::OnBnClickedButtonPlayRecord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Cwin_sdk_demoDlg::OnBnClickedButton1GetStreaminfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_objPlayHwnd.getStreamInfoTest();
}
