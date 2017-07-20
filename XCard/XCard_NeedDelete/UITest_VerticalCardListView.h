#pragma once
#include "UITestBase.h"
#include "XCommon.h"


class CVerticalCardListView;

class CUITest_VerticalCardListView : public QObject,  public CUITestBase
{
	Q_OBJECT
	typedef vector<TCardInfo> TVec_CardInfo;
public:
	CUITest_VerticalCardListView(void);
	~CUITest_VerticalCardListView(void);
public:
	virtual void SetUp();
	virtual void TearDown();

private slots:
	void Slot_PushCard();
private:
	CVerticalCardListView* m_pCardListView;
	QTimer m_oTimer;
	TVec_CardInfo m_vtCardInfo;

};
