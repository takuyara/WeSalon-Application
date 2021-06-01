//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.

#include "pch.h"
#include "WeSalon.h"
#include "ReplyAct.h"
#include "afxdialogex.h"
#include "dbif.h"


// ReplyAct 对话框

IMPLEMENT_DYNAMIC(ReplyAct, CDialogEx)

ReplyAct::ReplyAct(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REPLYACT, pParent)
{

}

ReplyAct::~ReplyAct()
{
}

void ReplyAct::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ReplyAct, CDialogEx)
	ON_BN_CLICKED(IDB_REPLYTRUE2, &ReplyAct::OnBnClickedReplytrue2)
END_MESSAGE_MAP()


// ReplyAct 消息处理程序


BOOL ReplyAct::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	editf.CreatePointFont(150, _T("Comic Sans MS"));
	butf.CreatePointFont(120, _T("Comic Sans MS"));

	GetDlgItem(IDS_REPLYTOWHICH)->SetFont(&editf);
	GetDlgItem(IDE_ACTNAME)->SetFont(&editf);
	GetDlgItem(IDE_REPLYCONTENT2)->SetFont(&butf);
	GetDlgItem(IDB_REPLYTRUE2)->SetFont(&editf);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ReplyAct::OnBnClickedReplytrue2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s, s1;
	GetDlgItem(IDE_REPLYCONTENT2)->GetWindowText(s);
	GetDlgItem(IDE_ACTNAME)->GetWindowText(s1);
	Reply crep;
	if (!FindAct(s1)){
		MessageBox(_T("No such activity"));
		return ;
	}
	crep.act = s1;
	crep.content = s;
	crep.replyto = -1;
	InsertReply(crep);
	MessageBox(_T("Reply established!"));
	CDialogEx::EndDialog(0);
}
