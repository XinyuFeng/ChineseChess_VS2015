#pragma once
#include "SearchEngine.h"
class CAlphaBetaEngine :
	public CSearchEngine
{
public:
	CAlphaBetaEngine();
	virtual ~CAlphaBetaEngine();
	virtual int SearchAGoodMove(int position[10][9]);
protected:
	int alphabeta(int depth, int alpha, int beta);
};

