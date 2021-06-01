//Pionniers du TJ, benissiez-moi par votre Esprits Saints!
//It rained on us at 4am.

#pragma once


// CChooseDlg 对话框

class CChooseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChooseDlg)

public:
	CChooseDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChooseDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOOSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CFont buttonf;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedManage();
	afx_msg void OnBnClickedFilter1();
	afx_msg void OnBnClickedViewother();
	afx_msg void OnBnClickedComment();
	afx_msg void OnClose();
	afx_msg void OnBnClickedQuit();
};
