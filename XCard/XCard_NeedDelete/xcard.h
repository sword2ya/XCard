#ifndef XCARD_H
#define XCARD_H

#include <QtGui/QMainWindow>
#include "ui_xcard.h"

class XCard : public QMainWindow
{
	Q_OBJECT

public:
	XCard(QWidget *parent = 0, Qt::WFlags flags = 0);
	~XCard();

private:
	Ui::XCardClass ui;
};

#endif // XCARD_H
