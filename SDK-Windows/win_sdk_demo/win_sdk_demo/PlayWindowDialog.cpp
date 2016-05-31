#include "stdafx.h"
#include "PlayWindowDialog.h"
//#include "LogOutput.h"

std::string TCHAR2STRING(TCHAR * STR)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0,STR, -1, NULL, 0, NULL, NULL);

	char* chRtn =new char[iLen*sizeof(char)];

	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);

	std::string str(chRtn);

	return str;

}

std::string getTimeString()
{
	struct   tm     *ptm; 
	char str[16];
	time_t       ts; 
	int      year,mon,day,hour,min,sec;
	ts    =   time(NULL); 
	ptm   =   localtime(&ts); 
	year  =   ptm-> tm_year+1900;     //年 
	mon   =   ptm-> tm_mon+1;         //月 
	day   =   ptm-> tm_mday;          //日 
	hour  =   ptm-> tm_hour;        //h为与现在相比的时间差，h为0时表示当前时间
	min   =   ptm-> tm_min;           //分 
	sec   =   ptm-> tm_sec;           //秒
	sprintf(str, "%d%d%d%d%d%d", year, mon, day, hour, min, sec);

	return str;
}

PlayWindowDialog::PlayWindowDialog(void)
{
}

PlayWindowDialog::PlayWindowDialog(CWnd * p_ParentHwnd)
{
	m_HParentHwnd = p_ParentHwnd;
}

std::string PlayWindowDialog::getCurrentFileDir()
{
// 	char buf[100];
// 	GetCurrentDirectory(sizeof(buf),buf);
// 	MessageBox(buf);
// 	HINSTANCE hInst=NULL;
// 	hInst=AfxGetApp()->m_hInstance;
// 	char path_buffer[_MAX_PATH];
// 	GetModuleFileName(hInst,path_buffer,sizeof(path_buffer));//得到exe文件的全路径
// 	//分离路径和文件名。
// 	char drive[_MAX_DRIVE];
// 	char dir[_MAX_DIR];
// 	char fname[_MAX_FNAME];
// 	char ext[_MAX_EXT];
// 	_splitpath( path_buffer, drive, dir, fname, ext );
// 	CString Path;
// 	Path.Format("%s%s",drive,dir);
// 	char path[300];
// 	strcpy(path,drive);
// 	strcat(path,dir);
	TCHAR exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);
	strPath=(CString)exeFullPath;
	int position=strPath.ReverseFind('\\');
	strPath=strPath.Left(position+1); 
	TCHAR FilePath[MAX_PATH];
	GetModuleFileName(NULL,FilePath,MAX_PATH);
	
	//CString Path;
	//Path.Format("%s%s",drive,dir);
	return TCHAR2STRING(FilePath);
}

PlayWindowDialog::~PlayWindowDialog(void)
{
}

void PlayWindowDialog::setParentHwnd(CWnd * p_ParentHwnd)
{
	m_HParentHwnd = p_ParentHwnd;
}

bool PlayWindowDialog::init()
{
	return m_objStreamPlayer.initPlayer(m_hWnd,true) < 0 ? false : true;
}

int PlayWindowDialog::startPlay(const std::string & url)
{
	return m_objStreamPlayer.open(url , true , (LYCloud::PlayerMsgCallBack)m_objMsgHandler);
}

void PlayWindowDialog::stopPlay()
{
	m_objStreamPlayer.close();
}

void PlayWindowDialog::mute()
{
	m_objStreamPlayer.mute();
}

void PlayWindowDialog::unmute()
{
	m_objStreamPlayer.unmute();
}

int PlayWindowDialog::snapshot()
{
	std::string strFilePath = getCurrentFileDir() + "snapshot_" + getTimeString() + ".jpg";
	//CLogOutputEx::instance().output(OT_FILE_VIEWER, LOG_INFO_HIT, "snap file path : %s\n",strFilePath.c_str());
	int nRet = m_objStreamPlayer.snapshot(strFilePath);
	if(nRet == 0)
	{
		CString path(strFilePath.c_str());
		CString cstr = _T("截图保存为：") + path;
		AfxMessageBox(cstr);
	}
	return nRet;
}

int PlayWindowDialog::startLocalRecord()
{
	std::string strFilePath = getCurrentFileDir() + "record_" + getTimeString() + ".h264";
	std::string path = "C:\\Users\\sun\\Desktop\\playerData_thread.h264";
	std::string path1 = getTimeString() + ".h264";
	//CLogOutputEx::instance().output(OT_FILE_VIEWER, LOG_INFO_HIT, "record file path : %s\n",strFilePath.c_str());
	return m_objStreamPlayer.startLocalRecord(path1);
}

void PlayWindowDialog::stopLocalRecord()
{
	m_objStreamPlayer.stopLocalRecord();
}

void PlayWindowDialog::getStreamInfoTest()
{
	std::string streamInfo_0 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_AUDIO_DOWNLOAD_SPEED);
	std::string streamInfo_1 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_VIDEO_DOWNLOAD_SPEED);
	std::string streamInfo_2 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_RATIO_HEIGHT);
	std::string streamInfo_3 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_RATIO_WIDTH);
	std::string streamInfo_4 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_VIDEO_FRAME_RATE);
	std::string streamInfo_5 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_AUDIO_FRAME_RATE);
	std::string streamInfo_6 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_VIDEO_AVERAGE_DOWNLOAD_SPEED);
	std::string streamInfo_7 = m_objStreamPlayer.getStreamInfo(LYCloud::STREAMINFO_AUDIO_AVERAGE_DOWNLOAD_SPEED);
// 	char out_put[1024] = {0};
// 	sprintf_s(out_put,"audio download speed:%s,video download speed:%s\n ratio height:%s,ratio width:%s\n video fps:%s,audio fps:%s\n avg video downlaod speed %s \n avg audio downlaod speed %s\n",
// 				0,streamInfo_1,streamInfo_2,streamInfo_3,streamInfo_4,0,streamInfo_6,0);
	CString s0(streamInfo_0.c_str());
	CString s1(streamInfo_1.c_str());
	CString s2(streamInfo_2.c_str());
	CString s3(streamInfo_3.c_str());
	CString s4(streamInfo_4.c_str());
	CString s5(streamInfo_5.c_str());
	CString s6(streamInfo_6.c_str());
	CString s7(streamInfo_7.c_str());
	CString cstr = _T("audio download speed: ") + s0 + _T("\nvideo download speed: ") + s1 + _T("\nratio height: ") + s2 + _T("\nratio width: ") + s3 + _T("\nvideo fps: ") + s4 + _T("\naudio fps: ") + s5 + _T("\navg video downlaod speed: ") + s6 + _T("\navg audio downlaod speed: ") + s7 ;
	AfxMessageBox(cstr);
}

