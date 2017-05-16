#include "content.h"
#include <QPixmap>

Content::Content(QWidget *parent)
    : QStackedWidget(parent)
{
//    stack = new QStackedWidget(this);
    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
    /*插入其他页面*/

    insertionPage = new DataInsertion(this);
    welcomePage = new WelcomeInterface(this);
    helpPage = new HelpInterface(this);
    blankPage = new BlankInterface(this);
    listPage = new DataList(this);
    definitionPage = new QQDataDefinition(this);
//    figurePage = new FigureInterface(this);
    analysisPage = new ResidueAnalysis(this);
    digAnalysisPage = new DigestionAnalysis(this);
    qqFigurePage = new QQFigureInterface(this);
    digFigurePage = new DigestionFigureInterface(this);
    digDefinitionPage = new DigestionDataDefinition(this);
    assessInsertionPage = new AssessDataInsertion(this);
    acuteDefinitionPage = new AcuteDataDefinition(this);
    acuteAnalysisPage = new AcuteAssessAnalysis(this);
    chronicAnalysisPage = new ChronicAssessAnalysis(this);
    chronicDefinitionPage = new ChronicDataDefinition(this);
//    QScrollArea *scrollArea = new QScrollArea;
//    scrollArea->setWidget(assessInsertionPage);

    this->addWidget(welcomePage);   //0
    this->addWidget(helpPage);      //1
    this->addWidget(blankPage);     //2
    this->addWidget(insertionPage); //3
    this->addWidget(listPage);      //4
    this->addWidget(definitionPage);//5
    this->addWidget(qqFigurePage);    //6
    this->addWidget(analysisPage);  //7
    this->addWidget(digAnalysisPage);  //8
    this->addWidget(digFigurePage); // 9
    this->addWidget(digDefinitionPage); // 10
    this->addWidget(assessInsertionPage);   // 11
    this->addWidget(acuteDefinitionPage);   // 12
    this->addWidget(acuteAnalysisPage);     // 13
    this->addWidget(chronicDefinitionPage); //14
    this->addWidget(chronicAnalysisPage);   //15

    QLayout *stackLayout =  this->layout();
    stackLayout->setAlignment(Qt::AlignCenter);
//    delete stackLayout;
//    this->setLayout(layout);


    QObject::connect(this->acuteDefinitionPage,
                     static_cast<void (AcuteDataDefinition::*)(AssessData *, QVector<double>)>(&AcuteDataDefinition::sendSelectedData),
                     this,
                     &Content::receiveAssessSelectedData
                     );
    QObject::connect(this,
                     static_cast<void (Content::*)(AssessData *, QVector<double>)>(&Content::sendSelectedData),
                     this->acuteAnalysisPage,
                     &AcuteAssessAnalysis::receiveSelectedData
                     );
    QObject::connect(this->definitionPage,
                     static_cast<void (QQDataDefinition::*)(PesticideData *, int)>(&QQDataDefinition::sendSelectedData),
                     this,
                     &Content::receiveSelectedData
                     );
    QObject::connect(this->digDefinitionPage,
                     static_cast<void (DigestionDataDefinition::*)(PesticideData *, QMap<int,double>, int)>(&DigestionDataDefinition::sendSelectedData),
                     this,
                     &Content::receiveDigestionSelectedData
                     );
    QObject::connect(this,
                     static_cast<void (Content::*)(PesticideData *, QMap<int,double>, int)>(&Content::sendDigestionSelectedData),
                     this->digFigurePage,
                     &DigestionFigureInterface::receiveSelectedData
                     );
    QObject::connect(this,
                     static_cast<void (Content::*)(PesticideData *, int)>(&Content::sendSelectedData),
                     this->qqFigurePage,
                     &QQFigureInterface::receiveSelectedData
                     );

    QObject::connect(this,
                     static_cast<void (Content::*)(PesticideData *, int)>(&Content::sendSelectedData),
                     this->analysisPage,
                     &ResidueAnalysis::receiveSelectedData
                     );
    QObject::connect(this,
                     static_cast<void (Content::*)(PesticideData *, QMap<int, double>, int)>(&Content::sendDigestionSelectedData),
                     this->digAnalysisPage,
                     &DigestionAnalysis::receiveSelectedData
                     );

}

void Content::setCurrentIndex(int index)
{
//    QStringList filter;
    QStackedWidget::setCurrentIndex(index);
    if(index == 4)
    {
        listPage->freshFileList();
    }
    else if(index == 5)
    {
        definitionPage->freshFileList();
    }
    else if(index == 10)
    {
        digDefinitionPage->freshFileList();
    }
    else if (index == 12)
    {
        acuteDefinitionPage->freshFileList();
    }
    else if(index == 14)
        chronicDefinitionPage->freshFileList();


}

void Content::receiveSelectedData(PesticideData *p, int key)
{
    emit sendSelectedData(p, key);
}
void Content::receiveAssessSelectedData(AssessData *p, QVector<double> key)
{
    emit sendSelectedData(p, key);
}

void Content::receiveDigestionSelectedData(PesticideData *p, QMap<int, double> m, int index)
{
    emit sendDigestionSelectedData(p, m, index);
}


BlankInterface::BlankInterface(QWidget *parent)
    :QWidget(parent)
{

}

WelcomeInterface::WelcomeInterface(QWidget *parent)
    :QWidget(parent)
{
    QLabel *label = new QLabel(this);
    QPixmap pixmap(":/images/welcome");
    label->setPixmap(pixmap);
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(label);
    mainLayout->setAlignment(label, Qt::AlignCenter);
    // 设置滚动轴
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QWidget *client = new QWidget(scrollArea);
    client->setLayout(mainLayout);
    scrollArea->setWidget(client);
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(scrollArea);
}

HelpInterface::HelpInterface(QWidget *parent)
    :QWidget(parent)
{
    QLabel *label = new QLabel(this);
    label->setText("这是帮助页面。");
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(label);
    mainLayout->setAlignment(label, Qt::AlignCenter);
//    this->setLayout(mainLayout);
    // 设置滚动轴
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QWidget *client = new QWidget(scrollArea);
    client->setLayout(mainLayout);
    scrollArea->setWidget(client);
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(scrollArea);
}

