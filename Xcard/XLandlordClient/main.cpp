#include "stdafx.h"
#include "xlandlordclient.h"
#include <QtGui/QApplication>

/*

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XLandlordClient w;
	w.show();
	return a.exec();
}

*/
BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

