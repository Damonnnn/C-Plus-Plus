// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDailyPlan.h"
#include "HelpDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HELP_DIALOG, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_HELP, mEditHelp);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_THANKS, &CHelpDlg::OnBnClickedButtonThanks)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序
BOOL CHelpDlg::OnInitDialog()
{
	//read readme.txt and show it 
	//CFileFind   finder;
	CString  str;
	//CString readme;
	//CFile f;
	//check if file exist
	//readme.Format(_T("readme.txt"));
	//mEditHelp.Clear();
	//BOOL if_file_exist = finder.FindFile(readme);
	//if (if_file_exist)
	//{
		//MessageBox(_T("dadada"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		//f.Open(readme, CFile::modeRead);
		//f.Read(str.GetBuffer(f.GetLength()), f.GetLength());
		//f.Close();
	//}
	str.Format(_T("\
Thanks for using MyDailyPlan.\n\
Usage:\n  \
	1. Click \"Add\" or just press enter to add plan.\n \
	2. Click \"Delete\" to a delete plan.\n \
	3. Click \"Clear All\" to clear all plans.\n \
	4. Click \"Up\" or \"Down\" to order your plans.\n \
	5. Click \"-->>\" to move an item to finished task.\n \
	6. Click \"<<--\" to move an finished task back to ToDoList.\n \
	7. select the date to show your plans of a specific date.\n \
	8. Click the left arrow or right arrow to check your plans day by day.\n \
	9. Click \"Help\" to show this massage.\n \
	10. Click \"Exit\" to exit this application.\n \
    \n\
    \n\
    \n\
请记住，自己写下的计划，哭着也得完成。"
	));
	GetDlgItem(IDC_STATIC_HELP)->SetWindowText(str);
	return FALSE;
}

void CHelpDlg::OnBnClickedButtonThanks()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
