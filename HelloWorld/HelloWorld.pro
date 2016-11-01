
#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T09:36:10
#
#-------------------------------------------------

QT       += core gui axcontainer printsupport dbus widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloWorld
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spreadsheet/printview.cpp \
    spreadsheet/spreadsheet.cpp \
    spreadsheet/spreadsheetdelegate.cpp \
    spreadsheet/spreadsheetitem.cpp \
    polevl.cpp \
    ndtri.cpp \
    ufunction.cpp \
    excel.cpp \
    imageviewer/imageviewer.cpp

HEADERS  += mainwindow.h \
    newspaper.h \
    reader.h \
    eventlabel.h \
    spreadsheet/printview.h \
    spreadsheet/spreadsheet.h \
    spreadsheet/spreadsheetdelegate.h \
    spreadsheet/spreadsheetitem.h \
    polevl.h \
    ndtri.h \
    ufunction.h \
    excel.h \
    imageviewer/imageviewer.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
