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
#include "exceldatastruct.h"

#define DEBUG false

class Excel
{
public:
    QVector<double> residues;       // 残余药量
    QString trendLinesName;     // 趋势线名称，由输入变量组成
    QString pictureSavePath;    // 图片存储路径
    QString fileSavePath;    // 图片存储路径
    QMap<int, double> digestion;
public:
    Excel();
    ~Excel();
    void import(const QString &fileName);
    void read(const QString& sheetName);
    void exportPicture();
    // 返回 R-squared 值
    double savePlot();
    // 返回 R-squared 值
    QVector<QString> makeMetabolicPlot();
    void formula(const QString& sheetName);
    int addChart(const QString& sheetName);
    void saveData(DataStruct *excelData, const QString &fileSavePath, const QString &sheetName);
    QVector<DataStruct*> loadData(const QString &fileSavePath, const QString &sheetName);
    void createFile(const QString& filepath);
private:
    QAxObject* excel;
    QMap<QString, QString> indexMap;    // 指标映射表，共5个参数
    void createDoc(const QString &fileName, QAxObject* qObject);
};


#endif // EXCEL_H
