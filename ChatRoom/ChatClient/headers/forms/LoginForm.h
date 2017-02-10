#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
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


class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    QWidget *centralWidget;
    QPushButton *btn_login;
    QLineEdit *txt_account;
    QLineEdit *txt_pwd;
    QLabel *label;
    QLabel *label_2;

    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private:

private slots:
    void Login();
};

#endif // LOGINFORM_H
