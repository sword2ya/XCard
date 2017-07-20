#ifndef XLANDLORDCLIENTMAIN_H
#define XLANDLORDCLIENTMAIN_H

#include <QtGui/QMainWindow>
#include "ui_xlandlordclientmain.h"

class XlandlordClientMain : public QMainWindow
{
	Q_OBJECT

public:
	XlandlordClientMain(QWidget *parent = 0, Qt::WFlags flags = 0);
	~XlandlordClientMain();

private:
	Ui::XlandlordClientMainClass ui;
};

#endif // XLANDLORDCLIENTMAIN_H
