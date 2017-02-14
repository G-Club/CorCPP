/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ULoginForm
{
public:
    QWidget *centralWidget;
    QPushButton *btn_login;
    QLineEdit *txt_account;
    QLineEdit *txt_pwd;
    QLabel *lab_account;
    QLabel *lab_pwd;

    void setupUi(QMainWindow *ULoginForm)
    {
        if (ULoginForm->objectName().isEmpty())
            ULoginForm->setObjectName(QStringLiteral("ULoginForm"));
        ULoginForm->resize(395, 256);
        centralWidget = new QWidget(ULoginForm);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btn_login = new QPushButton(centralWidget);
        btn_login->setObjectName(QStringLiteral("btn_login"));
        btn_login->setGeometry(QRect(240, 180, 75, 23));
        btn_login->setFocusPolicy(Qt::NoFocus);
        txt_account = new QLineEdit(centralWidget);
        txt_account->setObjectName(QStringLiteral("txt_account"));
        txt_account->setGeometry(QRect(110, 60, 221, 31));
        txt_pwd = new QLineEdit(centralWidget);
        txt_pwd->setObjectName(QStringLiteral("txt_pwd"));
        txt_pwd->setGeometry(QRect(110, 110, 221, 31));
        txt_pwd->setMaxLength(16);
        txt_pwd->setEchoMode(QLineEdit::Password);
        lab_account = new QLabel(centralWidget);
        lab_account->setObjectName(QStringLiteral("lab_account"));
        lab_account->setGeometry(QRect(40, 60, 81, 31));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        lab_account->setFont(font);
        lab_pwd = new QLabel(centralWidget);
        lab_pwd->setObjectName(QStringLiteral("lab_pwd"));
        lab_pwd->setGeometry(QRect(30, 110, 81, 41));
        lab_pwd->setFont(font);
        ULoginForm->setCentralWidget(centralWidget);

        retranslateUi(ULoginForm);

        QMetaObject::connectSlotsByName(ULoginForm);
    } // setupUi

    void retranslateUi(QMainWindow *ULoginForm)
    {
        ULoginForm->setWindowTitle(QApplication::translate("ULoginForm", "Login", Q_NULLPTR));
        btn_login->setText(QApplication::translate("ULoginForm", "Login", Q_NULLPTR));
        txt_account->setText(QApplication::translate("ULoginForm", "10004", Q_NULLPTR));
        txt_account->setPlaceholderText(QApplication::translate("ULoginForm", "input your account", Q_NULLPTR));
        txt_pwd->setText(QApplication::translate("ULoginForm", "123456", Q_NULLPTR));
        txt_pwd->setPlaceholderText(QApplication::translate("ULoginForm", "input password", Q_NULLPTR));
        lab_account->setText(QApplication::translate("ULoginForm", "account:", Q_NULLPTR));
        lab_pwd->setText(QApplication::translate("ULoginForm", "password", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ULoginForm: public Ui_ULoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
