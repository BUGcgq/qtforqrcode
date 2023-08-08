# 设置软件版本
VERSION = 1.0.1
# 设置软件日期
DATE = 2023-08-7


DEFINES += HAVE_CONFIG_H   #qrencode used
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sizedialog.cpp \
    src/bitstream.c \
    src/mask.c \
    src/mmask.c \
    src/mqrspec.c \
    src/qrencode.c \
    src/qrinput.c \
    src/qrspec.c \
    src/rscode.c \
    src/split.c


HEADERS += \
    inc/bitstream.h \
    inc/config.h \
    inc/mask.h \
    inc/mmask.h \
    inc/mqrspec.h \
    inc/qrencode.h \
    inc/qrencode_inner.h \
    inc/qrinput.h \
    inc/qrspec.h \
    inc/rscode.h \
    inc/sizedialog.h \
    inc/split.h \
    mainwindow.h \
    sizedialog.h \
    sizedialog.h


FORMS += \
    mainwindow.ui \
    sizedialog.ui
RC_ICONS = image\increase.ico
TARGET = QRcode
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
# 将软件版本和日期作为预定义宏，可以在代码中使用
DEFINES += APP_VERSION=\\\"$$VERSION\\\" APP_DATE=\\\"$$DATE\\\"
RESOURCES += \
    resources.qrc \
    resources.qrc

DISTFILES += \
    qtcore.pro.user
