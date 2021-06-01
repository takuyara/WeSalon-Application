//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.

#include "pch.h"
#include "WeSalon.h"
#include "CChooseDlg.h"
#include "afxdialogex.h"
#include "ManageDlg.h"
#include "ViewDlg.h"
#include "CommentDlg.h"


// CChooseDlg 对话框

IMPLEMENT_DYNAMIC(CChooseDlg, CDialogEx)

CChooseDlg::CChooseDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHOOSE, pParent)
{
	
}

CChooseDlg::~CChooseDlg()
{
}

void CChooseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChooseDlg, CDialogEx)
	ON_BN_CLICKED(IDB_MANAGE, &CChooseDlg::OnBnClickedManage)
	ON_BN_CLICKED(IDB_VIEWOTHER, &CChooseDlg::OnBnClickedViewother)
	ON_BN_CLICKED(IDB_COMMENT, &CChooseDlg::OnBnClickedComment)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDB_QUIT, &CChooseDlg::OnBnClickedQuit)
END_MESSAGE_MAP()


// CChooseDlg 消息处理程序


BOOL CChooseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	buttonf.CreatePointFont(150, _T("Comic Sans MS"));
	GetDlgItem(IDB_MANAGE)->SetFont(&buttonf);
	GetDlgItem(IDB_VIEWOTHER)->SetFont(&buttonf);
	GetDlgItem(IDB_COMMENT)->SetFont(&buttonf);
	GetDlgItem(IDB_QUIT)->SetFont(&buttonf);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CChooseDlg::OnBnClickedManage()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	ManageDlg *dlg = new ManageDlg();
	dlg->DoModal();
	delete dlg;
	ShowWindow(SW_SHOW);
}

void CChooseDlg::OnBnClickedViewother()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	ViewDlg *dlg = new ViewDlg();
	dlg->DoModal();
	delete dlg;
	ShowWindow(SW_SHOW);
}


void CChooseDlg::OnBnClickedComment()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	CommentDlg *p = new CommentDlg();
	p->DoModal();
	delete p;
	ShowWindow(SW_SHOW);
}


void CChooseDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//MessageBox(_T("Onclose"));
	FinishConnection();
	CDialogEx::OnClose();
}


void CChooseDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	FinishConnection();
	EndDialog(0);
}
