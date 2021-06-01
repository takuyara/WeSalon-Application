//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.


#include "pch.h"
#include "WeSalon.h"
#include "ReplyDlg.h"
#include "afxdialogex.h"
#include "dbif.h"


// ReplyDlg 对话框

IMPLEMENT_DYNAMIC(ReplyDlg, CDialogEx)

ReplyDlg::ReplyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REPLY, pParent)
{

}

ReplyDlg::~ReplyDlg()
{
}

void ReplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ReplyDlg, CDialogEx)
	ON_BN_CLICKED(IDB_REPLYTRUE1, &ReplyDlg::OnBnClickedReplytrue1)
END_MESSAGE_MAP()


// ReplyDlg 消息处理程序


BOOL ReplyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	editf.CreatePointFont(150, _T("Comic Sans MS"));
	butf.CreatePointFont(120, _T("Comic Sans MS"));

	GetDlgItem(IDS_REPLYTOWHOM)->SetFont(&editf);
	GetDlgItem(IDE_REPLYCONTENT1)->SetFont(&butf);
	GetDlgItem(IDB_REPLYTRUE1)->SetFont(&editf);
	GetDlgItem(IDS_REPLYTOWHOM)->SetWindowText(GetReplyString());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ReplyDlg::OnBnClickedReplytrue1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	GetDlgItem(IDE_REPLYCONTENT1)->GetWindowText(s);
	Reply crep;
	crep.act = curreply->act;
	crep.content = s;
	crep.replyto = curreply->uuid;
	InsertReply(crep);
	MessageBox(_T("Reply established!"));
	CDialogEx::EndDialog(0);
}
