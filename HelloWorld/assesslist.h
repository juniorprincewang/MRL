#ifndef ASSESSLIST_H
#define ASSESSLIST_H
#include <QTreeWidget>

class AssessList : public QTreeWidget
{
    Q_OBJECT
public:
    AssessList(QWidget *parent=0);
public slots:
    void onTreeWidgetClicked(QTreeWidgetItem *item, int column);

};

#endif // ASSESSLIST_H
