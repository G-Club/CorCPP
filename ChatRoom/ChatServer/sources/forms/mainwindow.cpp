
#include <QtNetwork/QtNetwork>
#include "headers/forms/mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::UMainWindow)
{
    ui->setupUi(this);





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_txt_start_toggled(bool checked)
{
   QTcpServer server;
   server.listen(QHostAddress::Any,6123);
}

void MainWindow::on_btn_close_toggled(bool checked)
{

}
