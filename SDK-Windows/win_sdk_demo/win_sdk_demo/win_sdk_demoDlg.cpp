
// win_sdk_demoDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Cwin_sdk_demoDlg 对话框



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


// Cwin_sdk_demoDlg 消息处理程序

BOOL Cwin_sdk_demoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cwin_sdk_demoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	// TODO: 在此添加控件通知处理程序代码
}


void Cwin_sdk_demoDlg::OnBnClickedButtonPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cUrl;
	m_EditText.GetWindowText(cUrl);
	std::string url = WChar2Ansi(cUrl.GetBuffer(cUrl.GetLength()));
	m_play.EnableWindow(FALSE);
	int nRet = m_objPlayHwnd.startPlay(url);
	if(nRet != 0)
	{
		AfxMessageBox(_T("打开视频失败！"));
	}
	m_stop.EnableWindow(TRUE);
	cUrl.ReleaseBuffer(cUrl.GetLength());
}


void Cwin_sdk_demoDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_objPlayHwnd.stopPlay();
	m_stop.EnableWindow(FALSE);
	m_play.EnableWindow(TRUE);
	m_mute.SetWindowTextW(_T("播放声音"));
	m_muteFlag = true;
}


void Cwin_sdk_demoDlg::OnBnClickedButtonMute()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_muteFlag)
	{
		m_objPlayHwnd.mute();
		m_mute.SetWindowTextW(_T("播放声音"));
		m_muteFlag = true;
	}
	else
	{
		m_objPlayHwnd.unmute();
		m_mute.SetWindowTextW(_T("静音"));
		m_muteFlag = false;
	}
}


void Cwin_sdk_demoDlg::OnBnClickedButtonRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_recordFlag)
	{
		m_objPlayHwnd.startLocalRecord();
		m_record.SetWindowTextW(_T("停止录像"));
		m_recordFlag = true;
	}
	else
	{
		m_objPlayHwnd.stopLocalRecord();
		m_record.SetWindowTextW(_T("本地录像"));
		m_recordFlag = false;
	}
}


void Cwin_sdk_demoDlg::OnBnClickedButtonSnapshot()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_objPlayHwnd.snapshot() != 0)
		AfxMessageBox(_T("截图失败"));
}


void Cwin_sdk_demoDlg::OnBnClickedButtonPlayRecord()
{
	// TODO: 在此添加控件通知处理程序代码
}


void Cwin_sdk_demoDlg::OnBnClickedButton1GetStreaminfo()
{
	// TODO: 在此添加控件通知处理程序代码

	m_objPlayHwnd.getStreamInfoTest();
}
