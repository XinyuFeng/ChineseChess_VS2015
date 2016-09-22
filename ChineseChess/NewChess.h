#pragma once


// NewChess �Ի���

class NewChess : public CDialog
{
	DECLARE_DYNAMIC(NewChess)

public:
	NewChess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NewChess();
	int GetSelectedEngine() { return m_nSelectedEngine; };
	int GetSelectedPly() { return m_nSelectedPly; };

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWCHESS };
#endif
	CSpinButtonCtrl m_SetPly;
	CListBox m_SearchEngineList;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	int m_nSelectedEngine;
	int m_nSelectedPly;
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	//afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	//afx_msg void OnBnClickedNewgame();
	//afx_msg void OnDeltaposSel(NMHDR *pNMHDR, LRESULT *pResult);
};
