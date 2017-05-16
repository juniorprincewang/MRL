#pragma execution_character_set("utf-8")
#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QVector>
#include <QMap>
#include <QMessageBox>
#include <QList>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QScrollArea>
#include "publicdata.h"
#include "model.h"
#include "excel.h"

class DataAnalysis: public QWidget
{
public:
    DataAnalysis(QWidget *parent = 0);
    // 农药成分
    QLineEdit *chineseNameText;
    QLineEdit *englishNameText;
    QLineEdit *chemicalNameText;
    QLineEdit *molecularText;
    // 作用对象
    QLineEdit *ediblePartText;
    QLineEdit *nonEdiblePartText;
    QLineEdit *additivePartText;
    // 实验方式和地点
    QLineEdit *methodText;
    QLineEdit *frequencyText;
    QLineEdit *dosageText;
    QLineEdit *locationText;
public:
    QVBoxLayout *mainLayout;
    void fillWidget();
public:
    QString currentDir;
    PesticideData *pesticide;
    int key;
    QVector<double> residues;
    double rSquared;
public slots:
    void receiveSelectedData(PesticideData*, int);
public:
    void preset();

};


#endif // DATAANALYSIS_H
