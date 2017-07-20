#include "stdafx.h"
#include "UITest_VerticalCardListView.h"
#include "VerticalCardListView.h"

CUITest_VerticalCardListView::CUITest_VerticalCardListView(void)
{
	m_pCardListView = NULL;
	m_oTimer.setInterval(200);
	connect(&m_oTimer, SIGNAL(timeout()), this, SLOT(Slot_PushCard()));
	srand(time(NULL));
}

CUITest_VerticalCardListView::~CUITest_VerticalCardListView(void)
{
	if (NULL != m_pCardListView)
	{
		delete m_pCardListView;
		m_pCardListView = NULL;
	}
}


void CUITest_VerticalCardListView::SetUp()
{
	CUITestBase::SetUp();

	if (NULL != m_pCardListView)
	{
		delete m_pCardListView;
		m_pCardListView = NULL;
	}
	m_pCardListView = new CVerticalCardListView;
	m_pCardListView->show();
	m_pCardListView->SetCardSize(QSize(70,100));

	m_oTimer.start();
}

void CUITest_VerticalCardListView::TearDown()
{
	CUITestBase::TearDown();

	if (NULL != m_pCardListView)
	{
		delete m_pCardListView;
		m_pCardListView = NULL;
	}
	m_vtCardInfo.clear();
	m_oTimer.stop();
}

void CUITest_VerticalCardListView::Slot_PushCard()
{
	if (NULL == m_pCardListView )
	{
		return;
	}
	const size_t nMaxCardCnt = 20;
	if (m_vtCardInfo.size() >= nMaxCardCnt )
	{
		return;
	}
	int nCardPoint =  eCardPoint_Min + rand() % (eCardPoint_Max-eCardPoint_Min+1);
	int nCardSuit = eCardSuit_Min + rand() % (eCardSuit_Max-eCardSuit_Min+1);
	if (nCardPoint < eCardPoint_Min || nCardPoint > eCardPoint_Max)
	{
		return;
	}
	if (nCardSuit < eCardSuit_Min || nCardSuit > eCardSuit_Max )
	{
		return;
	}
	TCardInfo stCardInfo;
	stCardInfo.eSuit = (ECardSuit)nCardSuit;
	stCardInfo.ePoint = (ECardPoint)nCardPoint;
	m_vtCardInfo.push_back(stCardInfo);
	m_pCardListView->Clear();

	m_pCardListView->PushbackCard(&m_vtCardInfo[0], m_vtCardInfo.size());
}
