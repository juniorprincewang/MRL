#pragma execution_character_set("utf-8")
#ifndef FIGUREINTERFACE_H
#define FIGUREINTERFACE_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QListWidget>
#include <QFileInfoList>
#include <QMessageBox>
#include <QDir>
#include <QMap>
#include <QFile>
#include <QDebug>
#include <QLabel>
#include "qexcel.h"
#include "excel.h"
#include "publicdata.h"
#include "imageviewer/imageviewer.h"

class FigureInterface : public QWidget
{
    Q_OBJECT
public:
    FigureInterface(QWidget *parent = 0);
public:
    double rSquared;
    int key;
    PesticideData *pesticide;
    QString currentDir;
    QLabel *tableLabel;
    QPushButton *selectButton;
    QListWidget *fileListWidget;
    QTableWidget *tableWidget;
    QVBoxLayout *mainLayout;
public:
    virtual void fillTableWidget();
    virtual void plot(QString&) = 0;
    void preset();
public slots:
//    void receiveSelectedData(PesticideData*, int);
    virtual void selectButtonClicked() = 0;

};

#endif // FIGUREINTERFACE_H
