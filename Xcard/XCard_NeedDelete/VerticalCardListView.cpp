#include "stdafx.h"
#include "VerticalCardListView.h"


CVerticalCardListView::CVerticalCardListView(void)
{
	SetOverlap(6.f/7);
}

CVerticalCardListView::~CVerticalCardListView(void)
{
}

QSize CVerticalCardListView::sizeHint() const
{
	QSize oSizeRet;
	QSize oCardSize = CardSize();
	oSizeRet.setWidth(oCardSize.width());
	size_t nOverlapSize = Overlap()*oCardSize.width();
	size_t nCardCount = _GetCardCnt();
	if (nCardCount == 0)
	{
		oSizeRet.setHeight(oCardSize.height());
	}
	else
	{
		oSizeRet.setHeight((_GetCardCnt()-1) * (oCardSize.height()-nOverlapSize) + oCardSize.height() );
	}
	return oSizeRet;
}

QPoint CVerticalCardListView::_CalcCardPos( size_t nIdx ) const
{
	QPoint oPosRet;
	QSize oCardSize = CardSize();
	size_t nOverlapSize = Overlap()*oCardSize.width();
	oPosRet.setX(0);
	oPosRet.setY(nIdx * (oCardSize.height()-nOverlapSize) );
	return oPosRet;
}
