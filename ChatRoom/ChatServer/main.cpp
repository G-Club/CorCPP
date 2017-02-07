#include "headers/forms/mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "headers/tools/dbservice.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    /*
    //就是为数据库连接取一个名称，以后看到它的时候你就知道连接的是哪个数据库，包括用户名密码等都集成在里面了。。可以拿来直接用
    QSqlDatabase database =QSqlDatabase::addDatabase("QMYSQL","CONN_MYSQL");//设置要连接的数据库类型
    database.setHostName("localhost");
    database.setPort(3306);//设置端口
    database.setDatabaseName("chat");//要链接的数据库名称
    database.setUserName("root");
    database.setPassword("123456");
    bool b=database.open();//用户名、密码，成功返回1

    if(!b)
    {
        QString error = database.lastError().text();
        QMessageBox::information(0,QString("提示"),QString("error:\n")+error);
    }
    else
    {
        QMessageBox::information(0,QString("提示"),QString("成功"));
         w.close();
    }

*/



   /*

    DBServicce db ;
    //db.DatabaseName="chat";
    db.DatabaseName="homework";
    db.DriverName ="QMYSQL";
    db.ConnName="CONN_MYSQL";
    db.HostName ="localhost";
    db.Port =3306;
    db.Password="123456";
    db.UserName="root";
    bool b=db.Open();
    if(!b)
    {
        QMessageBox::information(0,QString("提示"),QString("error:\n"));
    }

*/


    return a.exec();
}
