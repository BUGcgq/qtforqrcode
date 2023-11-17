#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include "inc/qrencode.h"
#include <QPainter>
#include <QScreen>
#include "sizedialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int codeImagesize = 240;
    int desiredWidth;
    int desiredHeight;

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_Bt_generate_clicked();

    void on_Bt_save_clicked();

    void onComboBoxIndexChanged(int index);

    void openLink(const QString &link);

    void updateEdit(int index);

    void on_Bt_openDialog_clicked();

private:
    Ui::MainWindow *ui;
    QImage qrcodeImage;
    void generateQRCode(QString textToEncode, int width, int height);
    QPixmap generateQR(QString strContent, int width, int height);
    QLabel* versionLabel;  // 软件版本和日期的控件
    QLabel* ideaLabel;     // 技术领先、团队合作、一流服务、客户满意的控件
    QLabel* label_url;     // 链接的控件
    QString textQrcode;
};
#endif // MAINWINDOW_H
