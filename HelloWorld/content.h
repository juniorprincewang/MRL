#pragma execution_character_set("utf-8")
#ifndef CONTENT_H
#define CONTENT_H

#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "datainsertion.h"
#include "datalist.h"
#include "figureinterface.h"
#include "dataanalysis.h"
#include "residueanalysis.h"
#include "digestionanalysis.h"
#include "digestionfigureinterface.h"
#include "qqfigureinterface.h"

class WelcomeInterface: public QWidget
{
    Q_OBJECT
public:
    WelcomeInterface(QWidget *parent = 0);
private:
    QVBoxLayout *mainLayout;

};

class HelpInterface : public QWidget
{
public:
    HelpInterface(QWidget *parent = 0);
private:
    QVBoxLayout *mainLayout;
};

class BlankInterface : public QWidget
{
public:
    BlankInterface(QWidget *parent = 0);
};

class Content : public QStackedWidget
{
    Q_OBJECT

public:
    Content(QWidget *parent = 0);
    DataInsertion *insertionPage;
    WelcomeInterface *welcomePage;
    HelpInterface *helpPage;
    BlankInterface *blankPage;
    DataList *listPage;
    QQDataDefinition *definitionPage;
//    FigureInterface *figurePage;
//    DataAnalysis *analysisPage;
    ResidueAnalysis *analysisPage;
    DigestionAnalysis *digAnalysisPage;
    QQFigureInterface *qqFigurePage;
    DigestionFigureInterface *digFigurePage;
    DigestionDataDefinition *digDefinitionPage;

signals:
    void sendSelectedData(PesticideData*, int);
    void sendDigestionSelectedData(PesticideData*, QMap<int, double>, int);
public slots:
    void receiveSelectedData(PesticideData *, int);
    void receiveDigestionSelectedData(PesticideData*, QMap<int,double>, int);
    void setCurrentIndex(int index);
private:

};


#endif // CONTENT_H
