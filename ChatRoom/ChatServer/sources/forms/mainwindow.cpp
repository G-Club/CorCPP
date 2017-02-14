
#include <QtNetwork/QtNetwork>
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
    QTcpServer server;
    server.listen(QHostAddress::Any,6123);
}


void MainWindow::on_btn_start_toggled(bool checked)
{


}

void MainWindow::on_btn_close_toggled(bool checked)
{

}

