#include "stdafx.h"
#include "AlphaBetaEngine.h"
#include "ChineseChess.h"


CAlphaBetaEngine::CAlphaBetaEngine()
{
}


CAlphaBetaEngine::~CAlphaBetaEngine()
{
}


int CAlphaBetaEngine::SearchAGoodMove(int position[10][9])
{
	memcpy(CurPosition, position, 360); //copy current board to Curposition
	m_nMaxDepth = m_nSearchDepth;
	alphabeta(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 360);
	return 0;
}


int CAlphaBetaEngine::alphabeta(int depth, int alpha, int beta)
{
	int score;
	int Count, i;
	int type;
	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i;
	if (depth <= 0)
		return m_pEval->Eveluate(CurPosition, (m_nMaxDepth - depth) % 2);
	Count = m_pMG->CreatPossibleMove(CurPosition, depth, (m_nMaxDepth - depth) % 2);
	for (i = 0; i < Count; i++)
	{
		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		score = -alphabeta(depth - 1, -beta, -alpha);
		UnMakeMove(&m_pMG->m_MoveList[depth][i], type);
		if (score > alpha)
		{
			alpha = score;
			if (depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
		}
		if (alpha >= beta)
			break;//prun
	}
	return alpha;
}