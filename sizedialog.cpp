#include "sizedialog.h"
#include "ui_sizedialog.h"
#include <QButtonGroup>
#include <QPushButton>
#include <QScreen>

sizeDialog::sizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sizeDialog)
{
    ui->setupUi(this);
    // 设置窗口标题
    setWindowTitle("选择二维码大小");
    // 设置“确认”和“取消”按钮的文本
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确认");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    // 获取主屏幕（带有任务栏的屏幕）的可用几何尺寸
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect availableGeometry = primaryScreen->availableGeometry();

    // 计算主窗口的期望大小
    int desiredWidth = availableGeometry.width() * 0.3; // 屏幕宽度的60%
    int desiredHeight = availableGeometry.height() * 0.4; // 屏幕高度的70%

    setFixedSize(desiredWidth, desiredHeight);

    // 去除窗口图标
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    // 将勾选框添加到按钮组
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->checkBox_1);
    buttonGroup->addButton(ui->checkBox_2);
    buttonGroup->addButton(ui->checkBox_3);
    buttonGroup->addButton(ui->checkBox_4);

    // 设置按钮组为互斥模式
    buttonGroup->setExclusive(true);

    // 连接复选框和按钮盒的信号和槽
    connect(ui->checkBox_4, &QCheckBox::stateChanged, this, &sizeDialog::on_checkBox_4_stateChanged);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &sizeDialog::on_buttonBox_accepted);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &sizeDialog::on_buttonBox_rejected);
    ui->lineEdit->setVisible(false);
    ui->label->setVisible(false);
}

sizeDialog::~sizeDialog()
{
    delete ui;
}

void sizeDialog::on_checkBox_4_stateChanged(int state)
{
    ui->lineEdit->setVisible(state == Qt::Checked);
    ui->label->setVisible(state == Qt::Checked);
    ui->lineEdit->clear();
}

void sizeDialog::on_buttonBox_accepted()
{
    if (ui->checkBox_1->isChecked())
    {
        selectedValue = 240;
    }
    else if (ui->checkBox_2->isChecked())
    {
        selectedValue = 300;
    }
    else if (ui->checkBox_3->isChecked())
    {
        selectedValue = 400;
    }
    else if (ui->checkBox_4->isChecked())
    {
        bool ok;
        int value = ui->lineEdit->text().toInt(&ok);

        if (ok && value >= 1 && value <= 1000)
        {
            selectedValue = value;
        }
        else
        {
            QMessageBox::warning(this, tr("Invalid Input"), tr("不合法的值."));
            return; // 输入不合法，不关闭窗口
        }
    }

    accept(); // 关闭窗口
}


void sizeDialog::on_buttonBox_rejected()
{
    reject();
}
