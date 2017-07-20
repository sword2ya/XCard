#include "stdafx.h"
#include "xlandlordclientmain.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XlandlordClientMain w;
	w.show();
	return a.exec();
}
