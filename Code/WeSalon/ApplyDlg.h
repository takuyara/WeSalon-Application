#pragma once


// ApplyDlg 对话框

class ApplyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ApplyDlg)

public:
	ApplyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ApplyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont textf;
	virtual BOOL OnInitDialog();
	CComboBox m_sta;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancel2();
	CEdit m_ename;
	CEdit m_eloca;
	CEdit m_ecap;
	CEdit m_edesc;
	CDateTimeCtrl m_std;
	CDateTimeCtrl m_fnd;
	CDateTimeCtrl m_stt;
	CDateTimeCtrl m_fnt;
	afx_msg void OnClose();
};
