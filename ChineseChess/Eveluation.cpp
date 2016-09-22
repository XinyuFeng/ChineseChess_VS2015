#include "stdafx.h"
#include "Eveluation.h"
#include "ChineseChess.h"
#include "define.h"
//Pawn's additional value, closer to the king, higher the value.
// red
const int BA0[10][9] =
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{90, 90, 110, 120, 120, 120, 110, 90, 90},
	{90, 90, 110, 120, 120, 120, 110, 90, 90},
	{70, 90, 110, 110, 110, 110, 110, 90, 70},
	{70, 70, 70, 70, 70, 70, 70, 70, 70},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};
//black
const int BA1[10][9] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 70, 70, 70, 70, 70, 70, 70, 70, 70 },
	{ 70, 90, 110, 110, 110, 110, 110, 90, 70 },
	{ 90, 90, 110, 120, 120, 120, 110, 90, 90 },
	{ 90, 90, 110, 120, 120, 120, 110, 90, 90 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

int GetBingValue(int x, int y, int CurSituation[][9])
{
	if (CurSituation[y][x] == R_PAWN)
		return BA0[y][x];
	if (CurSituation[y][x] == B_PAWN)
		return BA1[y][x];
	return 0;  //isn't a pawn
}


CEveluation::CEveluation()
{
	m_BaseValue[B_KING] = BASEVALUE_KING;
	m_BaseValue[B_CAR] = BASEVALUE_CAR;
	m_BaseValue[B_HORSE] = BASEVALUE_HORSE;
	m_BaseValue[B_BISHOP] = BASEVALUE_BISHOP;
	m_BaseValue[B_ELEPHANT] = BASEVALUE_ELEPHANT;
	m_BaseValue[B_CANON] = BASEVALUE_CANON;
	m_BaseValue[B_PAWN] = BASEVALUE_PAWN;
	m_BaseValue[R_KING] = BASEVALUE_KING;
	m_BaseValue[R_CAR] = BASEVALUE_CAR;
	m_BaseValue[R_HORSE] = BASEVALUE_HORSE;
	m_BaseValue[R_BISHOP] = BASEVALUE_BISHOP;
	m_BaseValue[R_ELEPHANT] = BASEVALUE_ELEPHANT;
	m_BaseValue[R_CANON] = BASEVALUE_CANON;
	m_BaseValue[R_PAWN] = BASEVALUE_PAWN;

	m_FlexValue[B_KING] = FLEXIBILITY_KING;
	m_FlexValue[B_CAR] = FLEXIBILITY_CAR;
	m_FlexValue[B_HORSE] = FLEXIBILITY_HORSE;
	m_FlexValue[B_BISHOP] = FLEXIBILITY_BISHOP;
	m_FlexValue[B_ELEPHANT] = FLEXIBILITY_ELEPHANT;
	m_FlexValue[B_CANON] = FLEXIBILITY_CANON;
	m_FlexValue[B_PAWN] = FLEXIBILITY_PAWN;
	m_FlexValue[R_KING] = FLEXIBILITY_KING;
	m_FlexValue[R_CAR] = FLEXIBILITY_CAR;
	m_FlexValue[R_HORSE] = FLEXIBILITY_HORSE;
	m_FlexValue[R_BISHOP] = FLEXIBILITY_BISHOP;
	m_FlexValue[R_ELEPHANT] = FLEXIBILITY_ELEPHANT;
	m_FlexValue[R_CANON] = FLEXIBILITY_CANON;
	m_FlexValue[R_PAWN] = FLEXIBILITY_PAWN;

}


CEveluation::~CEveluation()
{
}

int count = 0;//the number of leaves who call the evaluate function

int CEveluation::Eveluate(int position[10][9], BOOL bIsRedTurn)
{
	int i, j, k;
	int nChessType, nTargetType;
	count++;

	memset(m_chessValue, 0, 360);
	memset(m_AttackPos, 0, 180);
	memset(m_GuardPos, 0, 360);
	memset(m_FlexibilityPos, 0, 360);
	//scan the board, find each chess, and its attack/guard chess, and its flexibility
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (position[i][j] != NOCHESS)
			{
				nChessType = position[i][j]; //get chess's type
				GetRelatePiece(position, j, i);//find all related position to (i, j)
				for (k = 0; k < nPosCount; ++k) //for every related position
				{
					nTargetType = position[RelatePos[k].y][RelatePos[k].x];
					if (nTargetType == NOCHESS)
						m_FlexibilityPos[i][j]++;//increase flexibility
					else //the target position is a chess
					{
						if (IsSameSide(nChessType, nTargetType))
						{// if the same side, increase the guard
							m_GuardPos[RelatePos[k].y][RelatePos[k].x]++;
						}
						else // not the same side, increase attack
						{
							m_AttackPos[RelatePos[k].y][RelatePos[k].x]++;
							m_FlexibilityPos[i][j]++;
							switch (nTargetType)
							{
							case R_KING:
								if (!bIsRedTurn)// black side now
									return 18888;//return fail value
								break;
							case B_KING:
								if (bIsRedTurn)
									return 18888;
								break;
							default:
								m_AttackPos[RelatePos[k].y][RelatePos[k].x] += (30 + (m_BaseValue[nTargetType] - m_BaseValue[nChessType]) / 10) / 10;//add more attack value according to target type;
								break;

							}
						}
					}
				}
			}
		}
	}

	for (i = 0; i < 10; ++i)
		for (j = 0; j < 9; ++j)
		{
			if (position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];//get the type
				m_chessValue[i][j]++; //if there is a chess, its value isn't zero
				m_chessValue[i][j] += m_FlexValue[nChessType] * m_FlexibilityPos[i][j];
				m_chessValue[i][j] += GetBingValue(j, i, position);
			}
		}
	// continue save the data scaned from above
	int nHalfvalue;
	for(i = 0; i < 10; ++i)
		for (j = 0; j < 9; ++j)
		{
			if (position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];
				nHalfvalue = m_BaseValue[nChessType] / 16;//1/16 of a chess's base value is the inc of attack/guard value
				m_chessValue[i][j] += m_BaseValue[nChessType];
				if (IsRed(nChessType))
				{
					if (m_AttackPos[i][j])// the current red chess is being attacked
					{
						if (bIsRedTurn)  // red side move now
						{
							if (nChessType == R_KING)
							{
								m_chessValue[i][j] -= 20;
							}
							else
							{
								m_chessValue[i][j] -= nHalfvalue * 2;
								if (m_GuardPos[i][j])//the current red chess is being guard
									m_chessValue[i][j] += nHalfvalue;//being guarded, add an inc
							}
						}
						else
						{// it's black turn now
							if (nChessType == R_KING)
							{
								return 18888;
							}
							// minus 10 times of inc, to show the high attack level
							m_chessValue[i][j] -= nHalfvalue * 10;
							if (m_GuardPos[i][j])
								m_chessValue[i][j] += nHalfvalue * 9;

						}
						// a pawn might attack a car which's guarded
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else
					{//isn't being attacked
						if (m_GuardPos[i][j])
							m_chessValue[i][j] += 5;
					}
				}
				else
				{// black chess
					if (m_AttackPos[i][j])//being attacked
					{
						if (!bIsRedTurn)
						{
							if (nChessType == B_KING)
								m_chessValue[i][j] -= 20;
							else
							{
								m_chessValue[i][j] -= nHalfvalue * 2;
								if (m_GuardPos[i][j])
									m_chessValue[i][j] += nHalfvalue;
							}
						}
						else//red turn now
						{
							if (nChessType == R_KING)
								return 18888;//fail
							m_chessValue[i][j] -= nHalfvalue * 10;
							if (m_GuardPos[i][j])
								m_chessValue[i][j] += nHalfvalue * 9;
						}
						// add the attack diff
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else
					{// isn't being attacked
						if (m_GuardPos[i][j])
							m_chessValue[i][j] += 5;// being guarded,  get bonus score
					}
				}
			}
		}
	//above saved total value of each chess
	//below calculate the total score of each side
	int nRedValue = 0;
	int nBlackValue = 0;
	for(i = 0; i < 10; i++)
		for (j = 0; j < 9; j++)
		{
			nChessType = position[i][j];
			if (nChessType != NOCHESS)
			{
				if (IsRed(nChessType))
					nRedValue += m_chessValue[i][j];
				else
					nBlackValue += m_chessValue[i][j];
			}

		}
	if (bIsRedTurn)
		return nRedValue - nBlackValue;
	else
		return nBlackValue - nRedValue;
}

