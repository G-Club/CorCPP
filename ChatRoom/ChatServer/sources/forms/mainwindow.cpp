#include "headers/forms/mainwindow.h"
#include "headers/ui/ui_mainwindow.h"
#include "headers/tools/cJSON.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <errno.h>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/qabstractsocket.h>
#include <QtNetwork/QtNetwork>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::UMainWindow)
{
    ui->setupUi(this);
    QTcpServer * soc_server = new QTcpServer(this);
    soc_server->
}

MainWindow::~MainWindow()
{
    delete ui;
}
