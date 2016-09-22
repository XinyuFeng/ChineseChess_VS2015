#include "stdafx.h"
#include "ChineseChess.h"
#include "FAlphaBetaEngine.h"


FAlphaBetaEngine::FAlphaBetaEngine()
{
}


FAlphaBetaEngine::~FAlphaBetaEngine()
{
}

int FAlphaBetaEngine::SearchAGoodMove(int position[10][9])
{
	memcpy(CurPosition, position, 360);
	m_nMaxDepth = m_nSearchDepth;
	FAlphaBeta(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 360);
	return 0;
}

int FAlphaBetaEngine::FAlphaBeta(int depth, int alpha, int beta)
{
	int current = -20000;
	int score;
	int Count, i;
	int type;
	i = IsGameOver(CurPosition, depth);
	if (i != 0)//game over
		return i;
	if (depth <= 0)
		return m_pEval->Eveluate(CurPosition, (m_nMaxDepth - depth) % 2);
	Count = m_pMG->CreatPossibleMove(CurPosition, depth, (m_nMaxDepth - depth) % 2);

	for (i = 0; i < Count; ++i)
	{
		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		score = -FAlphaBeta(depth - 1, -beta, -alpha);
		UnMakeMove(&m_pMG->m_MoveList[depth][i], type);
		if (score > current)
		{
			current = score;//save the maximum value
			if (depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			if (score >= alpha)
				alpha = score;
			if (score >= beta)
				break;//prun

		}
	}
	return current;
}