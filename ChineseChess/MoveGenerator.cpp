#include "stdafx.h"
#include "MoveGenerator.h"


CMoveGenerator::CMoveGenerator()
{
}


CMoveGenerator::~CMoveGenerator()
{
}


bool CMoveGenerator::IsValidMove(int position[10][9], int nFromX, int nFromY, int nToX, int nToY)
{
	int i, j;
	int nMoveChessID, nTargetID;
	if (nFromY == nToY && nFromX == nToX)
		return FALSE;
	nMoveChessID = position[nFromY][nFromX];
	nTargetID = position[nToY][nToX];
	if (IsSameSide(nMoveChessID, nTargetID))
		return FALSE; //same side is illegal
	switch (nMoveChessID)
	{
	case B_KING:
		if (nTargetID == R_KING)
		{
			if (nFromX != nToX)
				return FALSE;
			for (i = nFromY + 1; i < nToY; ++i)
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
	case R_KING:
		if (nTargetID == B_KING)
		{
			if (nFromX != nToX)
				return FALSE;
			for (i = nFromY - 1; i > nToY; --i)
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
	case R_BISHOP:
		if (nToY < 7 || nToX>5 || nToX < 3)
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
			return FALSE; // it can't pass the river
		if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
			return FALSE;
		if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
			return FALSE;
		break;
	case B_ELEPHANT:
		if (nToY > 4)
			return FALSE; // it can't pass the river
		if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
			return FALSE;
		if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOCHESS)
			return FALSE;
		break;
	case B_PAWN:
		if (nToY < nFromY)
			return FALSE;
		if (nFromY < 5 && nFromY == nToY)
			return FALSE;
		if (nToY - nFromY + abs(nToX - nFromX) > 1)
			return FALSE;
		break;
	case R_PAWN:
		if (nToY > nFromY)
			return FALSE;
		if (nFromY > 4 && nFromY == nToY)
			return FALSE;
		if (nFromY - nToY + abs(nToX - nFromX) > 1)
			return FALSE;
		break;
	case B_CAR:
	case R_CAR:
		if (nFromY != nToY&&nFromX != nToX)
			return FALSE;
		if (nFromY == nToY)
		{
			if (nFromX < nToX)
			{
				for (i = nFromX + 1; i < nToX; ++i)
					if (position[nFromY][i] != NOCHESS)
						return FALSE;
			}
			else
			{
				for (i = nToX + 1; i < nFromX; ++i)
					if (position[nFromY][i] != NOCHESS)
						return FALSE;
			}
		}
		else
		{
			if (nFromY < nToY)
			{
				for (j = nFromY + 1; j < nToY; j++)
					if (position[j][nFromX] != NOCHESS)
						return FALSE;
			}
			else
			{
				for (j = nToY + 1; j < nFromY; ++j)
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
			return FALSE;
		//if canon doesn't eat a chess, then there should be no chess on the line
		if (position[nToY][nToX] == NOCHESS)
		{
			if (nFromY == nToY)
			{
				if (nFromX < nToX)
				{
					for (i = nFromX + 1; i < nToX; i++)
						if (position[nFromY][i] != NOCHESS)
							return FALSE;
				}
				else
				{
					for (i = nToX + 1; i < nFromX; i++)
						if (position[nFromY][i] != NOCHESS)
							return FALSE;
				}
			}
			else
			{
				if (nFromY < nToY)
				{
					for (j = nFromY + 1; j < nToY; j++)
						if (position[j][nFromX] != NOCHESS)
							return FALSE;
				}
				else
				{
					for (j = nToY + 1; j < nFromY; j++)
						if (position[j][nFromX] != NOCHESS)
							return FALSE;
				}
			}
		}
		else
		{
			int count = 0;
			if (nFromY == nToY)
			{
				if (nFromX < nToX)
				{
					for (i = nFromX + 1; i < nToX; ++i)
						if (position[nFromY][i] != NOCHESS)
							count++;
					if (count != 1)
						return FALSE;
				}
				else
				{
					for (i = nToX + 1; i < nFromX; ++i)
						if (position[nFromY][i] != NOCHESS)
							count++;
					if (count != 1)
						return FALSE;
				}
			}
			else
			{
				if (nFromY < nToY)
				{
					for (j = nFromY + 1; j < nToY; ++j)
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

//insert a move to m_MoveList
int CMoveGenerator::AddMove(int nFromX, int nFromY, int nToX, int nToY, int nPly)
{
	m_MoveList[nPly][m_nMoveCount].From.x = nFromX;
	m_MoveList[nPly][m_nMoveCount].From.y = nFromY;
	m_MoveList[nPly][m_nMoveCount].To.x = nToX;
	m_MoveList[nPly][m_nMoveCount].To.y = nToY;
	m_nMoveCount++;
	return m_nMoveCount;
}

//creat all posible move, nside: true: black; false: red.
int CMoveGenerator::CreatPossibleMove(int position[10][9], int nPly, int nSide)
{
	int nChessID;
	int i, j;
	m_nMoveCount = 0;
	for(j = 0; j < 9; ++j)
		for (i = 0; i < 10; ++i)
		{
			if (position[i][j] != NOCHESS)
			{
				nChessID = position[i][j];
				if (!nSide&&IsRed(nChessID))
					continue; //ignore red chess
				if (nSide&&IsBlack(nChessID))
					continue; //ignore black
				switch (nChessID)
				{
				case R_KING:
				case B_KING:
					Gen_KingMove(position, i, j, nPly);
					break;
				case R_BISHOP:
					Gen_RBishopMove(position, i, j, nPly);
					break;
				case B_BISHOP:
					Gen_BBishopMove(position, i, j, nPly);
					break;
				case R_ELEPHANT:
				case B_ELEPHANT:
					Gen_ElephantMove(position, i, j, nPly);
					break;
				case R_HORSE:
				case B_HORSE:
					Gen_HorseMove(position, i, j, nPly);
					break;
				case R_CAR:
				case B_CAR:
					Gen_CarMove(position, i, j, nPly);
					break;
				case R_PAWN:
					Gen_RPawnMove(position, i, j, nPly);
					break;
				case B_PAWN:
					Gen_BPawnMove(position, i, j, nPly);
					break;
				case B_CANON:
				case R_CANON:
					Gen_CanonMove(position, i, j, nPly);
					break;
				default:
					break;


				}

			}
		}
	return m_nMoveCount;
}


void CMoveGenerator::Gen_KingMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	for (y = 0; y < 3; ++y)
		for (x = 3; x < 6; ++x)
			if (IsValidMove(position, j, i, x, y))
				AddMove(j, i, x, y, nPly);
	for (y = 7; y < 10; ++y)
		for (x = 3; x < 6; ++x)
			if (IsValidMove(position, j, i, x, y))
				AddMove(j, i, x, y, nPly);
}


void CMoveGenerator::Gen_RBishopMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	for (y = 7; y < 10; ++y)
		for (x = 3; x < 6; ++x)
			if (IsValidMove(position, j, i, x, y))
				AddMove(j, i, x, y, nPly);
}


void CMoveGenerator::Gen_BBishopMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	for (y = 0; y < 3; ++y)
		for (x = 3; x < 6; ++x)
			if (IsValidMove(position, j, i, x, y))
				AddMove(j, i, x, y, nPly);
}


void CMoveGenerator::Gen_ElephantMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	//insert bottom right position
	x = j + 2;
	y = i + 2;
	if (x < 9 && y < 10 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	//insert up right position
	x = j + 2;
	y = i - 2;
	if (x < 9 && y >= 0 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	//insert bottom left position
	x = j - 2;
	y = i + 2;
	if (x >= 0 && y < 10 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	//insert up left position
	x = j - 2;
	y = i - 2;
	if (x >= 0 && y >= 0 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);

}


void CMoveGenerator::Gen_HorseMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	//insert bottom right position
	x = j + 2;
	y = i + 1;
	if (x < 9 && y < 10 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	//insert up right position
	x = j + 2;
	y = i - 1;
	if (x < 9 && y >= 0 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	//insert bottom left position
	x = j - 2;
	y = i + 1;
	if (x >= 0 && y < 10 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	//insert up left position
	x = j - 2;
	y = i - 1;
	if (x >= 0 && y >= 0 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);

	x = j + 1;
	y = i + 2;
	if (x < 9 && y < 10 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	x = j - 1;
	y = i + 2;
	if (x >= 0 && y < 10 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	x = j + 1;
	y = i - 2;
	if (x < 9 && y >= 0 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);
	x = j - 1;
	y = i - 2;
	if (x >= 0 && y >= 0 && IsValidMove(position, j, i, x, y))
		AddMove(j, i, x, y, nPly);

}


void CMoveGenerator::Gen_RPawnMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	int nChessID;
	nChessID = position[i][j];
	y = i - 1; //move ahead
	x = j;
	if (y > 0 && !IsSameSide(nChessID, position[y][x]))
		AddMove(j, i, x, y, nPly);
	if (i < 5)//pass the river
	{
		y = i;
		x = j + 1;
		if (x < 9 && !IsSameSide(nChessID, position[y][x]))
			AddMove(j, i, x, y, nPly);
		x = j - 1;
		if (x >= 0 && !IsSameSide(nChessID, position[y][x]))
			AddMove(j, i, x, y, nPly);

	}

}


void CMoveGenerator::Gen_BPawnMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	int nChessID;
	nChessID = position[i][j];
	y = i + 1; //move ahead
	x = j;
	if (y < 10 && !IsSameSide(nChessID, position[y][x]))
		AddMove(j, i, x, y, nPly);
	if (i > 4)//pass the river
	{
		y = i;
		x = j + 1;
		if (x < 9 && !IsSameSide(nChessID, position[y][x]))
			AddMove(j, i, x, y, nPly);
		x = j - 1;
		if (x >= 0 && !IsSameSide(nChessID, position[y][x]))
			AddMove(j, i, x, y, nPly);

	}

}


void CMoveGenerator::Gen_CarMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	int nChessID;
	nChessID = position[i][j];
	//insert right position
	x = j + 1;
	y = i;
	while (x < 9)
	{
		if (NOCHESS == position[y][x])
			AddMove(j, i, x, y, nPly);
		else
		{
			if (!IsSameSide(nChessID, position[y][x]))
				AddMove(j, i, x, y, nPly);
			break;
		}
		x++;
	}
	//insert left position
	x = j - 1;
	y = i;
	while (x >= 0)
	{
		if (NOCHESS == position[y][x])
			AddMove(j, i, x, y, nPly);
		else
		{
			if (!IsSameSide(nChessID, position[y][x]))
				AddMove(j, i, x, y, nPly);
			break;
		}
		x--;
	}
	// insert bottom position
	x = j;
	y = i + 1;
	while (y < 10)
	{
		if (NOCHESS == position[y][x])
			AddMove(j, i, x, y, nPly);
		else
		{
			if (!IsSameSide(nChessID, position[y][x]))
				AddMove(j, i, x, y, nPly);
			break;
		}
		y++;
	}
	//insert up position
	x = j;
	y = i - 1;
	while (y >= 0)
	{
		if (NOCHESS == position[y][x])
			AddMove(j, i, x, y, nPly);
		else
		{
			if (!IsSameSide(nChessID, position[y][x]))
				AddMove(j, i, x, y, nPly);
			break;
		}
		y--;
	}
}


void CMoveGenerator::Gen_CanonMove(int position[10][9], int i, int j, int nPly)
{
	int x, y;
	bool flag;
	int nChessID;
	nChessID = position[i][j];
	//insert right position
	x = j + 1;
	y = i;
	flag = FALSE;
	while (x < 9)
	{
		if (NOCHESS == position[y][x])
		{
			if (!flag)
				AddMove(j, i, x, y, nPly);
		}
		else
		{
			if (!flag)
				flag = TRUE;
			else
			{
				if (!IsSameSide(nChessID, position[y][x]))
					AddMove(j, i, x, y, nPly);
				break;
			}
		}
		x++;
	}
	//insert left position
	x = j - 1;
	flag = FALSE;
	while (x >= 0)
	{
		if (NOCHESS == position[y][x])
		{
			if (!flag)
				AddMove(j, i, x, y, nPly);
		}
		else
		{
			if (!flag)
				flag = TRUE;
			else
			{
				if (!IsSameSide(nChessID, position[y][x]))
					AddMove(j, i, x, y, nPly);
				break;
			}
		}
		x--;
	}
	//insert bottom position
	x = j;
	y = i + 1;
	flag = FALSE;
	while (y < 10)
	{
		if (NOCHESS == position[y][x])
		{
			if (!flag)
				AddMove(j, i, x, y, nPly);
		}
		else
		{
			if (!flag)
				flag = TRUE;
			else
			{
				if (!IsSameSide(nChessID, position[y][x]))
					AddMove(j, i, x, y, nPly);
				break;
			}
		}
		y++;
	}
	y = i - 1;
	flag = FALSE;
	while (y >= 0)
	{
		if (NOCHESS == position[y][x])
		{
			if (!flag)
				AddMove(j, i, x, y, nPly);
		}
		else
		{
			if (!flag)
				flag = TRUE;
			else
			{
				if (!IsSameSide(nChessID, position[y][x]))
					AddMove(j, i, x, y, nPly);
				break;
			}
		}
		y--;
	}

}

