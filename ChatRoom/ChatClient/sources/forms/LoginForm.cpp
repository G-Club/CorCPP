
#include <QMessageBox>
#include "headers/forms/loginform.h"
#include "headers/ui/ui_loginform.h"
#include "headers/tools/cJSON.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <errno.h>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>

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
    //{\"account\":\"123456\",\"pwd\":\"456123\",\"key\":\"iskey\",\"timestamp\":\"\"}
    QString sendstr="{\"account\":\""+account+"\",\"pwd\":\""+pwd+"\",\"key\":\"iskey\",";
    time_t timer;//从1970年到现在经过了多少秒
    time(&timer);//
    /*
struct tm
{
    int tm_sec; //秒，正常范围0-59， 但允许至61
    int tm_min;  //分钟，0-59
    int tm_hour; //小时， 0-23
    int tm_mday; //日，即一个月中的第几天，1-31
    int tm_mon;  //月， 从一月算起，0-11  1+p->tm_mon;
    int tm_year;  //年， 从1900至今已经多少年  1900＋ p->tm_year;
    int tm_wday; //星期，一周中的第几天， 从星期日算起，0-6
    int tm_yday; //从今年1月1日到目前的天数，范围0-365
    int tm_isdst; //日光节约时间的旗标
};
*/
    struct tm* localtm ;
    localtm  =localtime(&timer);

    sendstr+="\"timestamp\":\""+QString::number(timer,10)+"\"}";

    QTcpSocket *client = new QTcpSocket(this);
    client->connect(QHostAddress("127.0.0.1"),6123);




    int a=0;
}
