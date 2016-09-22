// NewChess.cpp : 实现文件
//

#include "stdafx.h"
#include "ChineseChess.h"
#include "NewChess.h"
#include "afxdialogex.h"
#include "iostream"
using namespace std;

// NewChess 对话框

IMPLEMENT_DYNAMIC(NewChess, CDialog)

NewChess::NewChess(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_NEWCHESS, pParent)
{

}

NewChess::~NewChess()
{
}

void NewChess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_PLY, m_SetPly);
	DDX_Control(pDX, IDC_LISTENGINE, m_SearchEngineList);
}


BEGIN_MESSAGE_MAP(NewChess, CDialog)
	ON_LBN_SELCHANGE(IDC_LISTENGINE, &NewChess::OnLbnSelchangeList1)
	//ON_NOTIFY(UDN_DELTAPOS, IDC_PLY, &NewChess::OnDeltaposSpin1)
	//ON_EN_CHANGE(IDC_EDIT1, &NewChess::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_OK, &NewChess::OnBnClickedOk)
	//ON_BN_CLICKED(IDC_NEWGAME, &NewChess::OnBnClickedNewgame)
	//ON_NOTIFY(UDN_DELTAPOS, IDC_SEL, &NewChess::OnDeltaposSel)
END_MESSAGE_MAP()


// NewChess 消息处理程序
void NewChess::OnOK()
{
	m_nSelectedEngine = m_SearchEngineList.GetCurSel();
	//m_nSelectedEngine = 0;
	//m_nSelectedPly = m_SetPly.GetPos();
	m_nSelectedPly = 4;
	CDialog::OnOK();
}

BOOL NewChess::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_SearchEngineList.AddString(_T("AlphaBeta Search Engine"));
	//TCHAR *str = _T("Negamax Seach Engine");
	//LPCTSTR lp = str;
	m_SearchEngineList.AddString(_T("A Negamax Seach Engine"));
	m_SearchEngineList.AddString(_T("B lphaBeta Search Engine"));
	m_SearchEngineList.SetCurSel(0);
	//m_SetPly.SetRange(1, 15);
	//m_SetPly.SetPos(3);
	return TRUE;
}


void NewChess::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}



void NewChess::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void NewChess::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nSelectedEngine = m_SearchEngineList.GetCurSel();

	//m_nSelectedPly = m_SetPly.GetPos();
	CDialog::OnOK();
}


