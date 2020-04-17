#-------------------------------------------------
#
# Project created by QtCreator 2020-04-08T20:18:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EgretPoetry
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    Menu.cpp \
    LiLibrary/LiEasyLayout.cpp \
    LiLibrary/LiFileName.cpp \
    LiLibrary/LiFixedToLayout.cpp \
    LiLibrary/LiReadImageInfo.cpp \
    DataInput.cpp \
    DataInputMenu.cpp \
    DataInputConfigInfo.cpp \
    DataInputConfigSource.cpp \
    DataInputConfigAlign.cpp \
    DataInputConfigWord.cpp

HEADERS += \
        MainWindow.h \
    Menu.h \
    LiLibrary/LiEasyLayout.h \
    LiLibrary/LiFileName.h \
    LiLibrary/LiFixedToLayout.h \
    LiLibrary/LiReadImageInfo.h \
    DataInput.h \
    DataInputMenu.h \
    DataInputConfigInfo.h \
    DataInputConfigSource.h \
    GlobalEnum.h \
    DataInputConfigAlign.h \
    DataInputConfigWord.h

FORMS += \
        MainWindow.ui \
    Menu.ui \
    DataInput.ui \
    DataInputMenu.ui \
    DataInputConfigInfo.ui \
    DataInputConfigSource.ui \
    DataInputConfigAlign.ui \
    DataInputConfigWord.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
