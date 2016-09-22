#pragma once
#include "SearchEngine.h"

class CNegaMaxEngine : public CSearchEngine
{
public:
	CNegaMaxEngine();
	virtual ~CNegaMaxEngine();
	virtual int SearchAGoodMove(int position[10][9]);
protected:
	int NegaMax(int depth);//the negamax engine
};

