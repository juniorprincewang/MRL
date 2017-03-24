#include "analyselist.h"
#include <QDebug>

AnalyseList::AnalyseList(QWidget *parent)
    :QTreeWidget(parent)
{
    QStringList headers;
    headers << QStringLiteral("限量分析") ;
    this->setHeaderLabels(headers);
    this->setHeaderHidden(true);

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this,    SLOT(onTreeWidgetClicked(QTreeWidgetItem*, int)));
    QTreeWidgetItem *dataItem = new QTreeWidgetItem(this, QStringList() << QStringLiteral("数据"));
    QTreeWidgetItem *metaboliseItem = new QTreeWidgetItem(this, QStringList() << QStringLiteral("代谢消解"));
    QTreeWidgetItem *residueItem = new QTreeWidgetItem(this, QStringList() << QStringLiteral("残留限量"));

    new QTreeWidgetItem(dataItem, QStringList() << QStringLiteral("数据录入"));
    new QTreeWidgetItem(dataItem, QStringList() << QStringLiteral("查看数据"));
//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(dataInput, QStringList() << "leaf2");
//    leaf2->setCheckState(leaf2->columnCount()-1 , Qt::Checked);
    new QTreeWidgetItem(metaboliseItem, QStringList() << QStringLiteral("数据定义"));
    new QTreeWidgetItem(metaboliseItem, QStringList() << QStringLiteral("消解图"));
    new QTreeWidgetItem(metaboliseItem, QStringList() << QStringLiteral("结果"));
    // 残留限量项
    new QTreeWidgetItem(residueItem, QStringList() << QStringLiteral("数据定义"));
    new QTreeWidgetItem(residueItem, QStringList() << QStringLiteral("QQ图分析"));
    new QTreeWidgetItem(residueItem, QStringList() << QStringLiteral("残留分析"));

    QList<QTreeWidgetItem *> topLevel;
    topLevel << dataItem << metaboliseItem << residueItem;
    this->insertTopLevelItems(0, topLevel);

    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    QObject::connect(this,
                     static_cast<void (AnalyseList:: *)(QTreeWidgetItem*, int)>(&AnalyseList::itemClicked),
                     this,
                     &AnalyseList::onTreeWidgetClicked
                     );

}

void AnalyseList::onTreeWidgetClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem* parent= item->parent();
    if(parent == NULL)
        return;
    int col = parent->indexOfChild(item);
    QTreeWidget* ptreeWidget= parent->treeWidget();
    if(ptreeWidget == NULL)
        return;
//    int tcount = ptreeWidget->topLevelItemCount();
    int itemIndex = ptreeWidget->indexOfTopLevelItem(parent);
//    QMessageBox::about(NULL, QString("item"), QString().sprintf("%d, index = %d", col, itemIndex));
    qDebug() << QString("col = %1, index = %2").arg(col).arg(itemIndex);
    switch(itemIndex)
    {
    // 数据
    case 0:
        if(col ==0 )
        {
            qDebug() << QStringLiteral("新建数据");
            emit changeContent(1);
        }
        else if(col == 1)
        {
            qDebug() << QStringLiteral("打开数据");
            emit changeContent(2);
        }
        break;
//     代谢消解
    case 1:
        if(col == 0)
        {
            qDebug() << QStringLiteral("数据定义");
            emit changeContent(3);
        }
        else if(col == 1)
        {
            qDebug() << QStringLiteral("消解图");
            emit changeContent(4);
        }
        else if(col == 2)
        {
            qDebug() << QStringLiteral("结果");
            emit changeContent(5);
        }
        break;
//    残留限量
    case 2:

        if(col == 0)
        {
            qDebug() << QStringLiteral("数据定义");
            emit changeContent(6);
        }
        else if(col == 1)
        {
            qDebug() << QStringLiteral("QQ图分析");
            emit changeContent(7);
        }
        else if(col == 2)
        {
            qDebug() << QStringLiteral("残留分析");
            emit changeContent(8);
        }
        break;
    default:
        qDebug() << "add error page";
        break;
    }
}

