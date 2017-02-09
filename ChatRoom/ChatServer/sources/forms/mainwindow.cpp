#include "headers/forms/mainwindow.h"
#include "headers/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDesktopWidget* p_dw =QApplication::desktop();
    this->resize(500,420);
    int dw =p_dw->width();
    int dh = p_dw->height();
    this->move((dw-this->width())/2,(dh-this->height())/2);

}

MainWindow::~MainWindow()
{
    delete ui;
}
