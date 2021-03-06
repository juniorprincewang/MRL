﻿#pragma execution_character_set("utf-8")
#ifndef DATALIST_H
#define DATALIST_H
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
#include <QCheckBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>
#include <QScrollArea>
#include "qexcel.h"
#include "publicdata.h"
#include "datasheet.h"

class DataList: public QWidget
{
    Q_OBJECT
public:
    DataList(QWidget *parent = 0);
    void showFileList(QFileInfoList list);
    void freshFileList();
private:
    QString currentDir;
//    QPushButton *viewButton;
//    QTableWidget *tableWidget;
    QListWidget *fileListWidget;
    // 整体布局
    QVBoxLayout *mainLayout;
public slots:
    void viewButtonClicked();
    void deleteButtonClicked();
    void preview(QListWidgetItem*);
};

class DataDefinition : public QWidget
{
    Q_OBJECT
public:
    DataDefinition(QWidget *parent = 0);
    void showFileList(QFileInfoList list);
    PesticideData* getPesticideData(QString);
public:
    QStringList filter;
    QString currentDir;
    QPushButton *selectButton;    
    QListWidget *fileListWidget;
    QVBoxLayout *mainLayout;
    void freshFileList();
public slots:
    virtual void showFileInfo(QListWidgetItem*) = 0;
};


class QQDataDefinition : public DataDefinition
{
    Q_OBJECT
public:
    QQDataDefinition(QWidget* parent=0);
    QTableWidget *tableWidget;

    void reloadTableWidget(QMap<int, QVector<double>>);
private:
    // 残余数据
    QString xlsFilePath;
    PesticideData *pesticideData;
    QVector<double> residues;
    QList<int> phi;
    QMap<int, QVector<double>> phis;
    QString selectedFile;
    QMap<int, QVector<double>> getPhi(QString);

public slots:
    virtual void showFileInfo(QListWidgetItem*);
    void selectButtonClicked();
signals:
    void sendSelectedData(PesticideData *, int);
};

class DigestionDataDefinition : public DataDefinition
{
    Q_OBJECT
public:
    DigestionDataDefinition(QWidget *parent=0);
private:
    QButtonGroup *radioGroup;
    QButtonGroup *checkBoxGroup;
    QHBoxLayout *checkBoxLayout;
    QHBoxLayout *radioLayout;
    QPushButton *selectButton;
    QMap<int, QVector<double>> getPhi(QString);
    QString selectedFile;
    QString xlsFilePath;
    int radioIndex;
    QMap<int, double> selectData;
    QMap<int, QVector<double>> map;
public slots:
    virtual void showFileInfo(QListWidgetItem *);
    void selectButtonClicked();
signals:
    void sendSelectedData(PesticideData*, QMap<int, double>, int);
};

class AssessDataDefinition : public DataDefinition
{
    Q_OBJECT
public:
    AssessDataDefinition(QWidget *parent=0);

    QVector<double> result;
    QPushButton *selectButton;
    QGridLayout *pesticideLayout;

    QLineEdit *chineseNameText;
    QLineEdit *englishNameText;
    QLineEdit *chemicalNameText;
    QLineEdit *molecularText;
    QLineEdit *adiEdit;
    QLineEdit *arfdEdit;
    QString xlsFilePath;
    QString selectedFile;
    AssessData *assessData;
//    int toxicityIndex;
//    int residueIndex;
//    QList<int> populationIndexList;
    DataSheet *dataSheet;
    AssessData *getAssessDataFromFile(QString);
public slots:
    virtual void showFileInfo(QListWidgetItem *);
    void selectButtonClicked();
signals:
    void sendSelectedData(AssessData*, QVector<double>);
};

class AcuteDataDefinition: public AssessDataDefinition
{
    Q_OBJECT
public:
    AcuteDataDefinition(QWidget *parent);
public slots:
    virtual void showFileInfo(QListWidgetItem *);
};

class ChronicDataDefinition : public AssessDataDefinition
{
    Q_OBJECT
public:
    ChronicDataDefinition(QWidget *parent=0);
public slots:
    virtual void showFileInfo(QListWidgetItem *);
//signals:
//    void sendSelectedData(AssessData*, QVector<double>);

};

#endif // DATALIST_H
