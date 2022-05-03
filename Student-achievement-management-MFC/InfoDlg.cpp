// InfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Student-achievement-management-MFC.h"
#include "InfoDlg.h"
#include "InfoFile.h"


// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(DIALOG_INFO)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CInfoDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// 设置扩展风格
	//LVS_EX_FULLROWSELECT选中整行，LVS_EX_GRIDLINES网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表头
	CString field[] = { _T("学号"), _T("姓名"), _T("语文成绩"), _T("数学成绩"), _T("英语成绩") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	CInfoFile file;
	file.ReadDocline(); //读取商品信息

	//添加数据
	int i = 0;
	CString str;
	for (list<CInfoFile::msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		int column = 0;
		m_list.InsertItem(i, str);
		m_list.SetItemText(i, column++, (CString)it->studentNumber.c_str());
		m_list.SetItemText(i, column++, (CString)it->studentName.c_str());
		str.Format(_T("%d"), it->gradeChinese);
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), it->gradeMath);
		m_list.SetItemText(i, column++, str);
		str.Format(_T("%d"), it->gradeEnglish);
		m_list.SetItemText(i, column++, str);
		i++;
	}


	// TODO: 在此添加专用代码和/或调用基类
}


void CInfoDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
