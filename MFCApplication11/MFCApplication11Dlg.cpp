
// MFCApplication11Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication11.h"
#include "MFCApplication11Dlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHOWTASK (WM_USER+200) //注意n换成数字，n的大小应大于100

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CString program;


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication11Dlg 对话框



CMFCApplication11Dlg::CMFCApplication11Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION11_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication11Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication11Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication11Dlg::OnBnClickedButton3)

	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication11Dlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_MESSAGE(WM_SHOWTASK, &CMFCApplication11Dlg::OnShowtask)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication11Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication11Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()

afx_msg LRESULT CMFCApplication11Dlg::OnShowtask(WPARAM wParam, LPARAM lParam)
{

	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu();//声明一个弹出式菜单


		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭")); //增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this); //确定弹出式菜单的位置
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu(); //资源回收
		delete lpoint;
	} break;
	case WM_LBUTTONDBLCLK: //双击左键的处理
	{
		this->ShowWindow(SW_SHOW);//简单的显示主窗口完事儿
		DeleteTray();
	} break;
	default: break;
	}

	return 0;
}

// CMFCApplication11Dlg 消息处理程序

BOOL CMFCApplication11Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication11Dlg::OnPaint()
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
HCURSOR CMFCApplication11Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void KillProcess(CString sExeName)
{
	HANDLE hSnapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == 0)
		return;
	PROCESSENTRY32 thePE;
	thePE.dwSize = sizeof(PROCESSENTRY32);


	//遍历正在运行的第一个系统进程


	bool Status = Process32First(hSnapShot, &thePE);
	bool bHaveFlag = false;
	DWORD ProcessID = 0;


	while (Status)
	{
		//遍历正在运行的下一个系统进程  
		Status = Process32Next(hSnapShot, &thePE);
		//找到相应的进程 **.exe


		// if(0 == wcscmp(thePE.szExeFile,L""))
		CString sFindName = thePE.szExeFile;
		CString sTemp = sExeName.Mid(0, sFindName.GetLength());


		if (sFindName == sTemp)
		{
			bHaveFlag = true;
			ProcessID = thePE.th32ProcessID;


			//结束指定的进程 ProcessID
			if (!TerminateProcess(OpenProcess(PROCESS_TERMINATE || PROCESS_QUERY_INFORMATION, false, ProcessID), 0))
			{
				//AfxMessageBox(L"无法终止指定的进程！", MB_ICONWARNING || MB_OK);
			}
			else
			{
				//AfxMessageBox(L"进程结束！", MB_ICONWARNING || MB_OK);
				break;
			}
		}
	}
	CloseHandle(hSnapShot);
}

void CMFCApplication11Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	KillProcess(program);
}
#define TOOLTIPS_NAME_	"XXXX"
//最小化到托盘函数

void CMFCApplication11Dlg::ToTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(nid.szTip, _T(TOOLTIPS_NAME_)); //信息提示条
	Shell_NotifyIcon(NIM_ADD, &nid); //在托盘区添加图标
	ShowWindow(SW_HIDE); //隐藏主窗口
}
#define TOOLTIPS_NAME_	"YANG Remind"

//删除托盘图标函数
void CMFCApplication11Dlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK; //自定义的消息名称
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(nid.szTip, _T(TOOLTIPS_NAME_)); //信息提示条为“计划任务提醒”
	Shell_NotifyIcon(NIM_DELETE, &nid); //在托盘区删除图标
}








void CMFCApplication11Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	ToTray();
}

#define TM_MSG 10000

void CMFCApplication11Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == TM_MSG)
	{
		//具体实现
		KillProcess(program);
		SendMessage(WM_CLOSE);
		CDialogEx::OnTimer(TM_MSG);
	}
}

void CMFCApplication11Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int time;
	CString time1;
	GetDlgItem(IDC_EDIT2)->GetWindowText(time1);
	time = _ttoi(time1);
		time = time * 60000;
	SetTimer(TM_MSG, time, NULL);
}


UINT  ThreadFunc(LPVOID  lParam)
{
	
	while (true) {
		KillProcess(program);
		Sleep(1000);
	}
}

void CMFCApplication11Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(ThreadFunc, (LPVOID)this);//启动新的线程
}


void CMFCApplication11Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(program);

}
