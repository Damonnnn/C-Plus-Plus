
// MyDailyPlanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDailyPlan.h"
#include "MyDailyPlanDlg.h"
#include "afxdialogex.h"
#include "HelpDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static unsigned int m_Row, m_Col;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyDailyPlanDlg 对话框



CMyDailyPlanDlg::CMyDailyPlanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYDAILYPLAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDailyPlanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, daily_plan_list);
	DDX_Control(pDX, IDC_EDIT1, daily_plan_add_plan_edit);
	DDX_Control(pDX, IDC_LIST1, daily_plan_done_list);
	DDX_Control(pDX, IDC_EDIT2, m_temp_edit);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_dateCtrl);
}

BEGIN_MESSAGE_MAP(CMyDailyPlanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDailyPlanDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDailyPlanDlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CMyDailyPlanDlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDOK, &CMyDailyPlanDlg::OnBnClickedOk)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CMyDailyPlanDlg::OnHdnItemclickList2)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CMyDailyPlanDlg::OnNMDblclkList2)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CMyDailyPlanDlg::OnEnKillfocusEdit2)
	ON_BN_CLICKED(IDC_BUTTON_DONE, &CMyDailyPlanDlg::OnBnClickedButtonDone)
	ON_BN_CLICKED(IDC_BUTTON_UNDONE, &CMyDailyPlanDlg::OnBnClickedButtonUndone)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CMyDailyPlanDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMyDailyPlanDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_ALL, &CMyDailyPlanDlg::OnBnClickedButtonClearAll)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDailyPlanDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_Move_Up, &CMyDailyPlanDlg::OnBnClickedButtonMoveUp)
	ON_BN_CLICKED(IDC_BUTTON_Move_Down, &CMyDailyPlanDlg::OnBnClickedButtonMoveDown)
END_MESSAGE_MAP()


// CMyDailyPlanDlg 消息处理程序

BOOL CMyDailyPlanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//init the list control
	CRect rect;
	daily_plan_list.GetClientRect(&rect);
	daily_plan_list.InsertColumn(0, _T("State"), LVCFMT_LEFT, 55);
	daily_plan_list.InsertColumn(1, _T("#"), LVCFMT_LEFT, 40);
	daily_plan_list.InsertColumn(2, _T("Items"), LVCFMT_LEFT, rect.Width()-55-40);
	daily_plan_list.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//

	daily_plan_done_list.GetClientRect(&rect);
	daily_plan_done_list.InsertColumn(0, _T("#"), LVCFMT_LEFT, 40);
	daily_plan_done_list.InsertColumn(2, _T("Items"), LVCFMT_LEFT, rect.Width()-40);
	daily_plan_done_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_temp_edit.ShowWindow(SW_HIDE);
	//init the timer control
	m_dateCtrl.SetFormat(_T("yyyy-MM-dd"));

	//update the time
	CTime m_date;
	m_dateCtrl.GetTime(m_date);
	my_year = m_date.GetYear();
	my_month = m_date.GetMonth();
	my_day = m_date.GetDay();

	init_list_from_file();



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyDailyPlanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == SC_CLOSE)
	{
		//你自己的代码 
		//MessageBox(_T("你点击了xx"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		save_list_to_file();
		CDialogEx::OnOK();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyDailyPlanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyDailyPlanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyDailyPlanDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString edit_str,temp_str;
	unsigned int total_rows = daily_plan_list.GetItemCount();
	temp_str.Format(TEXT("%u"), total_rows);
	daily_plan_add_plan_edit.GetWindowText(edit_str);
	daily_plan_add_plan_edit.SetWindowText(_T(""));
	if (edit_str.IsEmpty())
	{
		MessageBox(_T("请输入文字"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		return;
	}
	daily_plan_list.InsertItem(total_rows, _T(""));
	daily_plan_list.SetItemText(total_rows, 1, temp_str);
	daily_plan_list.SetItemText(total_rows, 2, edit_str);

}


void CMyDailyPlanDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nId,i;
	CString temp_str;
	POSITION pos = daily_plan_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请至少在\"Todolist\"中选择一项"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化 
	nId = (int)daily_plan_list.GetNextSelectedItem(pos);
	delete_a_row(&daily_plan_list,nId,1);
}


void CMyDailyPlanDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	

	*pResult = 0;
}


void CMyDailyPlanDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	//CMyDailyPlanDlg::OnBnClickedButton1();
}



void CMyDailyPlanDlg::OnHdnItemclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	
	*pResult = 0;
}

void CMyDailyPlanDlg::delete_a_row(CListCtrl *m_list, int row,unsigned int column_to_be_update)
{
	int  i;
	CString temp_str;
	unsigned int total_rows;

	m_list->DeleteItem(row);
	total_rows = m_list->GetItemCount();
	for (i = 0; i < total_rows; i++)
	{
		temp_str.Format(TEXT("%u"), i);
		m_list->SetItemText(i, column_to_be_update, temp_str);
	}
}

void CMyDailyPlanDlg::transfer_row_to_done_list(int row)
{
	//获取daily_plan_list的column 2的内容
	TCHAR szBuf[1024];
	CString temp_str;
	LVITEM lvi;
	lvi.iItem = row;
	lvi.iSubItem = 2;
	lvi.mask = LVIF_TEXT;
	lvi.pszText = szBuf;
	lvi.cchTextMax = 1024;
	daily_plan_list.GetItem(&lvi);

	//将获取到底内容插入到daily_plan_done_list
	unsigned int total_rows = daily_plan_done_list.GetItemCount();
	temp_str.Format(TEXT("%u"), total_rows);
	daily_plan_done_list.InsertItem(total_rows, temp_str);
	daily_plan_done_list.SetItemText(total_rows, 1, szBuf);
}

void CMyDailyPlanDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	CRect rc;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_Row = pNMListView->iItem;//获得选中的行  
	m_Col = pNMListView->iSubItem;//获得选中列  


	if (pNMListView->iSubItem == 2) //如果选择的是子项;  
	{
		daily_plan_list.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//获得子项的RECT；  
		m_temp_edit.SetParent(&daily_plan_list);//转换坐标为列表框中的坐标  
		m_temp_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;  
		m_temp_edit.SetWindowText(daily_plan_list.GetItemText(m_Row, m_Col));//将该子项中的值放在Edit控件中；  
		m_temp_edit.ShowWindow(SW_SHOW);//显示Edit控件；  
		m_temp_edit.SetFocus();//设置Edit焦点  
		m_temp_edit.ShowCaret();//显示光标  
		m_temp_edit.SetSel(-1);//将光标移动到最后  
		


	}
#if 0
	int nId, i;
	CString temp_str,plan_string;
	POSITION pos = daily_plan_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		//MessageBox(_T("你双击了"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化 
	nId = (int)daily_plan_list.GetNextSelectedItem(pos);
	plan_string = daily_plan_list.GetItemText(nId, 2);
	daily_plan_add_plan_edit.SetWindowText(plan_string);
#endif
	*pResult = 0;
}


void CMyDailyPlanDlg::OnEnKillfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tem;
	//POSITION pos = daily_plan_list.GetFirstSelectedItemPosition();
	//if (pos == NULL)
	//{
	//	MessageBox(_T("你悲剧了"), _T("Warning!!!"), MB_ICONEXCLAMATION);
	//	return;
	//}
	//得到行号，通过POSITION转化 
	//int nId;
	//nId = (int)daily_plan_list.GetNextSelectedItem(pos);
	m_temp_edit.GetWindowText(tem);    //得到用户输入的新的内容  
	daily_plan_list.SetItemText(m_Row, m_Col, tem);   //设置编辑框的新内容  
	m_temp_edit.ShowWindow(SW_HIDE);                //应藏编辑框  
}

