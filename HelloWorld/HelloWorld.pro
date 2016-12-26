
#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T09:36:10
#
#-------------------------------------------------

QT       += core gui axcontainer printsupport dbus widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MRL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    polevl.cpp \
    ndtri.cpp \
    ufunction.cpp \
    excel.cpp \
    imageviewer/imageviewer.cpp \
    model.cpp \
    datasheet.cpp \
    datasheetdelegate.cpp \
    datasheetitem.cpp \
    printview.cpp \
    resultsheet.cpp

HEADERS  += mainwindow.h \
    newspaper.h \
    reader.h \
    eventlabel.h \
    polevl.h \
    ndtri.h \
    ufunction.h \
    excel.h \
    imageviewer/imageviewer.h \
    model.h \
    datasheet.h \
    datasheetdelegate.h \
    datasheetitem.h \
    printview.h \
    exceldatastruct.h \
    resultsheet.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
