#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QtNetwork>
#include <headers/ui/ui_mainwindow.h>

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
    QTcpServer* server =new QTcpServer();
    QTcpSocket* clientConnection;

};

#endif // MAINWINDOW_H
