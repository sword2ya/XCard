#include "stdafx.h"
#include "TestBase.h"


TEST(SetupTest, SetupAndTearDown)
{
	CTestBase::SetUpTestCase();
	CTestBase::TearDownTestCase();
}