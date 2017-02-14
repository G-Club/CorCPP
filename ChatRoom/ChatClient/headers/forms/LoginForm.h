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
    void connError();
    void connSucc();
    void on_btn_login_toggled(bool checked);
    void on_btn_login_clicked(bool checked);
};

#endif // LOGINFORM_H
