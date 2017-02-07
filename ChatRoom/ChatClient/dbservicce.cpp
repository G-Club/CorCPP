#include"dbservice.h"
#include<QtSql>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QMessageBox>
#include<list>

DBServicce::DBServicce()
{
    database =QSqlDatabase::addDatabase(DriverName);//设置要连接的数据库类型
}

DBServicce::DBServicce(QString& drivername, QString& connname)
{

    this->ConnName = connname;
    this->DriverName = drivername;
    database =QSqlDatabase::addDatabase(DriverName,ConnName);//设置要连接的数据库类型
}




bool DBServicce::Open()
{
    bool b=false;
    try
    {
        database.setHostName(HostName);
        database.setPort(Port);//设置端口
        database.setDatabaseName(DatabaseName);//要链接的数据库名称
        database.setUserName(UserName);
        database.setPassword(Password);
        b=database.open();//用户名、密码，成功返回1
        QString error = database.lastError().text();
    }
    catch(exception ex)
    {
        throw "Open Failed";
    }
    return b;
}

bool DBServicce::Open(QString& username, QString& password)
{
    bool b=false;
    try
    {
        database.setHostName(this->HostName);
        database.setPort(this->Port);//设置端口
        database.setDatabaseName(this->DatabaseName);//要链接的数据库名称
        database.setUserName(username);
        database.setPassword(password);
        b=database.open();//用户名、密码，成功返回1
    }
    catch(exception ex)
    {
        throw "Open Failed";
    }
    return b;
}

bool DBServicce::Close()
{
    if(IsOpen)
    {
        database.close();
        this->IsOpen = false;
    }

}



int DBServicce::ExecNonQuery(const QString sql,list<pair<int, QVariant>>& arr_para)
{
  int sign=0;
  if(IsOpen)
  {
      QSqlQuery query(database );

      query.prepare(sql);

      list<pair<int, QVariant>>::iterator itor;

      for( itor=arr_para.begin();itor!= arr_para.end();itor++)
      {
          query.bindValue(itor->first,itor->second);//参数化
      }


      bool b_=query.driver()->hasFeature(QSqlDriver::Transactions);
      query.exec();//执行SQL语句
      if(query.isActive())//是否成功执行了上一条语句
      {
          /*
          int size = query.size();//查出结果的长度
          query.last();//移动到最后一条记录
          query.seek(1);//移动到指定位置
          int at = query.at();//返回当前记录所在索引
          query.first();//移动到第一条记录
          */
          while(query.next())
          {
              QVariant varval= query.value(0);
               sign=varval.toInt();
          }
      }
  }
  return sign;
}

int DBServicce::ExecNonQuery(const QString sql, list<pair<QString, QVariant>>& arr_para)
{
    int sign=0;
    if(IsOpen)
    {
        QSqlQuery query(database );

        query.prepare(sql);

        list<pair<QString, QVariant>>::iterator itor;

        for( itor=arr_para.begin();itor!= arr_para.end();itor++)
        {
            QString f=itor->first;
            QString s=itor->second.toString();
            query.bindValue(itor->first,itor->second);//参数化
        }


        bool b_=query.driver()->hasFeature(QSqlDriver::Transactions);
        query.exec();//执行SQL语句
        if(query.isActive())//是否成功执行了上一条语句
        {
            /*
            int size = query.size();//查出结果的长度
            query.last();//移动到最后一条记录
            query.seek(1);//移动到指定位置
            int at = query.at();//返回当前记录所在索引
            query.first();//移动到第一条记录
            */

        }
    }
    return sign;
}


//返回查询结果
void DBServicce::ExecQuery(const QString sql, list<pair<int, QVariant>>& arr_para)
{
    if(IsOpen)
    {
        QSqlQuery query(database );

        query.prepare(sql);

        list<pair<int, QVariant>>::iterator itor;

        for( itor=arr_para.begin();itor!= arr_para.end();itor++)
        {
            query.bindValue(itor->first,itor->second);//参数化
        }


        bool b_=query.driver()->hasFeature(QSqlDriver::Transactions);
        query.exec();//执行SQL语句
        if(query.isActive())//是否成功执行了上一条语句
        {
            /*
            int size = query.size();//查出结果的长度
            query.last();//移动到最后一条记录
            query.seek(1);//移动到指定位置
            int at = query.at();//返回当前记录所在索引
            query.first();//移动到第一条记录
            */
            while(query.next())
            {
                QVariant varval= query.value(0);
                varval=query.value(1);

            }
        }
    }
}






//返回查询结果
void DBServicce::ExecQuery(const QString sql,list<pair<QString, QVariant>>& arr_para)
{
    if(IsOpen)
    {
        QSqlQuery query(database );
        query.prepare(sql);

        list<pair<QString, QVariant>>::iterator itor;
        for( itor=arr_para.begin();itor!= arr_para.end();itor++)
        {
            query.bindValue(itor->first,itor->second);//参数化
        }


        bool b_=query.driver()->hasFeature(QSqlDriver::Transactions);
        query.exec();//执行SQL语句
        if(query.isActive())//是否成功执行了上一条语句
        {
            int size = query.size();//查出结果的长度
            query.last();//移动到最后一条记录
            query.seek(1);//移动到指定位置
            int at = query.at();//返回当前记录所在索引
            query.first();//移动到第一条记录

            while(query.next())
            {
                QVariant varval= query.value(0);
                varval=query.value(1);
                QString name =query.value(4).toString();

                int a=90;
            }
        }

        QString error = query.lastError().text();
        int ff=60;
    }
}



DBServicce::~DBServicce()
{
    if(IsOpen)
    {
        database.close();
    }
}



