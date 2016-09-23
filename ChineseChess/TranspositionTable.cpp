#include "stdafx.h"
#include "TranspositionTable.h"
#include "ChineseChess.h"

LONGLONG rand64(void)
{
	return rand() ^ ((LONGLONG)rand() << 15) ^ ((LONGLONG)rand() << 30) ^ ((LONGLONG)rand() << 45) ^ ((LONGLONG)rand() << 60);
}


LONG rand32(void)
{
	return rand() ^ ((LONG)rand() << 15) ^ ((LONG)rand() << 30);
}


CTranspositionTable::CTranspositionTable()
{
	InitializeHashKey();
}


CTranspositionTable::~CTranspositionTable()
{
	delete m_pTT[0];
	delete m_pTT[1];
}


void CTranspositionTable::InitializeHashKey()
{
	int i, j, k;
	//set srand
	srand((unsigned)time(NULL));
	//fill out the array
	for(i = 0; i < 15; ++i)
		for(j = 0; j < 10; ++j)
			for (k = 0; k < 9; ++k)
			{
				m_nHashKey32[i][j][k] = rand32();
				m_ulHashKey64[i][j][k] = rand64();
			}
	m_pTT[0] = new HashItem[1024 * 1024];
	m_pTT[1] = new HashItem[1024 * 1024];
}


void CTranspositionTable::CalculateInitHashKey(int CurPosition[10][9])
{
	int j, k, nChessType;
	m_HashKey32 = 0;
	m_HashKey64 = 0;
	//sum up all chess's hash value
	for(j = 0; j < 10; ++j)
		for (k = 0; k < 9; ++k)
		{
			nChessType = CurPosition[j][k];
			if (nChessType != NOCHESS)
			{
				m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nChessType][j][k];
				m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nChessType][j][k];
			}
		}
}


void CTranspositionTable::Hash_MakeMove(CHESSMOVE *move, int CurPosition[10][9])
{
	int nToID, nFromID;
	nFromID = CurPosition[move->From.y][move->From.x];
	nToID = CurPosition[move->To.y][move->To.x];
	//remove the moving chess from board
	m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nFromID][move->From.y][move->From.x];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nFromID][move->From.y][move->From.x];
	if (nToID != NOCHESS)
	{
		m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nToID][move->To.y][move->To.x];
		m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nToID][move->To.y][move->To.x];
	}

	m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nFromID][move->To.y][move->To.x];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nFromID][move->To.y][move->To.x];

}


void CTranspositionTable::Hash_UnMakeMove(CHESSMOVE *move, int nChessID, int CurPosition[10][9])
{
	int nToID;
	nToID = CurPosition[move->To.y][move->To.x];
	m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nToID][move->From.y][move->From.x];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nToID][move->From.y][move->From.x];
	
	m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nToID][move->To.y][move->To.x];
	m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nToID][move->To.y][move->To.x];

	if (nChessID)
	{
		m_HashKey32 = m_HashKey32 ^ m_nHashKey32[nChessID][move->To.y][move->To.x];
		m_HashKey64 = m_HashKey64 ^ m_ulHashKey64[nChessID][move->To.y][move->To.x];
	}
}

//alpha:upbound
//beta:lowbound
//depth: current searching level
//tableNo: odd or even level
int CTranspositionTable::LookUpHashTable(int alpha, int beta, int depth, int TableNo)
{
	int x;
	HashItem *pht;
	//calculate 20 bits hash address:2M
	x = m_HashKey32 & 0xFFFFF;
	pht = &m_pTT[TableNo][x];
	if (pht->depth >= depth && pht->checksum == m_HashKey64)
	{
		switch (pht->entry_type)
		{
		case exact:
			return pht->eval;
		case lower_bound:
			if (pht->eval >= beta)
				return(pht->eval);
			else
				break;
		case upper_bound:
			if (pht->eval <= alpha)
				return (pht->eval);
			else
				break;
			   
		}
	}
	return 66666;//return invalid signal
}


void CTranspositionTable::EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth, int TableNo)
{
	int x;
	HashItem *pht;
	x = m_HashKey32 & 0xFFFFF;
	pht = &m_pTT[TableNo][x];
	//write the value to hash table
	pht->checksum = m_HashKey64;
	pht->entry_type = entry_type;
	pht->eval = eval;
	pht->depth = depth;
}
