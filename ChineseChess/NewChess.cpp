// NewChess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChineseChess.h"
#include "NewChess.h"
#include "afxdialogex.h"
#include "iostream"
using namespace std;

// NewChess �Ի���

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


// NewChess ��Ϣ�������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void NewChess::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void NewChess::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nSelectedEngine = m_SearchEngineList.GetCurSel();

	//m_nSelectedPly = m_SetPly.GetPos();
	CDialog::OnOK();
}


