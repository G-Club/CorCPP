#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QtNetwork>
#include <headers/ui/ui_mainwindow.h>
#include <headers/tools/tcpserver.h>

namespace Ui {
class UMainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_start_toggled(bool checked);
    void on_btn_close_toggled(bool checked);
    void on_btn_start_clicked(bool checked);
    void on_newconnect();
  //  void incomingConnection(int  socketDescriptor);
private:
    Ui::UMainWindow *ui;
    TcpServer* server =new TcpServer();
    QTcpSocket* clientConnection;

};

#endif // MAINWINDOW_H
