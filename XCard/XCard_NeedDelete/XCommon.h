#pragma once


enum ECardSuit
{
	eCardSuit_Min = 0,
	eCardSuit_Spade = 0,	// ����
	eCardSuit_Heart,	// ����
	eCardSuit_Club,		// ÷��
	eCardSuit_Diamond,	// ����
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
	eCardPoint_Kinglet, // С��
	eCardPoint_King, // ����
	eCardPoint_Max = eCardPoint_King, 
};

struct TCardInfo
{
	ECardPoint ePoint;
	ECardSuit eSuit;

	bool operator<(const TCardInfo& stOther) const // �����������Ҫ��Ϊmap�ļ�ֵʱʹ��
	{
		if (ePoint != stOther.ePoint)
		{
			return ePoint < stOther.ePoint;
		}
		return eSuit < stOther.eSuit;
	}
};