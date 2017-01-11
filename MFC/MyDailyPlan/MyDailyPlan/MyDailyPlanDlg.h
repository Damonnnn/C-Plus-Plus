
// MyDailyPlanDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"


// CMyDailyPlanDlg 对话框
class CMyDailyPlanDlg : public CDialogEx
{
// 构造
public:
	CMyDailyPlanDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYDAILYPLAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void delete_a_row(CListCtrl *m_list,int row,unsigned int column_to_be_update);
	void transfer_row_to_done_list(int row);
	void init_list_from_file(void);
	void save_list_to_file(void);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl daily_plan_list;
	CEdit daily_plan_add_plan_edit;
	afx_msg void OnBnClickedOk();
	afx_msg void OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl daily_plan_done_list;
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_temp_edit;
	afx_msg void OnEnKillfocusEdit2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonDone();
	afx_msg void OnBnClickedButtonUndone();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonClearAll();
	CDateTimeCtrl m_dateCtrl;
	afx_msg void OnBnClickedButton3();
	int my_year;
	int my_month;
	int my_day;
	afx_msg void OnBnClickedButtonMoveUp();
	afx_msg void OnBnClickedButtonMoveDown();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonForward();
};
