/********************************************************************************
** Form generated from reading UI file 'landlord.ui'
**
** Created: Wed Aug 2 09:35:31 2017
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANDLORD_H
#define UI_LANDLORD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_MainWnd
{
public:

    void setupUi(QDialog *MainWnd)
    {
        if (MainWnd->objectName().isEmpty())
            MainWnd->setObjectName(QString::fromUtf8("MainWnd"));
        MainWnd->resize(738, 439);

        retranslateUi(MainWnd);

        QMetaObject::connectSlotsByName(MainWnd);
    } // setupUi

    void retranslateUi(QDialog *MainWnd)
    {
        MainWnd->setWindowTitle(QApplication::translate("MainWnd", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWnd: public Ui_MainWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANDLORD_H
