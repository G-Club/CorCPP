
#include "headers/forms/mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::UMainWindow)
{
    ui->setupUi(this);
  connect(ui->btn_start,SIGNAL(clicked(bool)),this,SLOT(on_btn_start_clicked(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked(bool checked)
{
   if(!server->listen(QHostAddress::Any,6123))
   {
       QString value= this->ui->txt_info->toPlainText();
       value+="开启网络服务失败\n";
       return;
   }
    connect(server,SIGNAL(newConnection()),this,SLOT(on_newconnect()));
  // connect(server,SIGNAL(),this,SLOT(on_newconnect()));
}

void MainWindow::on_btn_start_toggled(bool checked)
{


}

void MainWindow::on_btn_close_toggled(bool checked)
{

}

//有新链接的方法
void MainWindow::on_newconnect(qintptr handle)
{
  QString value= this->ui->txt_info->toPlainText();
  value+="有新链接\n";
   this->ui->txt_info->setText(value);
}