BOOL CMyDailyPlanDlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		if (GetFocus() == GetDlgItem(IDC_EDIT1))  //根据不同控件焦点判断是那个在执行  
		{
			CMyDailyPlanDlg::OnBnClickedButton1();
			return TRUE; // return TRUE to avoid 键盘叮叮当声音
		}

		if (GetFocus() == GetDlgItem(IDC_EDIT2))  //根据不同控件焦点判断是那个在执行  
		{
			CMyDailyPlanDlg::OnEnKillfocusEdit2();
			return TRUE;
		}
 
	}
	else if (WM_CLOSE == pMsg->message)
	{
		MessageBox(_T("你点击了xx"), _T("Warning!!!"), MB_ICONEXCLAMATION);
	}
	return 0;
}


void CMyDailyPlanDlg::OnBnClickedButtonDone()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned int i = 0;
	int if_any_row_checked = 0;
	unsigned int total_rows = daily_plan_list.GetItemCount();
	while (i < total_rows)
	{
		if (daily_plan_list.GetCheck(i))
		{
			if_any_row_checked = 1;
			transfer_row_to_done_list(i);
			delete_a_row(&daily_plan_list,i,1);
			i = 0; //重新排了序，因此需要再轮一遍
			total_rows--;
		}
		else
		{
			i++;
		}

	}
	if (0 == if_any_row_checked)
	{
		MessageBox(_T("请至少标记一项任务为完成状态"), _T("Warning!!!"), MB_ICONEXCLAMATION);
	}
}


void CMyDailyPlanDlg::OnBnClickedButtonUndone()
{
	// TODO: 在此添加控件通知处理程序代码
	int nId, i;
	CString temp_str,item_string;
	POSITION pos = daily_plan_done_list.GetFirstSelectedItemPosition();
	unsigned int total_rows = daily_plan_list.GetItemCount();
	if (pos == NULL)
	{
		MessageBox(_T("请至少在\"Finished Task\"选择一项"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化 
	nId = (int)daily_plan_done_list.GetNextSelectedItem(pos);
	item_string = daily_plan_done_list.GetItemText(nId, 1);
	delete_a_row(&daily_plan_done_list, nId,0);
	//
	temp_str.Format(TEXT("%u"), total_rows);
	daily_plan_list.InsertItem(total_rows, _T(""));
	daily_plan_list.SetItemText(total_rows, 1, temp_str);
	daily_plan_list.SetItemText(total_rows, 2, item_string);

}


void CMyDailyPlanDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	CHelpDlg m_HelpDlg;
	m_HelpDlg.DoModal();
}


void CMyDailyPlanDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("你点击了exit"), _T("Warning!!!"), MB_ICONEXCLAMATION);
	save_list_to_file();
	CDialogEx::OnOK();
}

