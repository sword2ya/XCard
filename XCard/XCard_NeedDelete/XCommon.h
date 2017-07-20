#pragma once


enum ECardSuit
{
	eCardSuit_Min = 0,
	eCardSuit_Spade = 0,	// 黑桃
	eCardSuit_Heart,	// 红桃
	eCardSuit_Club,		// 梅花
	eCardSuit_Diamond,	// 方块
	eCardSuit_Max = eCardSuit_Diamond,
};

enum ECardPoint
{
	eCardPoint_Min = 0,
	eCardPoint_A = 0, // A
	eCardPoint_2, // 2 
	eCardPoint_3, // 3
	eCardPoint_4, // 4 
	eCardPoint_5, // 5 
	eCardPoint_6, // 6 
	eCardPoint_7, // 7 
	eCardPoint_8, // 8 
	eCardPoint_9, // 9 
	eCardPoint_10, // 10 
	eCardPoint_J, // J
	eCardPoint_Q, // Q 
	eCardPoint_K, // K 
	eCardPoint_Kinglet, // 小王
	eCardPoint_King, // 大王
	eCardPoint_Max = eCardPoint_King, 
};

struct TCardInfo
{
	ECardPoint ePoint;
	ECardSuit eSuit;

	bool operator<(const TCardInfo& stOther) const // 随意的排序，主要作为map的键值时使用
	{
		if (ePoint != stOther.ePoint)
		{
			return ePoint < stOther.ePoint;
		}
		return eSuit < stOther.eSuit;
	}
};