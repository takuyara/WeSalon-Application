#pragma once


// ModifyDlg 对话框

class ModifyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyDlg)

public:
	ModifyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ModifyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont textf;
	virtual BOOL OnInitDialog();
	CComboBox m_sta;
	CEdit m_ename;
	CEdit m_est;
	CEdit m_efn;
	CEdit m_eloca;
	CEdit m_ecap;
	CEdit m_edesc;
	afx_msg void OnBnClickedOk1();
	afx_msg void OnBnClickedCancel1();
	CDateTimeCtrl m_std;
	CDateTimeCtrl m_stt;
	CDateTimeCtrl m_fnd;
	CDateTimeCtrl m_fnt;
};
