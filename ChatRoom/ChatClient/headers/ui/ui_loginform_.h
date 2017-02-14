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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDesktopWidget>
#include <QApplication>


QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:

    QWidget *centralWidget;
    QPushButton *btn_login;
    QLineEdit *txt_account;
    QLineEdit *txt_pwd;
    QLabel *label;
    QLabel *label_2;
    void setupUi(QMainWindow *LoginForm)
    {

        if (LoginForm->objectName().isEmpty())
        {
            LoginForm->setObjectName(QStringLiteral("LoginForm"));
        }

        centralWidget = new QWidget(LoginForm);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));

        btn_login = new QPushButton(centralWidget);
        btn_login->setText(QString("登录"));
        btn_login->setObjectName(QStringLiteral("btn_login"));
        btn_login->setGeometry(QRect(260, 180, 75, 23));
        btn_login->setFocusPolicy(Qt::NoFocus);

        txt_account = new QLineEdit(centralWidget);
        txt_account->setObjectName(QStringLiteral("lineEdit"));
        txt_account->setGeometry(QRect(130, 60, 221, 31));
        txt_account->setPlaceholderText(QStringLiteral("input your account "));
        txt_account->setText(QApplication::tr("10005"));

        txt_pwd = new QLineEdit(centralWidget);
        txt_pwd->setObjectName(QStringLiteral("lineEdit_2"));
        txt_pwd->setGeometry(QRect(130, 110, 221, 31));
        txt_pwd->setMaxLength(16);
        txt_pwd->setEchoMode(QLineEdit::Password);
        txt_pwd->setPlaceholderText(QStringLiteral("input your password"));
        txt_pwd->setText(QApplication::tr("123456"));

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 70, 36, 16));
        label->setText(QString("账号:"));
        QFont font;
        font.setFamily(QStringLiteral("Aharoni"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 120, 36, 16));
        label_2->setFont(font);
        label_2->setText(QString("密码:"));
        LoginForm->setCentralWidget(centralWidget);

        LoginForm->setWindowFlags(LoginForm->windowFlags()&~Qt::WindowMaximizeButtonHint);
        LoginForm->resize(455,280);
        QDesktopWidget* p_dw =QApplication::desktop();
        int dw =p_dw->width();
        int dh = p_dw->height();
        LoginForm->move((dw-LoginForm->width())/2,(dh-LoginForm->height())/2);

        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QMainWindow *LoginForm)
    {
        LoginForm->setWindowTitle(QApplication::translate("LoginForm", "LoginForm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
class ULoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
