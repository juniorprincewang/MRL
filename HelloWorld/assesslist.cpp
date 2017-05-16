#include "assesslist.h"

AssessList::AssessList(QWidget *parent)
    :QTreeWidget(parent)
{
    QStringList headers;
    headers << QStringLiteral("安全评估") ;
    this->setHeaderLabels(headers);
    this->setHeaderHidden(true);

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this,    SLOT(onTreeWidgetClicked(QTreeWidgetItem*, int)));
    QTreeWidgetItem *dataItem = new QTreeWidgetItem(this, QStringList() << QStringLiteral("数据"));
    QTreeWidgetItem *acuteItem = new QTreeWidgetItem(this, QStringList() << QStringLiteral("急性评估"));
    QTreeWidgetItem *chronicItem = new QTreeWidgetItem(this, QStringList() << QStringLiteral("慢性评估"));

    new QTreeWidgetItem(dataItem, QStringList() << QStringLiteral("数据录入"));
    new QTreeWidgetItem(dataItem, QStringList() << QStringLiteral("查看数据"));
    // 急性评估
    new QTreeWidgetItem(acuteItem, QStringList() << QStringLiteral("数据定义"));
    new QTreeWidgetItem(acuteItem, QStringList() << QStringLiteral("评估结果"));
    // 慢性评估
    new QTreeWidgetItem(chronicItem, QStringList() << QStringLiteral("数据定义"));
    new QTreeWidgetItem(chronicItem, QStringList() << QStringLiteral("评估结果"));

    QList<QTreeWidgetItem *> topLevel;
    topLevel << dataItem << acuteItem << chronicItem;
    this->insertTopLevelItems(0, topLevel);

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void AssessList::onTreeWidgetClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem* parent= item->parent();
    if(parent == NULL)
        return;
    int col = parent->indexOfChild(item);
    QTreeWidget* ptreeWidget= parent->treeWidget();
    if(ptreeWidget == NULL)
        return;
    int itemIndex = ptreeWidget->indexOfTopLevelItem(parent);
//    QMessageBox::about(NULL, QString("item"), QString().sprintf("%d, index = %d", col, itemIndex));
//    qDebug() << QString("col = %1, index = %2").arg(col).arg(itemIndex);
    switch(itemIndex)
    {
    // 数据
    case 0:
        if(col ==0 )
        {
//            qDebug() << QStringLiteral("新建数据");
            emit changeContent(11);
        }
        else if(col == 1)
        {
//            qDebug() << QStringLiteral("查看数据");
            emit changeContent(4);
        }
        break;
//  急性评估
    case 1:
        if(col == 0)
        {
//            qDebug() << QStringLiteral("数据定义");
            emit changeContent(12);
        }
        else if(col == 1)
        {
//            qDebug() << QStringLiteral("评估结果");
            emit changeContent(13);
        }
        break;
//    慢性评估
    case 2:

        if(col == 0)
        {
//            qDebug() << QStringLiteral("数据定义");
            emit changeContent(14);
        }
        else if(col == 1)
        {
//            qDebug() << QStringLiteral("评估结果");
            emit changeContent(15);
        }
        break;
    default:
        qDebug() << "add error page";
        break;
    }
}
