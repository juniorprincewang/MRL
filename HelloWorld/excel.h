#ifndef EXCEL_H
#define EXCEL_H
#include <QVector>
#include <QMap>
#include <QString>
#include <QAxObject>
#include <QDebug>
#include <QTextStream>
#include <QtMath>

#include "ufunction.h"
#include "spreadsheet/spreadsheet.h"
#include "model.h"

#define DEBUG true

class Excel
{
public:
    QVector<double> residues;       // 残余药量
    QString trendLinesName;     // 趋势线名称，由输入变量组成
    QString pictureSavePath;    // 图片存储路径
public:
    Excel();
    ~Excel();
    void import(const QString &fileName);
    void read(const QString& sheetName);
    void exportPicture();
    void savePlot();
    void formula(const QString& sheetName);
    int addChart(const QString& sheetName);
private:
    QAxObject* excel;
    QMap<QString, QString> indexMap;    // 指标映射表，共5个参数
    void createDoc(const QString &fileName, QAxObject* qObject);
};


#endif // EXCEL_H
