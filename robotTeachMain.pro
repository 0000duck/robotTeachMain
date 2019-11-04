#-------------------------------------------------
#
# Project created by QtCreator 2019-04-30T09:59:33
#
#-------------------------------------------------

QT       += core gui network

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robotTeachMain
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


SOURCES += \
       main.cpp \
       frmInput/frminput.cpp \
       mainWindow/MainWindow.cpp \
    CFileIO.cpp

HEADERS += \
       frmInput/frminput.h \
       mainWindow/MainWindow.h \
    CFileIO.hpp

#x86平台
#INCLUDEPATH += /usr/include/libxml2/
#LIBS += -lxml2
#arm平台
INCLUDEPATH += /opt/zynq/libxml2-arm/include/libxml2
LIBS += -L/opt/zynq/libxml2-arm/lib -lxml2

FORMS += \
    frmInput/frminput.ui

RESOURCES += \
    src.qrc