void CMyDailyPlanDlg::init_list_from_file(void)
{
	//init the row if ini file eists
	CFileFind   finder;
	CString record_file_name;

	//first, clear the list:
	daily_plan_list.DeleteAllItems();
	daily_plan_done_list.DeleteAllItems();

	record_file_name.Format(_T("record_%d-%d-%d.ini"), my_year, my_month, my_day);
	BOOL if_file_exist = finder.FindFile(record_file_name);
	if (if_file_exist)
	{
		WCHAR list_record_str[2048];
		WCHAR record_file_path[2048];
		CString record_file_path_with_name;
		CString temp_record_file_name;
		temp_record_file_name.Format(_T("\\record_%d-%d-%d.ini"), my_year, my_month, my_day);
		int total_row, i, j;
		
		GetCurrentDirectory(sizeof(record_file_path), record_file_path);
		record_file_path_with_name = record_file_path + temp_record_file_name;

		//init the todolist
		total_row = ::GetPrivateProfileInt(_T("TODOLIST"), _T("TotalRow"), 0, record_file_path_with_name);
		for (i = 0; i < total_row; i++)
		{
			CString temp_str;
			daily_plan_list.InsertItem(i, _T(""));
			for (j = 0; j < 3; j++)
			{
				temp_str.Format(_T("Row%dCol%d"), i, j);
				::GetPrivateProfileString(_T("TODOLIST"), temp_str, _T(""), list_record_str, sizeof(list_record_str), record_file_path_with_name);
				if (0 == j)
				{
					if ('1' == list_record_str[0])
					{
						daily_plan_list.SetCheck(i, 1);
					}
				}
				else
				{
					temp_str = list_record_str;
					daily_plan_list.SetItemText(i, j, temp_str);
				}

			}
		}

		//init the finish list
		total_row = ::GetPrivateProfileInt(_T("FINISHLIST"), _T("TotalRow"), 0, record_file_path_with_name);
		for (i = 0; i < total_row; i++)
		{
			CString temp_str;
			daily_plan_done_list.InsertItem(i, _T(""));
			for (j = 0; j < 2; j++)
			{
				temp_str.Format(_T("Row%dCol%d"), i, j);
				::GetPrivateProfileString(_T("FINISHLIST"), temp_str, _T(""), list_record_str, sizeof(list_record_str), record_file_path_with_name);
				temp_str = list_record_str;
				daily_plan_done_list.SetItemText(i, j, temp_str);


			}
		}
		//MessageBox(_T("dadada"), _T("Warning!!!"), MB_ICONEXCLAMATION);
	}
	else
	{
		CFile record_file(record_file_name, CFile::modeCreate);
	}
}
void CMyDailyPlanDlg::save_list_to_file(void)
{
	unsigned int total_rows;
	CString temp_str, temp_value_str;
	WCHAR record_file_path[2048];
	CString record_file_path_with_name;
	CString record_file_name;
	int total_row, i, j;
	GetCurrentDirectory(sizeof(record_file_path), record_file_path);
	
	record_file_name.Format(_T("\\record_%d-%d-%d.ini"), my_year, my_month, my_day);
	record_file_path_with_name = record_file_path + record_file_name;
	//first,clear the file
	CFile File;
	File.Open(record_file_path_with_name, CFile::modeCreate | CFile::modeWrite, NULL);
	File.Close();

	//save todolist
	total_rows = daily_plan_list.GetItemCount();
	temp_str.Format(_T("%d"), total_rows);
	::WritePrivateProfileString(_T("TODOLIST"), _T("TotalRow"),temp_str, record_file_path_with_name);
	for (i = 0; i < total_rows; i++)
	{
		for (j = 0; j < 3; j++)
		{
			temp_str.Format(_T("Row%dCol%d"), i, j);
			if (0 == j)
			{
				if (daily_plan_list.GetCheck(i))
				{
					temp_value_str.Format(_T("%d"),1);
				}
				else
				{
					temp_value_str.Format(_T("%d"),0);
				}
				
			}
			else
			{
				temp_value_str = daily_plan_list.GetItemText(i, j);				
			}
			::WritePrivateProfileString(_T("TODOLIST"), temp_str, temp_value_str, record_file_path_with_name);
			
		}
	}
	//save finish list
	total_rows = daily_plan_done_list.GetItemCount();
	temp_str.Format(_T("%d"), total_rows);
	::WritePrivateProfileString(_T("FINISHLIST"), _T("TotalRow"), temp_str, record_file_path_with_name);
	for (i = 0; i < total_rows; i++)
	{
		for (j = 0; j < 2; j++)
		{
			temp_str.Format(_T("Row%dCol%d"), i, j);
			temp_value_str = daily_plan_done_list.GetItemText(i, j);
			::WritePrivateProfileString(_T("FINISHLIST"), temp_str, temp_value_str, record_file_path_with_name);

		}
	}
}

