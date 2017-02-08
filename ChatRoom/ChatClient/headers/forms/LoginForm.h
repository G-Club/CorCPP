#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <headers/ui/ui_loginform.h>

namespace Ui {
class LoginForm;
}


class LoginForm : public QMainWindow
{
    Q_OBJECT
 void closeEvent(QCloseEvent *event);
public:
   LoginForm(QWidget *parent = 0);
   QLabel lab_name;
   QLabel lab_pwd;
   QLineEdit txt_name;
   QLineEdit txt_pwd;
    ~LoginForm();
private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
