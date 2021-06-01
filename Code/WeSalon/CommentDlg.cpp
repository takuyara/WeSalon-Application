//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.


#include "pch.h"
#include "WeSalon.h"
#include "CommentDlg.h"
#include "afxdialogex.h"
#include "ReplyDlg.h"
#include "ReplyAct.h"
#include "dbif.h"


// CommentDlg 对话框

IMPLEMENT_DYNAMIC(CommentDlg, CDialogEx)

CommentDlg::CommentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COMMENT, pParent){

}

CommentDlg::~CommentDlg(){}

void CommentDlg::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDE_COMMENT, m_ecomment);
}


BEGIN_MESSAGE_MAP(CommentDlg, CDialogEx)
	ON_BN_CLICKED(IDB_REPLY, &CommentDlg::OnBnClickedReply)
	ON_BN_CLICKED(IDB_REPLYTOACT, &CommentDlg::OnBnClickedReplytoact)
	ON_BN_CLICKED(IDB_PREV, &CommentDlg::OnBnClickedPrev)
	ON_BN_CLICKED(IDB_NEXT, &CommentDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDB_SEARCH, &CommentDlg::OnBnClickedSearch)
END_MESSAGE_MAP()


// CommentDlg 消息处理程序


BOOL CommentDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	capf.CreatePointFont(250, _T("Comic Sans MS"));
	bgbutf.CreatePointFont(180, _T("Comic Sans MS"));
	smbutf.CreatePointFont(150, _T("Comic Sans MS"));
	textf.CreatePointFont(120, _T("Comic Sans MS"));

	GetDlgItem(IDS_COMMENT)->SetFont(&capf);
	GetDlgItem(IDE_KEYWORD3)->SetFont(&bgbutf);
	GetDlgItem(IDB_SEARCH)->SetFont(&bgbutf);
	GetDlgItem(IDE_COMMENT)->SetFont(&textf);
	GetDlgItem(IDB_PREV)->SetFont(&smbutf);
	GetDlgItem(IDB_NEXT)->SetFont(&smbutf);
	GetDlgItem(IDB_REPLY)->SetFont(&smbutf);
	GetDlgItem(IDB_REPLYTOACT)->SetFont(&smbutf);

	curkey = _T("");
	GetReplies(curkey, rep, nrep);
	curid = 0;
	DrawReply();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CommentDlg::DrawReply(){
	CString s = nrep ? GetRepStr(rep + curid) : _T("No replies");
	m_ecomment.SetWindowText(s);
}

void CommentDlg::OnBnClickedReply(){
	// TODO: 在此添加控件通知处理程序代码
	if (!nrep){
		MessageBox(_T("No comments to reply"));
		return ;
	}
	curreply = rep + curid;
	//ShowWindow(SW_HIDE);
	ReplyDlg *p = new ReplyDlg();
	p->DoModal();
	delete p;
	//ShowWindow(SW_SHOW);
	GetReplies(curkey, rep, nrep);
	DrawReply();
}


void CommentDlg::OnBnClickedReplytoact(){
	// TODO: 在此添加控件通知处理程序代码
	//ShowWindow(SW_HIDE);
	ReplyAct *p = new ReplyAct();
	p->DoModal();
	delete p;
	//ShowWindow(SW_SHOW);
	GetReplies(curkey, rep, nrep);
	DrawReply();
}

void CommentDlg::OnBnClickedPrev(){
	// TODO: 在此添加控件通知处理程序代码
	if (nrep) curid = (curid + nrep - 1) % nrep;
	DrawReply();
}

void CommentDlg::OnBnClickedNext(){
	// TODO: 在此添加控件通知处理程序代码
	if (nrep) curid = (curid + 1) % nrep;
	DrawReply();
}

void CommentDlg::OnBnClickedSearch(){
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDE_KEYWORD3)->GetWindowText(curkey);
	GetReplies(curkey, rep, nrep);
	DrawReply();
}
