#pragma once
#include "dbif.h"

// ManageDlg 对话框

class ManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ManageDlg)

public:
	ManageDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ManageDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MANAGE };
#endif

protected:
	CFont capf, butf1, butf2, textf, listf;
	void FlushList();
	CString curkey;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	afx_msg void OnBnClickedFilter1();
	CEdit m_edit;
	Activity act[MAX_ACT];
	int nact, sortid, stflg[20];
	afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedApply();
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
};
