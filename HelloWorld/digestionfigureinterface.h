#pragma execution_character_set("utf-8")
#ifndef DIGESTIONFIGUREINTERFACE_H
#define DIGESTIONFIGUREINTERFACE_H
#include "figureinterface.h"

class DigestionFigureInterface : public FigureInterface
{
    Q_OBJECT
public:
    DigestionFigureInterface(QWidget *parent = 0);

    void fillTableWidget();
    void plot(QString&);
private:
    QMap<int, double> selectData;

public slots:
    void receiveSelectedData(PesticideData*, QMap<int, double>, int);
    void selectButtonClicked();
};

#endif // DIGESTIONFIGUREINTERFACE_H
