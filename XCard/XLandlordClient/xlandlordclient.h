#ifndef XLANDLORDCLIENT_H
#define XLANDLORDCLIENT_H

#include <QtGui/QMainWindow>
#include "ui_xlandlordclient.h"

class XLandlordClient : public QMainWindow
{
	Q_OBJECT

public:
	XLandlordClient(QWidget *parent = 0, Qt::WFlags flags = 0);
	~XLandlordClient();

private:
	Ui::XLandlordClientClass ui;
};

#endif // XLANDLORDCLIENT_H
