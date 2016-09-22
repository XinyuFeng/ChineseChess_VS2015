#pragma once
#include "SearchEngine.h"
class FAlphaBetaEngine :
	public CSearchEngine
{
public:
	FAlphaBetaEngine();
	virtual ~FAlphaBetaEngine();
	virtual int SearchAGoodMove(int position[10][9]);
protected:
	int FAlphaBeta(int depth, int alpha, int beta);
};

