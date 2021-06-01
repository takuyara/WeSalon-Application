//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.


#include "pch.h"
#include "WeSalon.h"
#include "ViewDlg.h"
#include "afxdialogex.h"
#include "dbif.h"
#include "MoreAbout.h"


// ViewDlg 对话框

IMPLEMENT_DYNAMIC(ViewDlg, CDialogEx)

ViewDlg::ViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIEWOTHER, pParent)
{

}

ViewDlg::~ViewDlg()
{
}

void ViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDE_KEYWORD2, m_edit);
}


BEGIN_MESSAGE_MAP(ViewDlg, CDialogEx)
	ON_BN_CLICKED(IDB_FILTER2, &ViewDlg::OnBnClickedFilter2)
	ON_BN_CLICKED(IDB_MOREABOUT, &ViewDlg::OnBnClickedMoreabout)
	ON_BN_CLICKED(IDB_PARTICIPATE, &ViewDlg::OnBnClickedParticipate)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &ViewDlg::OnNMClickList2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, &ViewDlg::OnLvnColumnclickList2)
END_MESSAGE_MAP()


// ViewDlg 消息处理程序


BOOL ViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	capf.CreatePointFont(200, _T("Comic Sans MS"));
	butf1.CreatePointFont(120, _T("Comic Sans MS"));
	butf2.CreatePointFont(150, _T("Comic Sans MS"));
	textf.CreatePointFont(150, _T("Comic Sans MS"));
	listf.CreatePointFont(100, _T("Comic Sans MS"));
	GetDlgItem(IDS_OTHERACT)->SetFont(&capf);
	GetDlgItem(IDE_KEYWORD2)->SetFont(&textf);
	GetDlgItem(IDS_KEYWORD2)->SetFont(&textf);
	GetDlgItem(IDB_FILTER2)->SetFont(&butf1);
	GetDlgItem(IDB_MOREABOUT)->SetFont(&butf2);
	GetDlgItem(IDB_PARTICIPATE)->SetFont(&butf2);

	m_list.SetFont(&listf);
	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("Activity Name"), LVCFMT_LEFT, 160);
	m_list.InsertColumn(1, _T("Status"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("Start Time"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(3, _T("Finish Time"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(4, _T("Location"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T("Participants"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(6, _T("Role"), LVCFMT_LEFT, 100);
	sortid = -1;
	for (int i = 0; i < 7; ++i) stflg[i] = 1;

	GetActivity(_T(""), act, nact, false);
	InsertList(&m_list, act, nact);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ViewDlg::OnBnClickedFilter2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit.SetSel(0, -1);
	m_edit.GetWindowText(curkey);
	GetActivity(curkey, act, nact, false);
	InsertList(&m_list, act, nact);
}


void ViewDlg::OnBnClickedMoreabout()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL){
		MessageBox(_T("Please choose which to show more."));
		return ;
	}
	curact = act + m_list.GetNextSelectedItem(pos);
	
	//ShowWindow(SW_HIDE);
	MoreAbout *p = new MoreAbout();
	p->DoModal();
	delete p;
	//ShowWindow(SW_SHOW);
}


void ViewDlg::OnBnClickedParticipate()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL){
		MessageBox(_T("Please choose which to show more."));
		return ;
	}
	curact = act + m_list.GetNextSelectedItem(pos);
	if (curact->status != _T("Coming Soon")){
		MessageBox(_T("Cannot participate this activity now"));
		return ;
	}
	if (JoinInAct()){
		MessageBox(_T("Successfully participating activity: ") + curact->name);
		GetActivity(curkey, act, nact, false);
		InsertList(&m_list, act, nact);
	} else MessageBox(_T("Activity already full or time confliction."));
}


void ViewDlg::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL) return ;
	curact = act + m_list.GetNextSelectedItem(pos);
	
	GetDlgItem(IDB_PARTICIPATE)->
		EnableWindow(curact->role == "N/A");
	*pResult = 0;
}


void ViewDlg::OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	stflg[sortid = pNMLV->iSubItem] *= -1;
	int cnt = m_list.GetItemCount();
	for (int i = 0; i < cnt; ++i) m_list.SetItemData(i, i);
	m_list.SortItems((PFNLVCOMPARE)CompareFunc2, (LPARAM)this);
	*pResult = 0;
}
