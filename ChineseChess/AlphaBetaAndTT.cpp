#include "stdafx.h"
#include "AlphaBetaAndTT.h"
#include "ChineseChess.h"


CAlphaBetaAndTT::CAlphaBetaAndTT()
{
}


CAlphaBetaAndTT::~CAlphaBetaAndTT()
{
}


int CAlphaBetaAndTT::SearchAGoodMove(int position[10][9])
{
	memcpy(CurPosition, position, 360);
	CalculateInitHashKey(CurPosition);
	m_nMaxDepth = m_nSearchDepth;
	alphabeta(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 90);
}


int CAlphaBetaAndTT::alphabeta(int depth, int alpha, int beta)
{
	int score;
	int Count, i;
	int type;
	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i; //gameover
	score = LookUpHashTable(alpha, beta, depth, (m_nMaxDepth - depth) % 2);
	if (score != 66666)
		return score;
	if (depth <= 0)//leaf node
	{
		score = m_pEval->Eveluate(CurPosition, (m_nMaxDepth - depth) % 2);
		EnterHashTable(exact, score, depth, (m_nMaxDepth - depth) % 2);
		return score;
	}
	//get all possible move from current board
	Count = m_pMG->CreatPossibleMove(CurPosition, depth, (m_nMaxDepth - depth) % 2);
	int eval_is_exact = 0; //data type signal
	for (i = 0; i < Count; ++i)
	{
		Hash_MakeMove(&m_pMG->m_MoveList[depth][i], CurPosition);
		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		score = -alphabeta(depth - 1, -beta, -alpha);
		Hash_UnMakeMove(&m_pMG->m_MoveList[depth][i], type, CurPosition);
		UnMakeMove(&m_pMG->m_MoveList[depth][i], type);
		if (score >= beta)
		{//beta pruning
			EnterHashTable(lower_bound, score, depth, (m_nMaxDepth - depth) % 2);
			return score;
		}
		if (score > alpha)
		{
			alpha = score;
			eval_is_exact = 1;
			if (depth == m_nMaxDepth)
			{
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			}
		}

		if (eval_is_exact)
			EnterHashTable(exact, alpha, depth, (m_nMaxDepth - depth) % 2);
		else
			EnterHashTable(upper_bound, alpha, depth, (m_nMaxDepth - depth) % 2);

		return alpha;
	}

}