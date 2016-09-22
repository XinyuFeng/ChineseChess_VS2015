#include "stdafx.h"
#include "SearchEngine.h"


CSearchEngine::CSearchEngine()
{
}


CSearchEngine::~CSearchEngine()
{
	delete m_pMG;
	delete m_pEval;
}

//change the board according the move
int CSearchEngine::MakeMove(CHESSMOVE *move)
{
	int nChessID;
	nChessID = CurPosition[move->To.y][move->To.x];//get the chess of target position
	//move chess to target position
	CurPosition[move->To.y][move->To.x] = CurPosition[move->From.y][move->From.x];
	// clear the original position
	CurPosition[move->From.y][move->From.x] = NOCHESS;
	return nChessID; //return the chess eated
}

// recover the board
void CSearchEngine::UnMakeMove(CHESSMOVE* move, int nChessID)
{
	CurPosition[move->From.y][move->From.x] = CurPosition[move->To.y][move->To.x];
	CurPosition[move->To.y][move->To.x] = nChessID;
}


int CSearchEngine::IsGameOver(int position[10][9], int nDepth)
{
	int i, j;
	bool RedLive = FALSE, BlackLive = FALSE;
	//check weather red side has king
	for(i=7; i<10; i++)
		for (j = 3; j < 6; j++)
		{
			if (position[i][j] == B_KING)
			{
				BlackLive = TRUE;
			}
			if (position[i][j] == R_KING)
			{
				RedLive = TRUE;
			}
		}
	//check weather black side has king
	for (i = 0; i<3; i++)
		for (j = 3; j < 6; j++)
		{
			if (position[i][j] == B_KING)
			{
				BlackLive = TRUE;
			}
			if (position[i][j] == R_KING)
			{
				RedLive = TRUE;
			}
		}
	i = (m_nMaxDepth - nDepth + 1) % 2;
	if (!RedLive)
		if (i)
			return 19990 + nDepth; //odd layer return max
		else
			return -19990 - nDepth;//even layer return min
	if (!BlackLive)
		if (i)
			return -19990 - nDepth;
		else
			return 19990 + nDepth;
	return 0; // both side of kings are alive
}

