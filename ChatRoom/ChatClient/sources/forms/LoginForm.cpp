
#include <QMessageBox>
#include "headers/forms/loginform.h"
#include "headers/ui/ui_loginform.h"
#include "headers/tools/cJSON.h"


LoginForm::LoginForm(QWidget *parent) :QMainWindow(parent)
{
    QString name=this->objectName();
    if (this->objectName().isEmpty())
    {
        this->setObjectName(QStringLiteral("LoginForm"));
    }

    this->centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    btn_login = new QPushButton(centralWidget);
    btn_login->setText(QString("登录"));
    btn_login->setObjectName(QStringLiteral("btn_login"));
    btn_login->setGeometry(QRect(260, 180, 75, 23));
    btn_login->setFocusPolicy(Qt::NoFocus);
    txt_account = new QLineEdit(centralWidget);
    txt_account->setObjectName(QStringLiteral("lineEdit"));
    txt_account->setGeometry(QRect(130, 60, 221, 31));

    txt_pwd = new QLineEdit(centralWidget);
    txt_pwd->setObjectName(QStringLiteral("lineEdit_2"));
    txt_pwd->setGeometry(QRect(130, 110, 221, 31));
    txt_pwd->setMaxLength(16);
    txt_pwd->setEchoMode(QLineEdit::Password);
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
    this->setCentralWidget(centralWidget);

    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->resize(375,280);
    QDesktopWidget* p_dw =QApplication::desktop();
    int dw =p_dw->width();
    int dh = p_dw->height();
    this->move((dw-this->width())/2,(dh-this->height())/2);

    connect(this->btn_login,SIGNAL(clicked()),this,SLOT(Login()));
}

LoginForm::~LoginForm()
{
    QMessageBox::about(this,tr("xigou"),tr("xigou end"));
    exit(1);
}

void LoginForm::Login()
{
  QString account = this->txt_account->text();//账号
  QString pwd = this->txt_pwd->text();//密码
  if(account.isEmpty()|| pwd.isEmpty())
  {
      QMessageBox::information(0,QString("提示"),QString("账号密码输入全"));
      return;
  }
  char* sendstr="";



}
