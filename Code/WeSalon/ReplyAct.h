#pragma once


// ReplyAct 对话框

class ReplyAct : public CDialogEx
{
	DECLARE_DYNAMIC(ReplyAct)

public:
	ReplyAct(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ReplyAct();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPLYACT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont editf, butf;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedReplytrue2();
};
