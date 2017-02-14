#include "headers/forms/mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) : QWidget(parent),ui(new Ui::UMainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}
