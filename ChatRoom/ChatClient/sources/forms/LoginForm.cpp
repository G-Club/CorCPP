#include "headers/forms/LoginForm.h"
#include<QMessageBox>
#include<QDialog>
#include <QtUiTools/QUiLoader>
#include <headers/ui/ui_loginform.h>

LoginForm::LoginForm(QWidget *parent) : QMainWindow(parent),ui(new Ui::LoginForm)
{

    this->lab_name.setParent(this);
     this->lab_pwd.setParent(this);
     this->lab_name.setText(tr("用户名"));
     this->lab_pwd.setText(tr("密码"));
     ui->setupUi(this);

}
void LoginForm::closeEvent(QCloseEvent *event)
{
//this->close();
    exit(1);
}

LoginForm::~LoginForm()
{
     delete ui;
   QMessageBox::information(0,tr("lala"),tr("xigou"));
}
