//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.

#include "pch.h"
#include "framework.h"
#include "WeSalon.h"
#include "WeSalonDlg.h"
#include "afxdialogex.h"
#include "dbif.h"
#include "CChooseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWeSalonDlg 对话框



CWeSalonDlg::CWeSalonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WESALON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWeSalonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWeSalonDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDB_LOGIN, &CWeSalonDlg::OnBnClickedLogin)
	ON_BN_CLICKED(IDB_REGISTER, &CWeSalonDlg::OnBnClickedRegister)
END_MESSAGE_MAP()


// CWeSalonDlg 消息处理程序

BOOL CWeSalonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Capfont.CreatePointFont(600, _T("Comic Sans MS"));
	Textfont.CreatePointFont(200, _T("Comic Sans MS"));
	GetDlgItem(IDS_CAPTAIN)->SetFont(&Capfont);
	GetDlgItem(IDS_USERNAME)->SetFont(&Textfont);
	GetDlgItem(IDS_PASSWORD)->SetFont(&Textfont);
	GetDlgItem(IDE_USERNAME)->SetFont(&Textfont);
	GetDlgItem(IDE_PASSWORD)->SetFont(&Textfont);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWeSalonDlg::OnPaint()
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
HCURSOR CWeSalonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWeSalonDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1, s2;
	GetDlgItem(IDE_USERNAME)->GetWindowText(s1);
	GetDlgItem(IDE_PASSWORD)->GetWindowText(s2);
	if (!LogIn(s1, s2)){
		MessageBox(_T("Wrong username or password"));
	} else {
		CChooseDlg *dlg = new CChooseDlg();
		ShowWindow(SW_HIDE);
		dlg->DoModal();
		delete dlg;
		//ShowWindow(SW_SHOW);
		CDialogEx::EndDialog(0);
	}
}


void CWeSalonDlg::OnBnClickedRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1, s2;
	GetDlgItem(IDE_USERNAME)->GetWindowText(s1);
	GetDlgItem(IDE_PASSWORD)->GetWindowText(s2);
	if (!Register(s1, s2)){
		MessageBox(_T("Username already exists"));
	} else {
		MessageBox(_T("Register successful!"));
		CChooseDlg *dlg = new CChooseDlg();
		ShowWindow(SW_HIDE);
		dlg->DoModal();
		delete dlg;
		//ShowWindow(SW_SHOW);
		CDialogEx::EndDialog(0);
	}
}

void CWeSalonDlg::OnClose(){
	//MessageBox(_T("Onclose"));
	FinishConnection();
	CDialogEx::OnClose();
}
