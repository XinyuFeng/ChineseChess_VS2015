#pragma once
#define BASEVALUE_PAWN 100
#define BASEVALUE_BISHOP 250
#define BASEVALUE_ELEPHANT 250
#define BASEVALUE_CAR 500
#define BASEVALUE_HORSE 350
#define BASEVALUE_CANON 350
#define BASEVALUE_KING 10000
// each chess's flexibility
//the socre that if the chess has one more moving position, it should add the score
#define FLEXIBILITY_PAWN 15
#define FLEXIBILITY_BISHOP 1
#define FLEXIBILITY_ELEPHANT 1
#define FLEXIBILITY_CAR 6
#define FLEXIBILITY_HORSE 12
#define FLEXIBILITY_CANON 6
#define FLEXIBILITY_KING 0
class CEveluation
{
public:
	CEveluation();
	virtual ~CEveluation();
	//BIsRedTurn : who should play now
	virtual int Eveluate(int position[10][9], BOOL bIsRedTurn);
protected:
	// enumerate those chess who are correlate with a chess at particular position
	int GetRelatePiece(int position[10][9], int j, int i);
	// judge weather chess at From can move to To
	BOOL CanTouch(int position[10][9], int nFromX, int nFromY, int nToX, int nToY);
	//add a position to the "relate position list"
	void AddPoint(int x, int y);
	int m_BaseValue[15];// save chess's base value
	int m_FlexValue[15];// save chess's flexibility score
	short m_AttackPos[10][9];// save the attack info for every position
	int m_GuardPos[10][9];// save every position's guarded info
	int m_FlexibilityPos[10][9];//save the flex score of the chess in every position
	int m_chessValue[10][9];//the total value of a chess at a position
	int nPosCount;//save the number of relate position of a chess
	POINT RelatePos[20]; // save a chess's related position

};

