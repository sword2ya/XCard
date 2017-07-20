#pragma once
#include "ui_CCard.h"
#include "XCommon.h"


class CCardView :
	public QAbstractButton
{
public:
	CCardView(void);
	~CCardView(void);

	void SetCard(ECardPoint ePoint, ECardSuit eSuit);

public:
	virtual QSize sizeHint() const;
	virtual void paintEvent(QPaintEvent *);
	
private:
	void _UpdateBackImage();

private:
	Ui_Card m_uiCard;
	TCardInfo m_stCardInfo;
	QPixmap m_oPixmap;
	bool m_bMouseDown;
};
