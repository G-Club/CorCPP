
#include <QMessageBox>
#include "headers/forms/loginform.h"
#include "headers/ui/ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :QMainWindow(parent),ui(new Ui::LoginForm)
{
    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->resize(375,280);
    QDesktopWidget* p_dw =QApplication::desktop();
    int dw =p_dw->width();
    int dh = p_dw->height();
    this->move((dw-this->width())/2,(dh-this->height())/2);

    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    QMessageBox::about(this,tr("xigou"),tr("xigou end"));
    exit(1);
    delete ui;
}
