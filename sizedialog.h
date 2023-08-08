#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class sizeDialog;
}

class sizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sizeDialog(QWidget *parent = nullptr);
    int selectedValue;
    ~sizeDialog();

private slots:
    void on_checkBox_4_stateChanged(int state);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::sizeDialog *ui;

};

#endif // SIZEDIALOG_H
