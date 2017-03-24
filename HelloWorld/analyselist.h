#ifndef ANALYSELIST_H
#define ANALYSELIST_H
#include <QTreeWidget>

class AnalyseList : public QTreeWidget
{
    Q_OBJECT
public:
    AnalyseList(QWidget *parent=0);

public slots:
    void onTreeWidgetClicked(QTreeWidgetItem *item, int column);
signals:
    void changeContent(int);

};

#endif // ANALYSELIST_H
