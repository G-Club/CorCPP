#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include <headers/ui/ui_loginform.h>

namespace Ui {
class ULoginForm;
} // namespace Ui

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private:
 Ui::ULoginForm *ui;
private slots:
    void Login();
    void connError();
    void connSucc();
};

#endif // LOGINFORM_H
