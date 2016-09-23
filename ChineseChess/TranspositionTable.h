#pragma once
#include "ChineseChess.h"
#include "define.h"

enum ENTRY_TYPE{exact, lower_bound, upper_bound};
typedef struct HASHITEM {
	LONGLONG checksum;
	ENTRY_TYPE entry_type;
	short depth;//the depth when get hash value
	short eval;// node's value
}HashItem;

class CTranspositionTable
{
public:
	CTranspositionTable();
	virtual ~CTranspositionTable();
	//calculate the hash of a board
	void CalculateInitHashKey(int CurPosition[10][9]);
	//get new hash value according to the move
	void Hash_MakeMove(CHESSMOVE* move, int CurPosition[10][9]);
	// recover the has value by cancelling the move
	void Hash_UnMakeMove(CHESSMOVE* move, int nChessID, int CurPosition[10][9]);
	//look up hash table
	int LookUpHashTable(int alpha, int beta, int depth, int TableNo);
	// save the current node's value to hash table
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth, int TableNo);
	//create hash table
	void InitializeHashKey();
	UINT m_nHashKey32[15][10][9];//32 bit
	ULONGLONG m_ulHashKey64[15][10][9];//64 bit
	HashItem *m_pTT[2];//transposition table ptr
	UINT m_HashKey32;//32 bit hash value
	LONGLONG m_HashKey64;//64 bit hash value

};

