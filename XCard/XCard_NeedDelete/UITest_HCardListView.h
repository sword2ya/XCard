#pragma once
#include "UITestBase.h"
#include "XCommon.h"


class CHorizontalCardListView;

class CUITest_HorizontalCardListView : public QObject,public CUITestBase
{
	Q_OBJECT 
	typedef vector<TCardInfo> TVec_CardInfo;
public:
	CUITest_HorizontalCardListView(void);
	~CUITest_HorizontalCardListView(void);

public:

	virtual void SetUp();
	virtual void TearDown();

private slots:
	void Slot_PushCard();

private:
	CHorizontalCardListView *m_pCardListView;
	QTimer m_oTimer;
	TVec_CardInfo m_vtCardInfo;
};
