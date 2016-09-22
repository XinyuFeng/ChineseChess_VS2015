
// ChineseChessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChineseChess.h"
#include "ChineseChessDlg.h"
#include "afxdialogex.h"
#include "NewChess.h"
#include "MoveGenerator.h"
#include "iostream"
#include "AlphaBetaEngine.h"
#include "FAlphaBetaEngine.h"

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BORDERWIDTH 15//board(left/right)width
#define BORDERHEIGHT 14//board(up/down)height
#define GRILLEWIDTH 39//each grid's width
#define GRILLEHEIGHT 39//each grid's height

const int InitChessBoard[10][9] = 
{
	{B_CAR, B_HORSE, B_ELEPHANT, B_BISHOP, B_KING, B_BISHOP,B_ELEPHANT, B_HORSE, B_CAR},
	{NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS},
	{ NOCHESS, B_CANON, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, B_CANON, NOCHESS},
	{B_PAWN, NOCHESS, B_PAWN, NOCHESS, B_PAWN, NOCHESS, B_PAWN, NOCHESS, B_PAWN},
	{ NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS},
	{ NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS},
	{R_PAWN, NOCHESS, R_PAWN, NOCHESS, R_PAWN, NOCHESS, R_PAWN, NOCHESS, R_PAWN},
	{ NOCHESS, R_CANON, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, R_CANON, NOCHESS},
	{ NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS, NOCHESS},
	{R_CAR, R_HORSE, R_ELEPHANT, R_BISHOP, R_KING, R_BISHOP, R_ELEPHANT, R_HORSE, R_CAR}
};
///////////////////////////////////////////////////////////////////////////////////////

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


// CChineseChessDlg 对话框



CChineseChessDlg::CChineseChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CHINESECHESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChineseChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_NODECOUNT, m_OutputInfo);
}

BEGIN_MESSAGE_MAP(CChineseChessDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_NEWGAME, OnNewgame)
END_MESSAGE_MAP()


// CChineseChessDlg 消息处理程序

BOOL CChineseChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	m_Chessman.Create(IDB_CHESSMAN, 36, 14, RGB(0, 255, 0));
	//get board's weidth, height
	BITMAP BitMap;
	m_BoardBmp.LoadBitmapW(IDB_CHESSBOARD);
	m_BoardBmp.GetBitmap(&BitMap);
	m_nBoardWidth = BitMap.bmWidth;
	m_nBoardHeight = BitMap.bmHeight;
	cout << m_nBoardHeight;//debug
	m_BoardBmp.DeleteObject();
	memcpy(m_ChessBoard, InitChessBoard, 360);//init chessboard
	CMoveGenerator *pMG;
	CEveluation *pEvel;
	m_pSE = new CNegaMaxEngine;
	pMG = new CMoveGenerator;
	pEvel = new CEveluation;
	m_pSE->SetSearchDeepth(3);
	m_pSE->SetMoveGenerator(pMG);//set move generator for seasrch engine
	m_pSE->SetEveluator(pEvel);
	m_MoveChess.nChessID = NOCHESS;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CChineseChessDlg::OnPaint()
{
	CPaintDC dc(this);
	CDC MemDC;
	int i, j;
	POINT pt;
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(&dc);
	m_BoardBmp.LoadBitmapW(IDB_CHESSBOARD);
	pOldBmp = MemDC.SelectObject(&m_BoardBmp);
	for(i = 0; i < 10; i++)
		for (j = 0; j < 9; j++)
		{// draw chess
			if (m_ChessBoard[i][j] == NOCHESS)
				continue;
			pt.x = j*GRILLEHEIGHT + 14;
			pt.y = i*GRILLEWIDTH + 15;
			m_Chessman.Draw(&MemDC, m_ChessBoard[i][j] - 1, pt, ILD_TRANSPARENT);
		}
	// draw chess which the user is moving 
	if (m_MoveChess.nChessID != NOCHESS)
		m_Chessman.Draw(&MemDC, m_MoveChess.nChessID - 1, m_MoveChess.ptMovePoint, ILD_TRANSPARENT);
	// fresh those info to window
	dc.BitBlt(0, 0, m_nBoardWidth, m_nBoardHeight, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(&pOldBmp);// recover memory DC's map
	MemDC.DeleteDC();//release memory
	m_BoardBmp.DeleteObject();
}


void CChineseChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

/*void CChineseChessDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}*/

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChineseChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChineseChessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int x, y;
	// transform coordiation to the grid
	y = (point.y - 14) / GRILLEHEIGHT;
	x = (point.x - 15) / GRILLEWIDTH;
	// backup current board
	memcpy(m_BackupChessBoard, m_ChessBoard, 360);
	// iwhether mouse is in the board and clicked the red chess
	if (point.x > 0 && point.y > 0 && point.x < m_nBoardWidth && point.y < m_nBoardHeight && IsRed(m_ChessBoard[y][x]))
	{
		memcpy(m_BackupChessBoard, m_ChessBoard, 360);
		//update movechess
		m_ptMoveChess.x = x;
		m_ptMoveChess.y = y;
		m_MoveChess.nChessID = m_ChessBoard[y][x];
		//remove from its original position
		m_ChessBoard[m_ptMoveChess.y][m_ptMoveChess.x] = NOCHESS;
		//let chess's middle point be the position of mouse
		point.x -= 18;
		point.y -= 18;
		m_MoveChess.ptMovePoint = point;
		InvalidateRect(NULL, FALSE);//refresh window
		UpdateWindow();
		SetCapture();//mouse point

	}
	CDialog::OnLButtonDown(nFlags, point);
}


