
#include<QApplication>
#include<QtSql>
#include<QDialog>
#include<QFileDialog>
#include<QMessageBox>
#include<iostream>
#include <QDesktopWidget>
#include"headers/forms/LoginForm.h"
#include "headers/tools/cJSON.h"

using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginForm window;

    window.setWindowTitle(QString("登录"));
    window.setFixedSize(300,200);//设置FixedSize以后 就不可以改变窗体大小
   //window.setAttribute(Qt::WA_DeleteOnClose,true);//没有任何内存占用的时候直接使用Qt::WA_DeleteOnClose会导致内存越界 报错Critical error detected c0000374


   /*QT中调用close时，默认情况下是不会释放new的内存的，只是干掉了界面，但内存中还有，这个时候有点类似hide函数的功能。
    virtual void setVisible(bool visible);
    inline void setHidden(bool hidden) { setVisible(!hidden); }
    inline void show() { setVisible(true); }
    inline void hide() { setVisible(false); }
但是，在当前窗体类的构造函数中如果设置了this->setAttribute(Qt::WA_DeleteOnClose,true);
那么close时就会在内存中干掉界面，释放new的内存，下次再使用这块内存时（比如show）就会段错误。实际过程是delete了堆内存，并且还调用了析构函数。
*/
     int deskw = QApplication::desktop()->width();
     int deskh =QApplication::desktop()->height();
    window.show();
    window.move ((deskw - window.width())/2,(deskh- window.height())/2);

    a.exec();

    return 1;
}







