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

}
