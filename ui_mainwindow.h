/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <checklabel.h>
#include <mylabel.h>
#include <prelabel.h>

QT_BEGIN_NAMESPACE

class Ui_Mainwindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelTitle;
    QPushButton *pushButtonMined;
    QPushButton *pushButtonClose;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_3;
    myLabel *label;
    QWidget *tab_2;
    preLabel *curlabel;
    QPushButton *pushButton;
    QWidget *tab_3;
    QPushButton *pushButtonMergeAll;
    checkLabel *checklabel;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Mainwindow)
    {
        if (Mainwindow->objectName().isEmpty())
            Mainwindow->setObjectName(QStringLiteral("Mainwindow"));
        Mainwindow->resize(1126, 653);
        centralWidget = new QWidget(Mainwindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 24));
        horizontalLayout_7 = new QHBoxLayout(widget);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        labelTitle = new QLabel(widget);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));
        QFont font;
        font.setFamily(QStringLiteral("MV Boli"));
        font.setPointSize(14);
        labelTitle->setFont(font);

        horizontalLayout_7->addWidget(labelTitle);

        pushButtonMined = new QPushButton(widget);
        pushButtonMined->setObjectName(QStringLiteral("pushButtonMined"));
        pushButtonMined->setMaximumSize(QSize(24, 24));
        QFont font1;
        font1.setPointSize(12);
        pushButtonMined->setFont(font1);

        horizontalLayout_7->addWidget(pushButtonMined);

        pushButtonClose = new QPushButton(widget);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setMaximumSize(QSize(24, 24));
        pushButtonClose->setFont(font1);

        horizontalLayout_7->addWidget(pushButtonClose);


        verticalLayout_2->addWidget(widget);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new myLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);


        horizontalLayout->addLayout(horizontalLayout_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        curlabel = new preLabel(tab_2);
        curlabel->setObjectName(QStringLiteral("curlabel"));
        curlabel->setGeometry(QRect(470, 180, 181, 151));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(940, 130, 89, 24));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(28);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton->setFont(font2);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButtonMergeAll = new QPushButton(tab_3);
        pushButtonMergeAll->setObjectName(QStringLiteral("pushButtonMergeAll"));
        pushButtonMergeAll->setGeometry(QRect(0, 0, 141, 61));
        QFont font3;
        font3.setFamily(QStringLiteral("Bauhaus 93"));
        font3.setPointSize(22);
        pushButtonMergeAll->setFont(font3);
        checklabel = new checkLabel(tab_3);
        checklabel->setObjectName(QStringLiteral("checklabel"));
        checklabel->setGeometry(QRect(140, 60, 781, 321));
        tabWidget->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tabWidget);

        Mainwindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Mainwindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Mainwindow->setStatusBar(statusBar);

        retranslateUi(Mainwindow);
        QObject::connect(pushButtonMined, SIGNAL(clicked()), Mainwindow, SLOT(showMinimized()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *Mainwindow)
    {
        Mainwindow->setWindowTitle(QApplication::translate("Mainwindow", "Mainwindow", Q_NULLPTR));
        labelTitle->setText(QApplication::translate("Mainwindow", "<html><head/><body><p><span style=\" font-size:12pt;\">LicenseSplit</span></p></body></html>", Q_NULLPTR));
        pushButtonMined->setText(QApplication::translate("Mainwindow", "\342\231\245", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("Mainwindow", "\342\234\230", Q_NULLPTR));
        label->setText(QApplication::translate("Mainwindow", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Mainwindow", "\345\210\206\345\211\262", Q_NULLPTR));
        curlabel->setText(QApplication::translate("Mainwindow", "TextLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Mainwindow", "\357\274\213", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Mainwindow", "\346\240\207\346\263\250", Q_NULLPTR));
        pushButtonMergeAll->setText(QApplication::translate("Mainwindow", "\345\220\210\345\271\266", Q_NULLPTR));
        checklabel->setText(QApplication::translate("Mainwindow", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Mainwindow", "\346\240\270\351\252\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Mainwindow: public Ui_Mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
