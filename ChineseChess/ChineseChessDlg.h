
// ChineseChessDlg.h : 头文件
//

#pragma once
#include "define.h"
#include "SearchEngine.h"
#include "NegaMaxEngine.h"

typedef struct _movechess
{
	int nChessID;
	POINT ptMovePoint;
}MOVECHESS;
// CChineseChessDlg 对话框
class CChineseChessDlg : public CDialog
{
// 构造
public:
	CChineseChessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHINESECHESS_DIALOG };
#endif

	CStatic m_OutputInfo;
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNewgame();
	DECLARE_MESSAGE_MAP()

private:
	int m_ChessBoard[10][9];
	int m_BackupChessBoard[10][9];//backup
	MOVECHESS m_MoveChess; //the chess currently be moved
	POINT m_ptMoveChess;//the posiion of currently chess
	CBitmap m_BoardBmp;// to show chessboard
	CImageList m_Chessman;//ImageList object to draw chess
	int m_nBoardWidth; //width of chessboard
	int m_nBoardHeight;//hight of chessboard
	CSearchEngine *m_pSE;// search engine ptr
};
