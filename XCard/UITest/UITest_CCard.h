#pragma once
#include "UITestBase.h"
#include "CardView.h"
#include "XCommon.h"

class CUITest_CCard :  public QObject, public CUITestBase
{
	Q_OBJECT
public:
	CUITest_CCard(void);
	~CUITest_CCard(void);

	virtual void SetUp();
	virtual void TearDown();

public slots:
	void Slot_OnTransferTimer();

private:
	CCardView m_oCardView;
	TCardInfo m_oCardInfo;
	QTimer m_oTransferTimer;
};
