#pragma once
#include "MoveGenerator.h"
#include "Eveluation.h"

class CSearchEngine
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();
	// find a good move
	virtual int SearchAGoodMove(int position[10][9]) = 0;
	//set max searching depth
	void SetSearchDeepth(int nDepth) { m_nSearchDepth = nDepth; };
	//set evaluation engine
	void SetEveluator(CEveluation *pEval) { m_pEval = pEval; };
	//set move generator
	void SetMoveGenerator(CMoveGenerator *pMG) { m_pMG = pMG; };
protected:
	//the chessboard after a move generatea
	int MakeMove(CHESSMOVE * move);
	//reset the chessboard to the former one
	void UnMakeMove(CHESSMOVE * move, int type);
	// game over?
	int IsGameOver(int position[10][9], int nDepth);
	//current board state
	int CurPosition[10][9];
	CHESSMOVE m_cmBestMove;
	CMoveGenerator *m_pMG;
	CEveluation *m_pEval;
	int m_nSearchDepth; //max searching depth
	int m_nMaxDepth;// max depth of current search
};

