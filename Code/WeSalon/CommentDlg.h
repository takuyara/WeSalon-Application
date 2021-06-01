#pragma once
#include "dbif.h"

// CommentDlg 对话框

class CommentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CommentDlg)

public:
	CommentDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CommentDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CFont capf, bgbutf, smbutf, textf;
	Reply rep[MAX_REP];
	int curid, nrep;
	CString curkey;
	void DrawReply();
	afx_msg void OnBnClickedReply();
	afx_msg void OnBnClickedReplytoact();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedNext();
	CEdit m_ecomment;
	afx_msg void OnBnClickedSearch();
};
