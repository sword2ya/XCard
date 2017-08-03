// MainTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <QtCore\QThread>
#include <QtGui\QAction>


csmsg::TCSMessage g_stMessagePackage;


class CMainThread : public QThread
{
public:
	CMainThread(int nArgc, char* pArgv[])
	{
		m_nArgc = nArgc;
		m_pArgv = pArgv;
	}
	virtual void run()
	{
		::testing::InitGoogleTest(&m_nArgc, m_pArgv);
		RUN_ALL_TESTS();
	}
private:
	int m_nArgc;
	char** m_pArgv;
};


int _tmain(int argc, _TCHAR* argv[])
{
	CMainThread oMainThread(argc, argv);
	oMainThread.start(QThread::HighPriority);
	while (true )
	{
		if (oMainThread.isFinished())
		{
			return 0;
		}
		Sleep(50);
	}
	return 0;
}

