#include "stdafx.h"
#include "xcard.h"
#include <QtGui/QApplication>
#include "CardView.h"
#include "UITestRegister.h"
#include "UITest_MainWnd.h"

static void Test()
{
	UITest_InitTests();
	UITest_PrepareTestObj(NULL);
	CUITest_MainWnd *pTestControl = new CUITest_MainWnd;
	pTestControl->show();
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	if (1)
	{
		Test();
	}
	else
	{
		XCard w;
		w.show();
	}
	return a.exec();
}
