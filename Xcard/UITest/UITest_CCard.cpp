#include "stdafx.h"
#include "UITest_CCard.h"

CUITest_CCard::CUITest_CCard(void)
{
	m_oCardInfo.ePoint = eCardPoint_Min;
	m_oCardInfo.eSuit = eCardSuit_Max;
	m_oCardView.SetCard(m_oCardInfo.ePoint, m_oCardInfo.eSuit);
	m_oCardView.setFixedSize(52, 75);

	m_oTransferTimer.setInterval(500);
	connect(&m_oTransferTimer,SIGNAL(timeout()),this,SLOT(Slot_OnTransferTimer()));

}

CUITest_CCard::~CUITest_CCard(void)
{
}

void CUITest_CCard::SetUp()
{
	CUITestBase::SetUp();
	m_oTransferTimer.start();
	m_oCardView.show();
}

void CUITest_CCard::TearDown()
{
	CUITestBase::TearDown();
	m_oTransferTimer.stop();
	m_oCardView.hide();
}

void CUITest_CCard::Slot_OnTransferTimer()
{
	bool bAddSuit = false;
	if (m_oCardInfo.ePoint >= eCardPoint_Max)
	{
		m_oCardInfo.ePoint = eCardPoint_Min;
		bAddSuit = true;
	}
	else
	{
		m_oCardInfo.ePoint = (ECardPoint)(m_oCardInfo.ePoint+1);
	}

	if (bAddSuit)
	{
		if (m_oCardInfo.eSuit >= eCardSuit_Max)
		{
			m_oCardInfo.eSuit = eCardSuit_Min;
		}
		else
		{
			m_oCardInfo.eSuit = (ECardSuit)(m_oCardInfo.eSuit + 1);
		}
	}
	m_oCardView.SetCard(m_oCardInfo.ePoint, m_oCardInfo.eSuit);
}
