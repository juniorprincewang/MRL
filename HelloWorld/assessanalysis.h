#pragma execution_character_set("utf-8")
#ifndef ASSESSANALYSIS_H
#define ASSESSANALYSIS_H

#include <QLabel>
#include <QLineEdit>
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
#include <QValidator>
#include <QScrollArea>
#include "publicdata.h"
class AssessAnalysis : public QWidget
{
    Q_OBJECT
public:
    AssessAnalysis(QWidget *parent=0);
    // 农药成分
    QLineEdit *chineseNameText;
    QLineEdit *englishNameText;
    QLineEdit *chemicalNameText;
    QLineEdit *molecularText;
    QVBoxLayout *mainLayout;
    QLineEdit *assessTypeText;
    QLineEdit *mrlText;
    QLineEdit *riskProbabilityText;
    QString currentDir;
public slots:
    virtual void receiveSelectedData(AssessData*, QVector<double>) = 0;

};

// 短期膳食摄入评估
class AcuteAssessAnalysis : public AssessAnalysis
{
    Q_OBJECT
public:
    AcuteAssessAnalysis(QWidget *parent=0);
    QLineEdit *NESTIText;
    QLineEdit *riskProbabilityText;
private:
    AssessData *data;
    void getNESTI();
public slots:
    virtual void receiveSelectedData(AssessData*, QVector<double>);


};

// 长期膳食摄入评估
class ChronicAssessAnalysis : public AssessAnalysis
{
    Q_OBJECT
public:
    ChronicAssessAnalysis(QWidget *parent=0);
    QLineEdit *NEDIText;
    QLineEdit *riskProbabilityText;
public slots:
    virtual void receiveSelectedData(AssessData*, QVector<double>);

};

#endif // ASSESSANALYSIS_H
