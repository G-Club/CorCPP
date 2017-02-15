
#include <QMessageBox>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <errno.h>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QtNetwork>
#include "headers/forms/loginform.h"
#include "headers/forms/mainform.h"
#include "headers/tools/cJSON.h"



LoginForm::LoginForm(QWidget *parent) :QMainWindow(parent),ui(new Ui::ULoginForm())
{
    QString name=this->objectName();
    ui->setupUi(this);
    connect(ui->btn_login,SIGNAL(clicked(bool)),this,SLOT(on_btn_login_clicked(bool)));
}

LoginForm::~LoginForm()
{
    QMessageBox::about(this,tr("xigou"),tr("xigou end"));
    exit(1);
}
void LoginForm::on_btn_login_clicked(bool checked)
{
    QString account = ui->txt_account->text().trimmed();//账号
    QString pwd = ui->txt_pwd->text().trimmed();//密码

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

    /*
socket打開后首先進入  查找主機狀態，查找到了，會有hostFound（）信號發出。你可以把這個信號綁定一個槽，
在槽裏改變一個bool變量以標記是否查找到主機了。查找到了主機后，socket進入正在連接狀態，連接建立后，
會有connected（）信號發出。你可以把這個信號綁定一個槽，在槽裏改變一個bool變量以標記是否連接成功到主機了。
之後，socket進入已連接狀態。


任何连接或者进行连接立即关闭并且QSocket进入HostLookup 状态查找功发射hostFound()始TCP连接
并且进入Connecting状态连接功发射connected()并且进入Connected状态任何现错误发射error()
*/
    QTcpSocket *client = new QTcpSocket(this);

     client->connectToHost(QHostAddress("127.0.0.1"),6123);

     connect(client,SIGNAL(hostFound()),this,SLOT(connError()));
     connect(client,SIGNAL(connected()),this,SLOT(connSucc()));
    connect(client,SIGNAL(disconnected()),this,SLOT(onDisconnect()));
            int a=0;

}


void LoginForm::on_btn_login_toggled(bool checked)
{


}

void LoginForm::ConnSucc()
{
    QMessageBox::about(0,QApplication::tr("socket"),tr("connected success"));
}

void LoginForm::ConnError()
{
    QMessageBox::about(0,QApplication::tr("socket"),tr("connected error"));
}

void LoginForm::onDisconnect()
{
 QMessageBox::about(0,QApplication::tr("socket"),tr("SOCKET Disconnect"));
}
