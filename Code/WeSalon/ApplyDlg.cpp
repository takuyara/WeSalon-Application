//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.


#include "pch.h"
#include "WeSalon.h"
#include "ApplyDlg.h"
#include "afxdialogex.h"
#include "dbif.h"


// ApplyDlg 对话框

IMPLEMENT_DYNAMIC(ApplyDlg, CDialogEx)

ApplyDlg::ApplyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APPLY, pParent)
{

}

ApplyDlg::~ApplyDlg()
{
}

void ApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATUS2, m_sta);
	DDX_Control(pDX, IDE_NAME2, m_ename);
	DDX_Control(pDX, IDE_LOCATION2, m_eloca);
	DDX_Control(pDX, IDE_CAPACITY2, m_ecap);
	DDX_Control(pDX, IDE_DESC2, m_edesc);
	DDX_Control(pDX, IDT_STDATE2, m_std);
	DDX_Control(pDX, IDT_FNDATE2, m_fnd);
	DDX_Control(pDX, IDT_STTIME2, m_stt);
	DDX_Control(pDX, IDT_FNTIME2, m_fnt);
}


BEGIN_MESSAGE_MAP(ApplyDlg, CDialogEx)
	ON_BN_CLICKED(IDB_OK2, &ApplyDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDB_CANCEL2, &ApplyDlg::OnBnClickedCancel2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ApplyDlg 消息处理程序


BOOL ApplyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	textf.CreatePointFont(120, _T("Comic Sans MS"));
	GetDlgItem(IDS_NAME2)->SetFont(&textf);
	GetDlgItem(IDS_STATUS2)->SetFont(&textf);
	GetDlgItem(IDS_START2)->SetFont(&textf);
	GetDlgItem(IDS_FINISH2)->SetFont(&textf);
	GetDlgItem(IDS_LOCATION2)->SetFont(&textf);
	GetDlgItem(IDS_CAPACITY2)->SetFont(&textf);
	GetDlgItem(IDS_DESC2)->SetFont(&textf);
	GetDlgItem(IDE_NAME2)->SetFont(&textf);
	//GetDlgItem(IDE_START2)->SetFont(&textf);
	//GetDlgItem(IDE_FINISH2)->SetFont(&textf);
	GetDlgItem(IDE_LOCATION2)->SetFont(&textf);
	GetDlgItem(IDE_CAPACITY2)->SetFont(&textf);
	GetDlgItem(IDE_DESC2)->SetFont(&textf);
	GetDlgItem(IDB_OK2)->SetFont(&textf);
	GetDlgItem(IDB_CANCEL2)->SetFont(&textf);

	m_sta.AddString(_T("Voting"));
	m_sta.AddString(_T("Coming Soon"));
	m_sta.AddString(_T("Ongoing"));
	m_sta.AddString(_T("Finished"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ApplyDlg::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	Activity res;
	m_ename.GetWindowText(res.name);
	m_eloca.GetWindowText(res.loca);
	m_edesc.GetWindowText(res.desc);
	int t = m_sta.GetCurSel();
	if (t == 0) res.status = _T("Voting");
	if (t == 1) res.status = _T("Coming Soon");
	if (t == 2) res.status = _T("Ongoing");
	if (t == 3) res.status = _T("Finished");
	//CString tmp;
	//m_est.GetWindowText(tmp);
	/*
	if (!stoitrans(tmp, res.sttime)){
		MessageBox(_T("Start time must be a positive integer!"));
		return ;
	}
	//m_efn.GetWindowText(tmp);
	if (!stoitrans(tmp, res.fntime)){
		MessageBox(_T("Finish time must be a positive integer!"));
		return ;
	}
	*/
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
	/*
	CString r1;
	r1.Format(_T("%d, %d"), res.sttime, res.fntime);
	MessageBox(r1);
	*/
	CString tmp;
	m_ecap.GetWindowText(tmp);
	if (!stoitrans(tmp, res.maxnum)){
		MessageBox(_T("Capacity must be a positive integer!"));
		return ;
	}
	if (ApplyActivity(res)){
		MessageBox(_T("Apply success!"));
		CDialogEx::EndDialog(0);
	} else MessageBox(_T("Location is already occupied at that time. \r\nOr there maybe a name confliction."));
}



void ApplyDlg::OnBnClickedCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::EndDialog(0);
}




void ApplyDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}
