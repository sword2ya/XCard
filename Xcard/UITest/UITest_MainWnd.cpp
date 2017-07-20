#include "stdafx.h"
#include "UITest_MainWnd.h"
#include "ui_TestControl.h"
#include "UITestManager.h"
#include "XCommon.h"
#include "CardView.h"

CUITest_MainWnd::CUITest_MainWnd(void)
{
	Ui_TestControl oUiTestControl;
	oUiTestControl.setupUi(this);
	_InitSubWndPoint(oUiTestControl);
	_InitButtonSlot();

	//setWindowFlags(Qt::FramelessWindowHint);
	_UpdateBtnState();
}

CUITest_MainWnd::~CUITest_MainWnd(void)
{
}

void CUITest_MainWnd::Slot_Start()
{
	g_oUITestManager.Start();
	_UpdateBtnState();
}

void CUITest_MainWnd::Slot_Stop()
{
	g_oUITestManager.Stop();
	_UpdateBtnState();
}

void CUITest_MainWnd::Slot_Next()
{
	g_oUITestManager.Next();
	_UpdateBtnState();
}

void CUITest_MainWnd::Slot_Pre()
{
	g_oUITestManager.Pre();
	_UpdateBtnState();
}

void CUITest_MainWnd::_InitSubWndPoint(const Ui_TestControl &oUiTestControl)
{
	m_pBtnNext = oUiTestControl.btnNext;
	m_pBtnPre = oUiTestControl.btnPre;
	m_pBtnStart = oUiTestControl.btnStart;
	m_pBtnStop = oUiTestControl.btnStop;
}

void CUITest_MainWnd::_InitButtonSlot()
{
	connect(m_pBtnNext, SIGNAL(clicked()), this, SLOT(Slot_Next()));
	connect(m_pBtnPre, SIGNAL(clicked()), this, SLOT(Slot_Pre()));
	connect(m_pBtnStart, SIGNAL(clicked()), this, SLOT(Slot_Start()));
	connect(m_pBtnStop, SIGNAL(clicked()), this, SLOT(Slot_Stop()));
}

void CUITest_MainWnd::_UpdateBtnState()
{
	bool bIsRunning = g_oUITestManager.IsRunning();
	bool bHasPre = bIsRunning && g_oUITestManager.HasPre();
	bool bHasMore = bIsRunning && g_oUITestManager.HasMore();

	m_pBtnStart->setDisabled(bIsRunning);
	m_pBtnStop->setDisabled(!bIsRunning);
	m_pBtnNext->setDisabled(!bHasMore);
	m_pBtnPre->setDisabled(!bHasPre);
}
