#pragma execution_character_set("utf-8")
#ifndef DIGESTIONANALYSIS_H
#define DIGESTIONANALYSIS_H

#include "dataanalysis.h"

class DigestionAnalysis: public DataAnalysis
{
public:
    DigestionAnalysis(QWidget *parent = 0);
private:
    // 方程式、残留量取值计算、半衰期
    QVector<QString> formulaString;
    QLineEdit *equationText;
    QLineEdit *residueText;
    QLineEdit *halflifeText;
    QMap<int, double> selectedData;
    int radioIndex;
private:
//    bool isShapiroFranciaNormality();
public:
    void fillWidget();
    void plot();

public slots:
    void receiveSelectedData(PesticideData*, QMap<int, double>, int);

};


#endif // DIGESTIONANALYSIS_H
