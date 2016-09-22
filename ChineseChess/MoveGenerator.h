#pragma once
#include "define.h"

class CMoveGenerator
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();

	static bool IsValidMove(int position[10][9], int nFromX, int nFromY, int nToX, int nToY);
	int CreatPossibleMove(int position[10][9], int nPly, int nSide);
	CHESSMOVE m_MoveList[8][80];
protected:
	int AddMove(int nFromX, int nToX, int nFromY, int nToY, int nPly);
	void Gen_KingMove(int position[10][9], int i, int j, int nPly);
	void Gen_RBishopMove(int position[10][9], int i, int j, int nPly);
	void Gen_BBishopMove(int position[10][9], int i, int j, int nPly);
	void Gen_ElephantMove(int position[10][9], int i, int j, int nPly);
	void Gen_HorseMove(int position[10][9], int i, int j, int nPly);
	void Gen_CarMove(int position[10][9], int i, int j, int nPly);
	void Gen_RPawnMove(int position[10][9], int i, int j, int nPly);
	void Gen_BPawnMove(int position[10][9], int i, int j, int nPly);
	void Gen_CanonMove(int position[10][9], int i, int j, int nPly);
	int m_nMoveCount;
};

