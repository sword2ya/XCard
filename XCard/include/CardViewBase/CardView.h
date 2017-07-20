#pragma once
#include "XCommon.h"
#include <QtGui\QAbstractButton>
#include <QtGui/QWidget>




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
	TCardInfo m_stCardInfo;
	QPixmap m_oPixmap;
	bool m_bMouseDown;
};
