#pragma once


// MoreAbout 对话框

class MoreAbout : public CDialogEx
{
	DECLARE_DYNAMIC(MoreAbout)

public:
	MoreAbout(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MoreAbout();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOREABOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont textf;
	virtual BOOL OnInitDialog();
};
