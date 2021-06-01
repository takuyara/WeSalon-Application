//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.


#include "pch.h"
#include "WeSalon.h"
#include "ModifyDlg.h"
#include "afxdialogex.h"
#include "dbif.h"


// ModifyDlg 对话框

IMPLEMENT_DYNAMIC(ModifyDlg, CDialogEx)

ModifyDlg::ModifyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODIFY, pParent)
{

}

ModifyDlg::~ModifyDlg()
{
}

void ModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS1, m_sta);
	DDX_Control(pDX, IDE_NAME1, m_ename);
	DDX_Control(pDX, IDE_LOCATION1, m_eloca);
	DDX_Control(pDX, IDE_CAPACITY1, m_ecap);
	DDX_Control(pDX, IDE_DESC1, m_edesc);
	DDX_Control(pDX, IDT_STDATE1, m_std);
	DDX_Control(pDX, IDT_STTIME1, m_stt);
	DDX_Control(pDX, IDT_FNDATE1, m_fnd);
	DDX_Control(pDX, IDT_FNTIME1, m_fnt);
}


BEGIN_MESSAGE_MAP(ModifyDlg, CDialogEx)
	ON_BN_CLICKED(IDB_OK1, &ModifyDlg::OnBnClickedOk1)
	ON_BN_CLICKED(IDB_CANCEL1, &ModifyDlg::OnBnClickedCancel1)
END_MESSAGE_MAP()


// ModifyDlg 消息处理程序


BOOL ModifyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	textf.CreatePointFont(120, _T("Comic Sans MS"));
	GetDlgItem(IDS_NAME1)->SetFont(&textf);
	GetDlgItem(IDS_STATUS1)->SetFont(&textf);
	GetDlgItem(IDS_START1)->SetFont(&textf);
	GetDlgItem(IDS_FINISH1)->SetFont(&textf);
	GetDlgItem(IDS_LOCATION1)->SetFont(&textf);
	GetDlgItem(IDS_CAPACITY1)->SetFont(&textf);
	GetDlgItem(IDS_DESC1)->SetFont(&textf);
	GetDlgItem(IDE_NAME1)->SetFont(&textf);
	GetDlgItem(IDE_LOCATION1)->SetFont(&textf);
	GetDlgItem(IDE_CAPACITY1)->SetFont(&textf);
	GetDlgItem(IDE_DESC1)->SetFont(&textf);
	GetDlgItem(IDB_OK1)->SetFont(&textf);
	GetDlgItem(IDB_CANCEL1)->SetFont(&textf);

	m_sta.AddString(_T("Voting"));
	m_sta.AddString(_T("Coming Soon"));
	m_sta.AddString(_T("Ongoing"));
	m_sta.AddString(_T("Finished"));
	
	CString s;
	GetDlgItem(IDE_NAME1)->SetWindowText(curact->name);
	GetDlgItem(IDE_LOCATION1)->SetWindowText(curact->loca);
	s.Format(_T("%d"), curact->maxnum);
	GetDlgItem(IDE_CAPACITY1)->SetWindowText(s);
	GetDlgItem(IDE_DESC1)->SetWindowText(curact->desc);
	CTime stt = lltotime(curact->sttime), fnt = lltotime(curact->fntime);
	m_std.SetTime(&stt), m_stt.SetTime(&stt);
	m_fnd.SetTime(&fnt), m_fnt.SetTime(&fnt);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ModifyDlg::OnBnClickedOk1()
{
	// TODO: 在此添加控件通知处理程序代码
	Activity res;
	m_ename.GetWindowText(res.name);
	m_eloca.GetWindowText(res.loca);
	m_edesc.GetWindowText(res.desc);
	int t = m_sta.GetCurSel();
	m_sta.GetWindowText(res.status);
	CString tmp;
	CTime sttime, stdate, fntime, fndate;
	m_std.GetTime(stdate), m_stt.GetTime(sttime);
	m_fnd.GetTime(fndate), m_fnt.GetTime(fntime);
	if (stdate.GetYear() < 2020 || fndate.GetYear() < 2020){
		MessageBox(_T("Date is too early xD"));
		return ;
	}
	res.sttime = timetoll(stdate, sttime);
	res.fntime = timetoll(fndate, fntime);
	if (res.sttime > res.fntime){
		MessageBox(_T("Start time must smaller than finish time!"));
		return ;
	}
	m_ecap.GetWindowText(tmp);
	if (!stoitrans(tmp, res.maxnum)){
		MessageBox(_T("Capacity must be a positive integer!"));
		return ;
	}
	if (res.maxnum > curact->maxnum){
		MessageBox(_T("Capacity can only be enlarged!"));
		return ;
	}
	if (ModifyActivity(res)){
		MessageBox(_T("Modify success!"));
		CDialogEx::EndDialog(0);
	}
	else MessageBox(_T("Location is already occupied at that time."));
	
}


void ModifyDlg::OnBnClickedCancel1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::EndDialog(0);
}
