#include "stdafx.h"
#include "UITestManager.h"
#include "UITest_CCard.h"
#include "UITest_HCardListView.h"
#include "UITest_VerticalCardListView.h"


#define REGISTER_TEST_CLASS(TestClass) g_oUITestManager.GetTestObjectFactory()->RegisterTestClass(#TestClass, new __CUITest_ObjectFactoryHelper<TestClass>)


static void UITest_InitTests()
{
	REGISTER_TEST_CLASS(CUITest_CCard);
	REGISTER_TEST_CLASS(CUITest_HorizontalCardListView);
	REGISTER_TEST_CLASS(CUITest_VerticalCardListView);
}

static void UITest_PrepareTestObj(const char* szFilterName)
{
	CUITestObjectFactory* pTestObjFactory = g_oUITestManager.GetTestObjectFactory();
	size_t nCount = pTestObjFactory->DoFilter(szFilterName);
	for (size_t i = 0; i < nCount; ++i)
	{
		CUITestBase* pTestObj = pTestObjFactory->CreateTestObj(i);
		if (NULL != pTestObj)
		{
			g_oUITestManager.AddTestObj(pTestObj);
		}
	}
}