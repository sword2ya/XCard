#pragma once
#include "CardListView.h"

class CHorizontalCardListView : public CCardListView
{
	typedef set<size_t> TSet_LiftCards;
public:
	CHorizontalCardListView(void);
	~CHorizontalCardListView(void);

public:
	virtual QSize sizeHint() const;

public:

	virtual void Clear();

	void SetCanLift(bool bCan);
	bool CanLift() const;
	bool GetLiftCardIdx(size_t *arrLiftIdxs, size_t nMaxCnt) const ;
	size_t GetLiftCardCnt() const;
	bool IsLift(size_t nIdx) const ;
	bool LiftCard(size_t nIdx, bool bLift) ;

	void SetLiftSize(float fLiftSize);	// ���������С����
	size_t LiftSize() const;	// ��ȡ�����С����


protected:
	virtual QPoint _CalcCardPos( size_t nIdx ) const ;
	virtual void _OnCardClicked(size_t nIdx);

private:
	bool m_bCanLift;	// �Ƿ��������
	TSet_LiftCards m_setLiftCard;
	float m_fLiftSize;	// �����С����
};
