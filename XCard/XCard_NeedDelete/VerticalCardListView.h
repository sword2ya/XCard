#pragma once
#include "CardListView.h"

class CVerticalCardListView :
	public CCardListView
{
public:
	CVerticalCardListView(void);
	~CVerticalCardListView(void);

public:
	virtual QSize sizeHint() const;

protected:
	virtual QPoint _CalcCardPos( size_t nIdx ) const ;
	

};
