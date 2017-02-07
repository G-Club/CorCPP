
#include<QApplication>
#include<QtSql>
#include<QDialog>
#include<QFileDialog>
#include<QMessageBox>
#include<iostream>
#include"headers/forms/LoginForm.h"
#include "headers/tools/cJSON.h"

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


   char *out="" ;


   free(out);//释放空间
    a.exec();

    return 1;
}







