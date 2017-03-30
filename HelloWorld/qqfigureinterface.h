#pragma execution_character_set("utf-8")
#ifndef QQFIGUREINTERFACE_H
#define QQFIGUREINTERFACE_H
#include "figureinterface.h"

class QQFigureInterface : public FigureInterface
{
    Q_OBJECT
public:
    QQFigureInterface(QWidget *parent = 0);
    void plot(QString &);
public slots:
    void receiveSelectedData(PesticideData*, int);
    void selectButtonClicked();
};


#endif // QQFIGUREINTERFACE_H
