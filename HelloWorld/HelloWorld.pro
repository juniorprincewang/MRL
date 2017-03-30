
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
    resultsheet.cpp \
    content.cpp \
    datainsertion.cpp \
    menu.cpp \
    analyzelist.cpp \
    itemlist.cpp \
    assesslist.cpp \
    qexcel.cpp \
    datalist.cpp \
    figureinterface.cpp \
    dataanalysis.cpp \
    residueanalysis.cpp \
    digestionanalysis.cpp \
    qqfigureinterface.cpp \
    digestionfigureinterface.cpp

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
    resultsheet.h \
    content.h \
    datainsertion.h \
    menu.h \
    analyselist.h \
    itemlist.h \
    assesslist.h \
    qexcel.h \
    datalist.h \
    publicdata.h \
    figureinterface.h \
    dataanalysis.h \
    digestionanalysis.h \
    residueanalysis.h \
    qqfigureinterface.h \
    digestionfigureinterface.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += C:/Boost/include/boost-1_63
LIBS += C:/Boost/lib/libboost_regex-vc120-mt-gd-1_63.lib \
        C:/Boost/lib/libboost_math_tr1-vc120-mt-gd-1_63.lib
