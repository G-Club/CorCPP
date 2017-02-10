#ifndef UMAINWINDOW_H
#define UMAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>


namespace Ui {
class UMainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::UMainWindow *ui;
};

#endif // MAINWINDOW_H