extern int count;// leaves number
void CChineseChessDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	BOOL bTurnSide = FALSE;
	int timecount;
	int x, y;
	y = (point.y - 14) / GRILLEHEIGHT;
	x = (point.x - 15) / GRILLEWIDTH;
	//wether the user is moving chess, and the moving is legal?
	if (m_MoveChess.nChessID && CMoveGenerator::IsValidMove(m_BackupChessBoard, m_ptMoveChess.x, m_ptMoveChess.y, x, y))
	{
		m_ChessBoard[y][x] = m_MoveChess.nChessID;
		bTurnSide = TRUE;
	}
	else
		memcpy(m_ChessBoard, m_BackupChessBoard, 360);
	//clear the moving chess
	m_MoveChess.nChessID = NOCHESS;
	//refrash window
	InvalidateRect(NULL, FALSE);
	UpdateWindow();
	//release mouse
	ReleaseCapture();
	if (bTurnSide == TRUE)
	{
		timecount = GetTickCount();
		m_pSE->SearchAGoodMove(m_ChessBoard);//the computer make move
		CString sNodeCount;
		//sNodeCount.Format("%d ms, %d Nodes were eveluated.", GetTickCount() - timecount, count);
		//sNodeCount.Format("%d ms. %d Nodes were eveluated.", GetTickCount() - timecount, count);

	}
	//count = 0;
	InvalidateRect(NULL, FALSE);
	UpdateWindow();
	CDialog::OnLButtonUp(nFlags, point);
}


void CChineseChessDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_MoveChess.nChessID)
	{
		//prevent moving chess outside the board
		if (point.x < 15)
			point.x = 15;
		if (point.y < 15)
			point.y = 15;
		if (point.x > m_nBoardWidth - 15)
			point.x = m_nBoardWidth - 15;
		if (point.y > m_nBoardHeight - 15)
			point.y = m_nBoardHeight - 15;
		// make the center of chess be the position of mouse
		point.x -= 18;
		point.y -= 18;
		m_MoveChess.ptMovePoint = point; //save the moving chess's coordination
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CChineseChessDlg::OnNewgame()
{
	CMoveGenerator *pMG;
	CEveluation *pEvel;
	NewChess newGameDlg;
	if (newGameDlg.DoModal() == IDOK)
	{//user makes a new choice
		if (m_pSE)
			delete m_pSE;//release old search engine
		switch (newGameDlg.GetSelectedEngine())
		{
		case 0:
			m_pSE = new CNegaMaxEngine;
			break;
		case 1:
			m_pSE = new FAlphaBetaEngine;
			break;
		default:
			m_pSE = new CNegaMaxEngine;
			break;
		}
		m_pSE->SetSearchDeepth(newGameDlg.GetSelectedPly());
		pEvel = new CEveluation;

	}
	else
		return;
	memcpy(m_ChessBoard, InitChessBoard, 360);
	m_MoveChess.nChessID = NOCHESS;
	pMG = new CMoveGenerator;
	m_pSE->SetMoveGenerator(pMG);
	m_pSE->SetEveluator(pEvel);
	InvalidateRect(NULL, FALSE);
	UpdateWindow();
}