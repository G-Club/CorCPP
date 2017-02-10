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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UMainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *UMainWindow)
    {
        if (UMainWindow->objectName().isEmpty())
            UMainWindow->setObjectName(QStringLiteral("UMainWindow"));
        UMainWindow->resize(620, 500);
        centralWidget = new QWidget(UMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 280, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(400, 280, 75, 23));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(80, 40, 421, 221));
        UMainWindow->setCentralWidget(centralWidget);

        retranslateUi(UMainWindow);

        QMetaObject::connectSlotsByName(UMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UMainWindow)
    {
        UMainWindow->setWindowTitle(QApplication::translate("UMainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("UMainWindow", "PushButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("UMainWindow", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UMainWindow: public Ui_UMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
