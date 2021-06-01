#pragma once
#include "dbif.h"

// ViewDlg 对话框

class ViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ViewDlg)

public:
	ViewDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ViewDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWOTHER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CEdit m_edit;
	CString curkey;
	Activity act[MAX_ACT];
	int nact, sortid, stflg[20];
	CFont capf, butf1, butf2, textf, listf;
	afx_msg void OnBnClickedFilter2();
	afx_msg void OnBnClickedMoreabout();
	afx_msg void OnBnClickedParticipate();
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
};
