#pragma execution_character_set("utf-8")
#ifndef ASSESSLIST_H
#define ASSESSLIST_H
#include <QTreeWidget>
#include <QDebug>

class AssessList : public QTreeWidget
{
    Q_OBJECT
public:
    AssessList(QWidget *parent=0);
public slots:
    void onTreeWidgetClicked(QTreeWidgetItem *item, int column);
signals:
    void changeContent(int);
};

#endif // ASSESSLIST_H
