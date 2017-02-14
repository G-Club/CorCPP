#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void on_txt_start_toggled(bool checked);

    void on_btn_close_toggled(bool checked);

private:
    Ui::UMainWindow *ui;
};

#endif // MAINWINDOW_H
