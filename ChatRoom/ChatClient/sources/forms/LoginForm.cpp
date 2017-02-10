
#include <QMessageBox>
#include "headers/forms/loginform.h"
#include "headers/ui/ui_loginform.h"
#include "headers/tools/cJSON.h"


LoginForm::LoginForm(QWidget *parent) :QMainWindow(parent),ui(new Ui::ULoginForm())
{
    QString name=this->objectName();
   ui->setupUi(this);
   connect(ui->btn_login,SIGNAL(clicked()),this,SLOT(Login()));
}

LoginForm::~LoginForm()
{
    QMessageBox::about(this,tr("xigou"),tr("xigou end"));
    exit(1);
}

void LoginForm::Login()
{
  QString account = ui->txt_account->text();//账号
  QString pwd = ui->txt_pwd->text();//密码
  if(account.isEmpty()|| pwd.isEmpty())
  {
      QMessageBox::information(0,QString("提示"),QString("账号密码输入全"));
      return;
  }
  char* sendstr="";



}
