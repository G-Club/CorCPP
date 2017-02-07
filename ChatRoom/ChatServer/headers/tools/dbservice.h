#ifndef DBSERVICE_H
#define DBSERVICE_H
#include <iostream>
#include<string>
#include<QString>
#include<QtSql/QSql>
#include<QtSql>
#include<map>
using namespace std;

class DBServicce
{
public:
    DBServicce();
     DBServicce(QString& drivername, QString& connname);
    ~DBServicce();
    QString DriverName="QMYSQL";//驱动名称
    QString HostName;//主机名 即IP地址
    QString DatabaseName;//要连接的数据库名称
    unsigned int Port:20;//端口号，有20位够用了
    QString UserName;//用户名
    QString Password;//密码
    QString ConnName="Default";//链接名称

    int ExecNonQuery(const QString sql, list<pair<int, QVariant>>& arr_para);
     int ExecNonQuery(const QString sql,list<pair<QString, QVariant>>& arr_para);
    void ExecQuery(const QString sql,  list<pair<QString, QVariant>>& arr_para);
    void ExecQuery(const QString sql, list<pair<int, QVariant>>& arr_para);


    void ExecReader(const QString sql);
    bool Open();
    bool Open(QString& username, QString& password);
    bool Close();
private:
QSqlDatabase database ;//设置要连接的数据库类型
 QSqlQuery query ;
 bool IsOpen;
protected:


};






#endif // DBSERVICE_H




