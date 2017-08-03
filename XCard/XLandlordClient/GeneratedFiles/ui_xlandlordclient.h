/********************************************************************************
** Form generated from reading UI file 'xlandlordclient.ui'
**
** Created: Wed Aug 2 09:35:29 2017
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XLANDLORDCLIENT_H
#define UI_XLANDLORDCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_XLandlordClientClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XLandlordClientClass)
    {
        if (XLandlordClientClass->objectName().isEmpty())
            XLandlordClientClass->setObjectName(QString::fromUtf8("XLandlordClientClass"));
        XLandlordClientClass->resize(600, 400);
        menuBar = new QMenuBar(XLandlordClientClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        XLandlordClientClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XLandlordClientClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        XLandlordClientClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(XLandlordClientClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        XLandlordClientClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(XLandlordClientClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        XLandlordClientClass->setStatusBar(statusBar);

        retranslateUi(XLandlordClientClass);

        QMetaObject::connectSlotsByName(XLandlordClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *XLandlordClientClass)
    {
        XLandlordClientClass->setWindowTitle(QApplication::translate("XLandlordClientClass", "XLandlordClient", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class XLandlordClientClass: public Ui_XLandlordClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XLANDLORDCLIENT_H
