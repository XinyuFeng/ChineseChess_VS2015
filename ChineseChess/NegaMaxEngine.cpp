#include "stdafx.h"
#include "NegaMaxEngine.h"
#include "ChineseChess.h"

CNegaMaxEngine::CNegaMaxEngine()
{
}


CNegaMaxEngine::~CNegaMaxEngine()
{
}

//find a best move
int CNegaMaxEngine::SearchAGoodMove(int position[10][9])
{
	// set the searching layer ---- m_nSearchDepth
	m_nMaxDepth = m_nSearchDepth;
	//copy the chess to curposition
	memcpy(CurPosition, position, 360);
	// use negamax engine
	NegaMax(m_nMaxDepth);
	// change the board state
	MakeMove(&m_cmBestMove);
	// copy the changed board to position
	memcpy(position, CurPosition, 360);
	return 0;
}

//depth: the distance between leaf node and current node
int CNegaMaxEngine::NegaMax(int depth)
{
	int current = -20000;
	int score;
	int Count, i;
	int type;
	i = IsGameOver(CurPosition, depth);//is over?
	if (i != 0)
		return i;
	if (depth <= 0)// reach the leaf, return eveluation
		return m_pEval->Eveluate(CurPosition, (m_nMaxDepth - depth) % 2);
	// enumerate all possible move from now
	Count = m_pMG->CreatPossibleMove(CurPosition, depth, (m_nMaxDepth - depth) % 2);
	for (i = 0; i < Count; ++i)
	{
		// make new board state according to move
		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		// search nodes of next layer
		score = -NegaMax(depth - 1);
		// recover
		UnMakeMove(&m_pMG->m_MoveList[depth][i], type);
		if (score > current)
		{
			current = score;
			if (depth == m_nMaxDepth)
			{
				//save the best move at each root
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			}
		}
	}
	return current;


}
