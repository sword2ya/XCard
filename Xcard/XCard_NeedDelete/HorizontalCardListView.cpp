#include "stdafx.h"
#include "HorizontalCardListView.h"
#include "CardView.h"


CHorizontalCardListView::CHorizontalCardListView(void)
{
	m_bCanLift = false;
	m_fLiftSize = 1.f/3;
}

CHorizontalCardListView::~CHorizontalCardListView(void)
{
}

QSize CHorizontalCardListView::sizeHint() const
{
	QSize oSizeRet;
	QSize oCardSize = CardSize();
	size_t nOverlapSize = Overlap()*oCardSize.width();
	size_t nLiftSize = oCardSize.height() * m_fLiftSize;
	if (m_bCanLift)
	{
		oSizeRet.setHeight(oCardSize.height() + nLiftSize);
	}
	else
	{
		oSizeRet.setHeight(oCardSize.height());
	}
	size_t nCardCnt = _GetCardCnt();
	if (nCardCnt == 0)
	{
		oSizeRet.setWidth(oCardSize.width());
	}
	else
	{
		oSizeRet.setWidth(oCardSize.width() + (oCardSize.width()-nOverlapSize) * (nCardCnt - 1));
	}
	
	return oSizeRet;
}

QPoint CHorizontalCardListView::_CalcCardPos( size_t nIdx ) const
{
	QPoint oPointRet;
	QSize oCardSize = CardSize();
	size_t nOverlapSize = Overlap()*oCardSize.width();
	size_t nLiftSize = oCardSize.height() * m_fLiftSize;

	if ( IsLift(nIdx) || !m_bCanLift)
	{
		oPointRet.setY(0);
	}
	else
	{
		oPointRet.setY(nLiftSize);
	}
	oPointRet.setX(nIdx * (oCardSize.width()-nOverlapSize));
	return oPointRet;
}

void CHorizontalCardListView::_OnCardClicked(size_t nIdx)
{
	if (!m_bCanLift)
	{
		return;
	}
	LiftCard(nIdx, !IsLift(nIdx));
}

void CHorizontalCardListView::Clear()
{
	CCardListView::Clear();
	m_setLiftCard.clear();
}


void CHorizontalCardListView::SetCanLift( bool bCan )
{
	m_bCanLift = bCan;
	_ResetCards();
}

bool CHorizontalCardListView::CanLift() const 
{
	return m_bCanLift;
}

bool CHorizontalCardListView::GetLiftCardIdx( size_t *arrLiftIdxs, size_t nMaxCnt ) const
{
	if (m_setLiftCard.size() > nMaxCnt)
	{
		return false;
	}
	std::copy(m_setLiftCard.begin(), m_setLiftCard.end(), arrLiftIdxs);
	return true;
}

size_t CHorizontalCardListView::GetLiftCardCnt() const
{
	return m_setLiftCard.size();
}

bool CHorizontalCardListView::IsLift( size_t nIdx ) const
{
	return std::find(m_setLiftCard.begin(), m_setLiftCard.end(), nIdx) != m_setLiftCard.end();
}

bool CHorizontalCardListView::LiftCard( size_t nIdx, bool bLift )
{
	if ( nIdx >= _GetCardCnt())
	{
		return false;
	}
	if (IsLift(nIdx) == bLift)
	{
		return true;
	}
	if (bLift)
	{
		m_setLiftCard.insert(nIdx);
	}
	else
	{
		m_setLiftCard.erase(nIdx);
	}
	QPoint oCardPos = _CalcCardPos(nIdx);
	CCardView* pCardView = GetCardView(nIdx);
	pCardView->move(oCardPos);
	return true;
}

void CHorizontalCardListView::SetLiftSize( float fLiftSize )
{
	m_fLiftSize = fLiftSize;
	_ResetCards();
}

size_t CHorizontalCardListView::LiftSize() const
{
	return m_fLiftSize;
}
