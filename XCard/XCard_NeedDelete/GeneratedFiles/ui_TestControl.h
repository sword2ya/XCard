/********************************************************************************
** Form generated from reading UI file 'TestControl.ui'
**
** Created: Tue Jun 6 17:42:14 2017
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTCONTROL_H
#define UI_TESTCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestControl
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPre;
    QVBoxLayout *verticalLayout;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnNext;

    void setupUi(QWidget *TestControl)
    {
        if (TestControl->objectName().isEmpty())
            TestControl->setObjectName(QString::fromUtf8("TestControl"));
        TestControl->resize(277, 72);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TestControl->sizePolicy().hasHeightForWidth());
        TestControl->setSizePolicy(sizePolicy);
        TestControl->setMinimumSize(QSize(277, 72));
        TestControl->setMaximumSize(QSize(277, 72));
        horizontalLayout = new QHBoxLayout(TestControl);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnPre = new QPushButton(TestControl);
        btnPre->setObjectName(QString::fromUtf8("btnPre"));

        horizontalLayout->addWidget(btnPre);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnStart = new QPushButton(TestControl);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        verticalLayout->addWidget(btnStart);

        btnStop = new QPushButton(TestControl);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));

        verticalLayout->addWidget(btnStop);


        horizontalLayout->addLayout(verticalLayout);

        btnNext = new QPushButton(TestControl);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));

        horizontalLayout->addWidget(btnNext);


        retranslateUi(TestControl);

        QMetaObject::connectSlotsByName(TestControl);
    } // setupUi

    void retranslateUi(QWidget *TestControl)
    {
        TestControl->setWindowTitle(QApplication::translate("TestControl", "UI\346\265\213\350\257\225\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        btnPre->setText(QApplication::translate("TestControl", "\344\270\212\344\270\200\351\241\271", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("TestControl", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("TestControl", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        btnNext->setText(QApplication::translate("TestControl", "\344\270\213\344\270\200\351\241\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestControl: public Ui_TestControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTCONTROL_H