void CMyDailyPlanDlg::OnBnClickedButtonClearAll()
{
	// TODO: 在此添加控件通知处理程序代码

	if (::MessageBox(NULL, _T("确定要清除所有内容吗？"),_T("清除所有内容"), MB_YESNO) == IDYES)
	{
		daily_plan_list.DeleteAllItems();
		daily_plan_done_list.DeleteAllItems();
	}
}


void CMyDailyPlanDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString record_file_name;
	CTime m_date;
	CFileFind   finder;
	m_dateCtrl.GetTime(m_date);
	//judge if file exist
	record_file_name.Format(_T("record_%d-%d-%d.ini"), m_date.GetYear(), m_date.GetMonth(), m_date.GetDay());
	BOOL if_file_exist = finder.FindFile(record_file_name);
	if (!if_file_exist)
	{
		MessageBox(_T("您所选择的日期没有记录"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		return;
	}
	//save current data
	save_list_to_file();
	//update the time
	my_year = m_date.GetYear();
	my_month = m_date.GetMonth();
	my_day = m_date.GetDay();
	//init data from file
	init_list_from_file();
	
}


void CMyDailyPlanDlg::OnBnClickedButtonMoveUp()
{
	// TODO: 在此添加控件通知处理程序代码
	int nId, i;
	CString temp_str;
	POSITION pos = daily_plan_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请至少在\"Todolist\"中选择一项"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化 
	nId = (int)daily_plan_list.GetNextSelectedItem(pos);
	if (nId != 0) 
	{
		//get the current row text.
		TCHAR szBuf_current[1024];
		LVITEM lvi_current;
		lvi_current.iItem = nId;
		lvi_current.iSubItem = 2;
		lvi_current.mask = LVIF_TEXT;
		lvi_current.pszText = szBuf_current;
		lvi_current.cchTextMax = 1024;
		daily_plan_list.GetItem(&lvi_current);
		//get the above row text.
		TCHAR szBuf_above[1024];
		LVITEM lvi_above;
		lvi_above.iItem = nId - 1;
		lvi_above.iSubItem = 2;
		lvi_above.mask = LVIF_TEXT;
		lvi_above.pszText = szBuf_above;
		lvi_above.cchTextMax = 1024;
		daily_plan_list.GetItem(&lvi_above);
		//exchange the two text.
		daily_plan_list.SetItemText(nId, 2, szBuf_above);
		daily_plan_list.SetItemText(nId-1, 2, szBuf_current);
		// update the selection focus
		daily_plan_list.SetItemState(nId - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}
}


void CMyDailyPlanDlg::OnBnClickedButtonMoveDown()
{
	// TODO: 在此添加控件通知处理程序代码
	int nId, i;
	CString temp_str;
	POSITION pos = daily_plan_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请至少在\"Todolist\"中选择一项"), _T("Warning!!!"), MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化 
	nId = (int)daily_plan_list.GetNextSelectedItem(pos);
	unsigned int total_rows = daily_plan_list.GetItemCount();
	if (nId < (total_rows-1))
	{
		//get the current row text.
		TCHAR szBuf_current[1024];
		LVITEM lvi_current;
		lvi_current.iItem = nId;
		lvi_current.iSubItem = 2;
		lvi_current.mask = LVIF_TEXT;
		lvi_current.pszText = szBuf_current;
		lvi_current.cchTextMax = 1024;
		daily_plan_list.GetItem(&lvi_current);
		//get the below row text.
		TCHAR szBuf_below[1024];
		LVITEM lvi_below;
		lvi_below.iItem = nId + 1;
		lvi_below.iSubItem = 2;
		lvi_below.mask = LVIF_TEXT;
		lvi_below.pszText = szBuf_below;
		lvi_below.cchTextMax = 1024;
		daily_plan_list.GetItem(&lvi_below);
		//exchange the two text.
		daily_plan_list.SetItemText(nId, 2, szBuf_below);
		daily_plan_list.SetItemText(nId + 1, 2, szBuf_current);
		// update the selection focus
		daily_plan_list.SetItemState(nId + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}
}
