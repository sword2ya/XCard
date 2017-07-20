/********************************************************************************
** Form generated from reading UI file 'xcard.ui'
**
** Created: Tue Jun 6 17:42:15 2017
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XCARD_H
#define UI_XCARD_H

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

class Ui_XCardClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *XCardClass)
    {
        if (XCardClass->objectName().isEmpty())
            XCardClass->setObjectName(QString::fromUtf8("XCardClass"));
        XCardClass->resize(600, 400);
        menuBar = new QMenuBar(XCardClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        XCardClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(XCardClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        XCardClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(XCardClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        XCardClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(XCardClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        XCardClass->setStatusBar(statusBar);

        retranslateUi(XCardClass);

        QMetaObject::connectSlotsByName(XCardClass);
    } // setupUi

    void retranslateUi(QMainWindow *XCardClass)
    {
        XCardClass->setWindowTitle(QApplication::translate("XCardClass", "XCard", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class XCardClass: public Ui_XCardClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XCARD_H
