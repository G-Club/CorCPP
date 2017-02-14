#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class UMainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private:
    Ui::UMainForm *ui;
};

#endif // MAINFORM_H
