#pragma execution_character_set("utf-8")
#ifndef RESIDUEANALYSIS_H
#define RESIDUEANALYSIS_H

#include "dataanalysis.h"

class ResidueAnalysis: public DataAnalysis
{
public:
    ResidueAnalysis(QWidget *parent = 0);
private:
    // 分布，残留计算方法，推荐残留值

    QLineEdit *distributionText;
    QLineEdit *calcMethodText;
    QLineEdit *recommendationText;
private:


    bool isShapiroFranciaNormality();
public:
    void fillWidget();
    void logNormalityPlot();
    void normalityPlot();

public slots:
    void receiveSelectedData(PesticideData*, int);

};



#endif // RESIDUEANALYSIS_H
