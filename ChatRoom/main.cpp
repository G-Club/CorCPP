#include"LoginForm.h"
#include<QApplication>
#include<QtSql>
#include<QDialog>
#include<QFileDialog>
#include<QMessageBox>
#include"dbservice.h"
#include<iostream>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm window;
    window.setWindowTitle(QString("登录"));
    window.setFixedSize(405,280);//设置FixedSize以后 就不可以改变窗体大小
    window.setAttribute(Qt::WA_DeleteOnClose,true);/*QT中调用close时，默认情况下是不会释放new的内存的，只是干掉了界面，但内存中还有，这个时候有点类似hide函数的功能。
    virtual void setVisible(bool visible);
    inline void setHidden(bool hidden) { setVisible(!hidden); }
    inline void show() { setVisible(true); }
    inline void hide() { setVisible(false); }
但是，在当前窗体类的构造函数中如果设置了this->setAttribute(Qt::WA_DeleteOnClose,true);
那么close时就会在内存中干掉界面，释放new的内存，下次再使用这块内存时（比如show）就会段错误。实际过程是delete了堆内存，并且还调用了析构函数。
*/
    QDesktopWidget* p_dw = QApplication::desktop();//获取桌面可用大小

    window.show();
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
    /*
    else
    {
        list< pair<QString,QVariant>> _list;
       // _list.push_back(pair<QString,QVariant>(":name","Green"));
       // _list.push_back(pair<QString,QVariant>(":age",28));
        //_list.push_back(pair<QString,QVariant>(":sex",1));

        //_list.push_back(pair<QString,QVariant>(":addr","圣安东尼奥"));
       //_list.push_back(pair<QString,QVariant>(":bir","1987-04-15 08:19:39"));

        //int count= db.ExecNonQuery("update user set sex=:sex where uid=1;",_list);
       // QMessageBox::information(0,QString("count"),static_cast<QString>(count));
        // w.close();
    }
*/
    a.exec();

    return 1;
}







