#include "stdafx.h"
#include <QtGui/QApplication>
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
	Test();
	return a.exec();
}
