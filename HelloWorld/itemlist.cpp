#include "itemlist.h"


ItemList::ItemList(QWidget *parent)
    :QStackedWidget(parent)
{
    analyseList = new AnalyseList(this);
    assessList = new AssessList(this);
    QTreeWidget *startList = new QTreeWidget(this);
    startList->setHeaderHidden(true);
    QTreeWidget *helpList = new QTreeWidget(this);
    helpList->setHeaderHidden(true);
    this->addWidget(startList);
    this->addWidget(analyseList);
    this->addWidget(assessList);
    this->addWidget(helpList);
//    qDebug()<< this->indexOf(analyseList);
//    qDebug()<< this->indexOf(assessList);
    QObject::connect(analyseList,
                     static_cast<void (AnalyseList:: *)(int)> (&AnalyseList::changeContent),
                     this,
                     &ItemList::changeListSlot);
    QObject::connect(assessList,
                     static_cast<void (AssessList:: *)(int)> (&AssessList::changeContent),
                     this,
                     &ItemList::changeListSlot);
}

void ItemList::changeListSlot(int index)
{
    emit changeListSignal(index);
}

