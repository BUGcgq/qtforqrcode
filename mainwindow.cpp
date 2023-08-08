#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListView>
#include "sizedialog.h" // 包含对话框的头文件

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置gridLayout_2为主窗口的根布局，并将对齐方式设置为居中
    ui->centralwidget->setLayout(ui->gridLayout_2);
    ui->gridLayout_2->setAlignment(Qt::AlignCenter);
    ui->label_2->setText(QString("当前图片保存尺寸:%1*%1px").arg(codeImagesize));
    QIcon icon(":/prefix1/image/increase.ico");
    setWindowIcon(icon);
    setWindowTitle(qApp->applicationName()); // 设置窗口标题为程序名称
    ui->comboBox_qrcodeType->setView(new QListView());                             //使下拉框样式生效
    // 设置下拉框默认选项为 "交流桩二维码"
    connect(ui->comboBox_qrcodeType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onComboBoxIndexChanged);
    ui->comboBox_qrcodeType->setCurrentIndex(1);

    QPixmap backgroundImage(":/prefix1/image/bg.png");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    qDebug() << "Window size:" << this->size();
    qDebug() << "Background image size:" << backgroundImage.size();
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImage);
    this->setPalette(palette);

    versionLabel = new QLabel("软件版本：v" + QString(APP_VERSION) + " 日期：" + QString(APP_DATE), this);
    ideaLabel = new QLabel("技术领先、团队合作、一流服务、客户满意", this);
    label_url = new QLabel("<a href=\"https://www.szincrease.com/\">https://www.szincrease.com/</a>", this);
    label_url->setOpenExternalLinks(true); // 允许打开外部链接

    // 添加 versionLabel 到状态栏最左侧
    statusBar()->addWidget(versionLabel);

    // 添加一个弹簧控件，用于将后面的控件推到最右侧
    QWidget* horizontalSpacer = new QWidget(this);
    horizontalSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    statusBar()->addWidget(horizontalSpacer);

    // 添加 ideaLabel 到状态栏居中
    statusBar()->addWidget(ideaLabel);

    // 添加 label_url 到状态栏最右侧
    statusBar()->addPermanentWidget(label_url);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 在窗口大小改变时重新设置背景图像的大小
    QPixmap backgroundImage(":/prefix1/image/bg.png");
    backgroundImage = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgroundImage);
    this->setPalette(palette);

    QMainWindow::resizeEvent(event);
}
void MainWindow::onComboBoxIndexChanged(int index)
{
    updateEdit(index);
}
void MainWindow::updateEdit(int index)
{
    // 更新输入框内容
    if (index == 0) // 选择普通二维码
    {
        ui->textEdit->setPlaceholderText("请输入文本以生成二维码");
    }
    else if (index == 1) // 选择交流桩二维码
    {
        ui->textEdit->setPlaceholderText("请输入交流桩的SN序列号以生成二维码");
    }
}

void MainWindow::generateQRCode(QString textToEncode, int width, int height)
{
    QPixmap qrcodePixmap = generateQR(textToEncode, width, height);
    qrcodeImage = qrcodePixmap.toImage(); // Convert QPixmap to QImage
    ui->label->setPixmap(QPixmap::fromImage(qrcodeImage));
}

QPixmap MainWindow::generateQR(QString strContent, int width, int height)
{
    QRcode *qrcode = QRcode_encodeString(strContent.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);

    qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;

    double scale_x = (double)width / (double)qrcode_width;
    double scale_y = (double)height / (double)qrcode_width;
    QImage qrImg = QImage(width, height, QImage::Format_ARGB32);

    QPainter painter(&qrImg);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width, height);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);

    for (qint32 y = 0; y < qrcode_width; y++)
    {
        for (qint32 x = 0; x < qrcode_width; x++)
        {
            unsigned char b = qrcode->data[y * qrcode_width + x];
            if (b & 0x01)
            {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }

    QPixmap qrcodePixmap = QPixmap::fromImage(qrImg);
    return qrcodePixmap;
}

void MainWindow::on_Bt_generate_clicked()
{
    QString textToEncode = ui->textEdit->toPlainText();

    int typeIndex = ui->comboBox_qrcodeType->currentIndex();
    int textLength = textToEncode.length();

    if (textLength > 100 && typeIndex == 1){
        QMessageBox::warning(this, "警告", "交流桩二维码不能超过21位！", QMessageBox::Ok);
        return; // 超过21位，不生成二维码，直接退出函数
    }

    if (textLength > 100){
        QMessageBox::warning(this, "警告", "普通二维码输入不能超过100位！", QMessageBox::Ok);
        return; // 超过21位，不生成二维码，直接退出函数
    }

    // 判断文本是否为空
    if (textToEncode.isEmpty())
    {
        QMessageBox::warning(this, "警告", "输入不能为空", QMessageBox::Ok);
        return;
    }

    // 使用正则表达式验证文本是否只包含数字和字母
    QRegularExpression regex("^[\\x00-\\x7F]+$");
    if (!regex.match(textToEncode).hasMatch())
    {
        // 显示错误提示或执行其他操作
        QMessageBox::warning(this, "警告", "非法输入", QMessageBox::Ok);
        return;
    }

    if (typeIndex == 1) {
        // 交流桩二维码，限制输入为21位
        if (textLength > 21){
            QMessageBox::warning(this, "警告", "交流桩二维码输入不能超过21位！", QMessageBox::Ok);
            return; // 超过21位，不生成二维码，直接退出函数
        }
        else if (textLength >= 16) {
            textToEncode = textToEncode.right(16);
        }

        else if (textLength < 16) {
            // 不足16位后面补 '0'
            int zerosToAdd = 16 - textLength;
            QString zeros(zerosToAdd, '0');
            textToEncode = zeros + textToEncode;
        }

        textToEncode = "https://www.onecharging.com/inc/about?terminalCode=" + textToEncode + "01";
    }
    generateQRCode(textToEncode, 240, 240);
}

void MainWindow::on_Bt_save_clicked()
{
    if (!qrcodeImage.isNull()) {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save QR Code"), "", tr("Images (*.png *.jpg)"));
        if (!filePath.isEmpty()) {
            // 使用选中的尺寸大小调整图片并创建一个 QPixmap 对象
            QPixmap resizedImage = QPixmap::fromImage(qrcodeImage.scaled(codeImagesize, codeImagesize, Qt::KeepAspectRatio));

            if (!resizedImage.isNull()) {
                qDebug() << "Resized image width:" << resizedImage.width() << ", height:" << resizedImage.height();

                if (!resizedImage.save(filePath)) {
                    QMessageBox::critical(this, tr("Error"), tr("保存失败，文件路径不能为空"));
                } else {
                    QMessageBox::information(this, tr("Success"), tr("二维码保存成功."));
                }
            } else {
                QMessageBox::warning(this, tr("Warning"), tr("调整图片大小失败."));
            }
        }
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("图像为空，请确认生成了二维码."));
    }
}

void MainWindow::openLink(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link)); // 跳转到链接指定的网页
}


void MainWindow::on_Bt_openDialog_clicked()
{
    sizeDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        codeImagesize = dialog.selectedValue; // 获取用户选择的值
          qDebug() << "codeImagesize: " << codeImagesize;
          ui->label_2->setText(QString("当前图片保存尺寸:%1*%1px").arg(codeImagesize));
    }
}
