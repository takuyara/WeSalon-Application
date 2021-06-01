//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.

#include "pch.h"
#include "WeSalon.h"
#include "ManageDlg.h"
#include "afxdialogex.h"
#include "dbif.h"
#include "ModifyDlg.h"
#include "ApplyDlg.h"

// ManageDlg 对话框

IMPLEMENT_DYNAMIC(ManageDlg, CDialogEx)

ManageDlg::ManageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MANAGE, pParent)
{

}

ManageDlg::~ManageDlg()
{
}

void ManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDL_LIST1, m_list);
	DDX_Control(pDX, IDE_KEYWORD1, m_edit);
}


BEGIN_MESSAGE_MAP(ManageDlg, CDialogEx)
	ON_BN_CLICKED(IDB_FILTER1, &ManageDlg::OnBnClickedFilter1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDL_LIST1, &ManageDlg::OnLvnColumnclickList1)
	ON_BN_CLICKED(IDB_MODIFY, &ManageDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDB_DELETE, &ManageDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDB_APPLY, &ManageDlg::OnBnClickedApply)
	ON_NOTIFY(NM_CLICK, IDL_LIST1, &ManageDlg::OnNMClickList1)
END_MESSAGE_MAP()


// ManageDlg 消息处理程序


BOOL ManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	capf.CreatePointFont(200, _T("Comic Sans MS"));
	butf1.CreatePointFont(120, _T("Comic Sans MS"));
	butf2.CreatePointFont(150, _T("Comic Sans MS"));
	textf.CreatePointFont(150, _T("Comic Sans MS"));
	listf.CreatePointFont(100, _T("Comic Sans MS"));
	GetDlgItem(IDS_MYACT)->SetFont(&capf);
	GetDlgItem(IDE_KEYWORD1)->SetFont(&textf);
	GetDlgItem(IDS_KEYWORD1)->SetFont(&textf);
	GetDlgItem(IDB_FILTER1)->SetFont(&butf1);
	GetDlgItem(IDB_MODIFY)->SetFont(&butf2);
	GetDlgItem(IDB_DELETE)->SetFont(&butf2);
	GetDlgItem(IDB_APPLY)->SetFont(&butf2);

	m_list.SetFont(&listf);
	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | WS_VSCROLL | WS_HSCROLL);
	m_list.InsertColumn(0, _T("Activity Name"), LVCFMT_LEFT, 160);
	m_list.InsertColumn(1, _T("Status"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("Start Time"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(3, _T("Finish Time"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(4, _T("Location"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(5, _T("Participants"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(6, _T("Role"), LVCFMT_LEFT, 100);

	sortid = -1;
	for (int i = 0; i < 7; ++i) stflg[i] = 1;

	curkey = _T("");
	FlushList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void ManageDlg::FlushList(){
	GetActivity(curkey, act, nact, true);
	InsertList(&m_list, act, nact);
}

void ManageDlg::OnBnClickedFilter1(){
	// TODO: 在此添加控件通知处理程序代码
	m_edit.GetWindowText(curkey);
	FlushList();
}


void ManageDlg::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	stflg[sortid = pNMLV->iSubItem] *= -1;
	int cnt = m_list.GetItemCount();
	for (int i = 0; i < cnt; ++i) m_list.SetItemData(i, i);
	m_list.SortItems((PFNLVCOMPARE)CompareFunc1, (LPARAM)this);
	*pResult = 0;
}


void ManageDlg::OnBnClickedModify()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL){
		MessageBox(_T("Please choose which to modify."));
		return ;
	}
	curact = act + m_list.GetNextSelectedItem(pos);
	ShowWindow(SW_HIDE);
	ModifyDlg *p = new ModifyDlg();
	p->DoModal();
	delete p;
	ShowWindow(SW_SHOW);
	FlushList();
}


void ManageDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL){
		MessageBox(_T("Please choose which to delete."));
		return ;
	}
	curact = act + m_list.GetNextSelectedItem(pos);
	CString confirm;
	confirm = _T("Confirm delete activity: ") + curact->name;
	if (MessageBox(confirm, NULL, MB_OKCANCEL) == IDOK)
		curact->role == _T("Participant") ? QuitAct() : DeleteAct();
	FlushList();
}


void ManageDlg::OnBnClickedApply()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	ApplyDlg *p = new ApplyDlg();
	p->DoModal();
	delete p;
	ShowWindow(SW_SHOW);
	FlushList();
}


void ManageDlg::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL) return ;
	curact = act + m_list.GetNextSelectedItem(pos);
	if (curact->role == "Participant"){
		GetDlgItem(IDB_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDB_DELETE)->SetWindowText(_T("Quit"));
	}
	if (curact->role == "Holder"){
		GetDlgItem(IDB_MODIFY)->EnableWindow(TRUE);
		GetDlgItem(IDB_DELETE)->SetWindowText(_T("Call off"));
	}
	*pResult = 0;
}