//add a posiiton into RelatePos
void CEveluation::AddPoint(int x, int y)
{
	RelatePos[nPosCount].x = x;
	RelatePos[nPosCount].y = y;
	nPosCount++;
}

//get all related position
int CEveluation::GetRelatePiece(int position[10][9], int j, int i)
{
	nPosCount = 0;
	int nChessID;
	int flag;
	int x, y;
	nChessID = position[i][j];
	switch (nChessID)
	{
	case R_KING:
	case B_KING:
		for (y = 0; y < 3; y++)
			for (x = 3; x < 6; x++)
				if (CanTouch(position, j, i, x, y))// can reach (x,y)
					AddPoint(x, y);// add(x, y) into relatepos
		for (y = 7; y < 10; y++)
			for (x = 3; x < 6; x++)
				if (CanTouch(position, j, i, x, y))
					AddPoint(x, y);
		break;
	case R_BISHOP:
		for (y = 7; y < 10; y++)
			for (x = 3; x < 6; x++)
				if (CanTouch(position, j, i, x, y))
					AddPoint(x, y);
		break;
	case B_BISHOP:
		for (y = 0; y < 3; y++)
			for (x = 3; x < 6; x++)
				if (CanTouch(position, j, i, x, y))
					AddPoint(x, y);
		break;
	case R_ELEPHANT:
	case B_ELEPHANT:
		//right down
		x = j + 2;
		y = i + 2;
		if (x < 9 && y < 10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		// right up
		x = j + 2;
		y = i - 2;
		if (x < 9 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		//left down
		x = j - 2;
		y = i + 2;
		if (x >= 0 && y < 10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		//right up
		x = j - 2;
		y = i - 2;
		if (x >= 0 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		break;
	case R_HORSE:
	case B_HORSE:
		x = j + 2;
		y = i + 1;
		if (x < 9 && y < 10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		x = j + 2;
		y = i - 1;
		if (x < 9 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		x = j - 2;
		y = i + 1;
		if (x >= 0 && y < 10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		x = j - 2;
		y = i - 1;
		if (x >= 0 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		x = j + 1;
		y = i + 2;
		if (x < 9 && y < 10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		x = j - 1;
		y = i + 2;
		if (x >= 0 && y < 10 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		x = j + 1;
		y = i - 2;
		if (x < 9 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		x = j - 1; 
		y = i - 2;
		if (x >= 0 && y >= 0 && CanTouch(position, j, i, x, y))
			AddPoint(x, y);
		break;
	case R_CAR:
	case B_CAR:
		// check whether it can move right 
		x = j + 1;
		y = i;
		while (x < 9)
		{
			if (NOCHESS == position[y][x])
				AddPoint(x, y);
			else
			{// reach first chess
				AddPoint(x, y);
				break;
			}
			x++;
		}
		//check left
		x = j - 1;
		y = i;
		while (x >= 0)
		{
			if (NOCHESS == position[y][x])
				AddPoint(x, y);
			else
			{
				AddPoint(x, y);
				break;
			}
			x--;
		}
		// check down
		x = j;
		y = i + 1;
		while (y < 10)
		{
			if (NOCHESS == position[y][x])
				AddPoint(x, y);
			else
			{
				AddPoint(x, y);
				break;
			}
			y++;
		}
		//check up
		x = j;
		y = i - 1;
		while (y >= 0)
		{
			if (NOCHESS == position[y][x])
				AddPoint(x, y);
			else
			{
				AddPoint(x, y);
				break;
			}
			y--;
		}
		break;
	case R_PAWN:
		y = i - 1;
		x = j;
		if (y >= 0)
			AddPoint(x, y); 
		if (i < 5)
		{//pass the river
			y = i;
			x = j + 1;
			if (x < 9)
				AddPoint(x, y);
			x = j - 1;
			if (x >= 0)
				AddPoint(x, y);
		}
		break;
	case B_PAWN:
		y = i + 1;
		x = j;
		if (y < 10)
			AddPoint(x, y);
		if (i > 4)
		{//pass the river
			y = i;
			x = j + 1;
			if (x < 9)
				AddPoint(x, y);
			x = j - 1;
			if (x >= 0)
				AddPoint(x, y);
		}
		break;
	case B_CANON:
	case R_CANON:
		// check right direction
		x = j + 1;
		y = i;
		flag = FALSE;
		while (x < 9)
		{
			if (NOCHESS == position[y][x])
			{
				if (!flag)
					AddPoint(x, y);
			}
			else
			{// has chess
				if (!flag)
					flag = TRUE;//first chess
				else
				{
					AddPoint(x, y);
					break;
				}
			}
			x++;
		}
		// check left direction
		x = j - 1;
		flag = FALSE;
		while (x >= 0)
		{
			if (NOCHESS == position[y][x])
			{
				if (!flag)
					AddPoint(x, y);
			}
			else
			{// has chess
				if (!flag)
					flag = TRUE;//first chess
				else
				{
					AddPoint(x, y);
					break;
				}
			}
			x--;
		}
		// check bottom direction
		x = j;
		y = i + 1;
		flag = FALSE;
		while (y < 10)
		{
			if (NOCHESS == position[y][x])
			{
				if (!flag)
					AddPoint(x, y);
			}
			else
			{// has chess
				if (!flag)
					flag = TRUE;//first chess
				else
				{
					AddPoint(x, y);
					break;
				}
			}
			y++;
		}
		// check up direction
		y = i - 1;
		flag = FALSE;
		while (y >= 0)
		{
			if (NOCHESS == position[y][x])
			{
				if (!flag)
					AddPoint(x, y);
			}
			else
			{// has chess
				if (!flag)
					flag = TRUE;//first chess
				else
				{
					AddPoint(x, y);
					break;
				}
			}
			y--;
		}
		break;
	default:
		break;

	}
	return nPosCount;
}


BOOL CEveluation::CanTouch(int position[10][9], int nFromX, int nFromY, int nToX, int nToY)
{
	int i, j;
	int nMoveChessID, nTargetID;
	if (nFromY == nToY && nFromX == nToX)
		return FALSE;
	nMoveChessID = position[nFromY][nFromX];
	nTargetID = position[nToY][nToX];
	switch (nMoveChessID)
	{
	case B_KING:
		if (nTargetID == R_KING)
		{
			if (nFromX != nToX)
				return FALSE;
			for (i = nFromY + 1; i < nToY; i++)
				if (position[i][nFromX] != NOCHESS)
					return FALSE;
		}
		else
		{
			if (nToY > 2 || nToX > 5 || nToX < 3)
				return FALSE;
			if (abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
				return FALSE;
		}
		break;
	case R_BISHOP:
		if (nToY < 7 || nToX > 5 || nToX < 3)
			return FALSE;
		if (abs(nFromY - nToY) != 1 || abs(nToX - nFromX) != 1)
			return FALSE;
		break;
	case B_BISHOP:
		if (nToY > 2 || nToX > 5 || nToX < 3)
			return FALSE;
		if (abs(nFromY - nToY) != 1 || abs(nToX - nFromX) != 1)
			return FALSE;
		break;
	case R_ELEPHANT:
		if (nToY < 5)
			return FALSE;//can't cross river
		if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
			return FALSE;
		if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
			return FALSE;
		break;
	case B_ELEPHANT:
		if (nToY > 4)
			return FALSE;//can't cross river
		if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
			return FALSE;
		if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
			return FALSE;
		break;
	case B_PAWN:
		if (nToY < nFromY)
			return FALSE; // a pawn can't turn back
		if (nFromY < 5 && nFromY == nToY)
			return FALSE;// can only go straight before passing river
		if (nToY - nFromY + abs(nToX - nFromX) > 1)
			return FALSE;// only go one step
		break;
	case R_PAWN:
		if (nToY > nFromY)
			return FALSE; // a pawn can't turn back
		if (nFromY > 4 && nFromY == nToY)
			return FALSE;// can only go straight before passing river
		if (nFromY - nToY + abs(nToX - nFromX) > 1)
			return FALSE;// only go one step
		break;
	case R_KING:
		if (nTargetID == B_KING)
		{
			if (nFromX != nToX)
				return FALSE;
			for (i = nFromY - 1; i > nToY; i--)
				if (position[i][nFromX] != NOCHESS)
					return FALSE;
		}
		else
		{
			if (nToY < 7 || nToX > 5 || nToX < 3)
				return FALSE;
			if (abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
				return FALSE;
		}
		break;
	case B_CAR:
	case R_CAR:
		if (nFromY != nToY && nFromX != nToX)
			return FALSE;//go straight
		if (nFromY == nToY)
		{// move in row
			if (nFromX < nToX)
			{//right
				for (i = nFromX + 1; i < nToX; i++)
					if (position[nFromY][i] != NOCHESS)
						return FALSE;
			}
			else
			{//left
				for (i = nToX + 1; i < nFromX; i++)
					if (position[nFromY][i] != NOCHESS)
						return FALSE;
			}
		}
		else
		{
			//move in col
			if (nFromY < nToY)
			{//right
				for (j = nFromY + 1; j < nToY; j++)
					if (position[j][nFromX] != NOCHESS)
						return FALSE;
			}
			else
			{//left
				for (j = nToY + 1; j < nFromY; j++)
					if (position[j][nFromX] != NOCHESS)
						return FALSE;
			}
		}
		break;
	case B_HORSE:
	case R_HORSE:
		if (!((abs(nToX - nFromX) == 1 && abs(nToY - nFromY) == 2) || (abs(nToX - nFromX) == 2 && abs(nToY - nFromY) == 1)))
			return FALSE;
		if (nToX - nFromX == 2)
		{
			i = nFromX + 1;
			j = nFromY;
		}
		else if (nFromX - nToX == 2)
		{
			i = nFromX - 1;
			j = nFromY;
		}
		else if (nToY - nFromY == 2)
		{
			i = nFromX;
			j = nFromY + 1;
		}
		else if (nFromY - nToY == 2)
		{
			i = nFromX;
			j = nFromY - 1;
		}

		if (position[j][i] != NOCHESS)
			return FALSE;
		break;
	case B_CANON:
	case R_CANON:
		if (nFromY != nToY && nFromX != nToX)
			return FALSE; //canon go straight
		if (position[nToY][nToX] == NOCHESS)
		{// don't eat
			if (nFromY == nToY)
			{// move in row
				if (nFromX < nToX)
				{//right
					for (i = nFromX + 1; i < nToX; i++)
						if (position[nFromY][i] != NOCHESS)
							return FALSE;
				}
				else
				{//left
					for (i = nToX + 1; i < nFromX; i++)
						if (position[nFromY][i] != NOCHESS)
							return FALSE;
				}
			}
			else
			{
				if (nFromY < nToY)
				{//bottom
					for (j = nFromY + 1; j < nToY; j++)
						if (position[j][nFromX] != NOCHESS)
							return FALSE;
				}
				else
				{//up
					for (j = nToY + 1; j < nFromY; j++)
						if (position[j][nFromX] != NOCHESS)
							return FALSE;
				}
			}
		}
		else//eat
		{
			int count = 0;
			if (nFromY == nToY)
			{
				//move in row
				if (nFromX < nToX)
				{//right
					for (i = nFromX + 1; i < nToX; i++)
						if (position[nFromY][i] != NOCHESS)
							count++;
					if (count != 1)
						return FALSE;
				}
				else
				{//left
					for (i = nToX + 1; i < nFromX; i++)
						if (position[nFromY][i] != NOCHESS)
							count++;
					if (count != 1)
						return FALSE;


				}
			}
			else// move in col
			{
				if (nFromY < nToY)
				{
					//bottom
					for (j = nFromY + 1; j < nToY; j++)
						if (position[j][nFromX] != NOCHESS)
							count++;
					if (count != 1)
						return FALSE;
				}
				else
				{
					for (j = nToY + 1; j < nFromY; j++)
						if (position[j][nFromX] != NOCHESS)
							count++;
					if (count != 1)
						return FALSE;
				}
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}