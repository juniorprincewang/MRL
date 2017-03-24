#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QStackedWidget>
#include "analyselist.h"
#include "assesslist.h"

class ItemList : public QStackedWidget
{
    Q_OBJECT
public:
    ItemList(QWidget *parent=0);
public slots:
    void changeListSlot(int index);
signals:
    void changeListSignal(int index);
private:
    AnalyseList *analyseList;
    AssessList *assessList;

};

#endif // ITEMLIST_H
