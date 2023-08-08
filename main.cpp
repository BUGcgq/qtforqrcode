#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 获取主屏幕（带有任务栏的屏幕）的可用几何尺寸
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect availableGeometry = primaryScreen->availableGeometry();

    // 计算主窗口的期望大小
    int desiredWidth = availableGeometry.width() * 0.6; // 屏幕宽度的60%
    int desiredHeight = availableGeometry.height() * 0.7; // 屏幕高度的70%

    // 创建主窗口对象
    MainWindow mainWindow;

    // 设置主窗口的期望大小
    mainWindow.resize(desiredWidth, desiredHeight);
    mainWindow.setMinimumSize(desiredWidth, desiredHeight);

    // 将主窗口居中显示在屏幕上
    mainWindow.move((availableGeometry.width() - desiredWidth) / 2,
                    (availableGeometry.height() - desiredHeight) / 2);

    mainWindow.show();

    return a.exec();
}
