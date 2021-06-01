//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.


#include "pch.h"
#include "WeSalon.h"
#include "MoreAbout.h"
#include "afxdialogex.h"
#include "dbif.h"


// MoreAbout 对话框

IMPLEMENT_DYNAMIC(MoreAbout, CDialogEx)

MoreAbout::MoreAbout(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOREABOUT, pParent)
{

}

MoreAbout::~MoreAbout()
{
}

void MoreAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MoreAbout, CDialogEx)
END_MESSAGE_MAP()


// MoreAbout 消息处理程序


BOOL MoreAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	textf.CreatePointFont(120, _T("Comic Sans MS"));
	GetDlgItem(IDE_MTITLE)->SetFont(&textf);
	GetDlgItem(IDE_MDESC)->SetFont(&textf);
	GetDlgItem(IDE_MTITLE)->SetWindowText(GetTitle());
	GetDlgItem(IDE_MDESC)->SetWindowText(GetDesc());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
