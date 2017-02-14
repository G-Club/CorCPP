/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UMainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *txt_start;
    QPushButton *btn_close;
    QTextEdit *txt_info;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UMainWindow)
    {
        if (UMainWindow->objectName().isEmpty())
            UMainWindow->setObjectName(QStringLiteral("UMainWindow"));



        UMainWindow->resize(602, 400);
        centralwidget = new QWidget(UMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        txt_start = new QPushButton(centralwidget);
        txt_start->setObjectName(QStringLiteral("txt_start"));
        txt_start->setGeometry(QRect(460, 30, 75, 23));
        btn_close = new QPushButton(centralwidget);
        btn_close->setObjectName(QStringLiteral("btn_close"));
        btn_close->setGeometry(QRect(460, 130, 75, 23));
        txt_info = new QTextEdit(centralwidget);
        txt_info->setObjectName(QStringLiteral("txt_info"));
        txt_info->setGeometry(QRect(20, 10, 401, 271));
        txt_info->setReadOnly(true);
        UMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 602, 23));
        UMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(UMainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        UMainWindow->setStatusBar(statusbar);

        retranslateUi(UMainWindow);

        QMetaObject::connectSlotsByName(UMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UMainWindow)
    {
        UMainWindow->setWindowTitle(QApplication::translate("UMainWindow", "MainWindow", Q_NULLPTR));
        txt_start->setText(QApplication::translate("UMainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        btn_close->setText(QApplication::translate("UMainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
        txt_info->setPlaceholderText(QApplication::translate("UMainWindow", "some info", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UMainWindow: public Ui_UMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
