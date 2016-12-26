#ifndef DATASHEETITEM_H
#define DATASHEETITEM_H
#include "datasheet.h"

#include <QTableWidgetItem>

class DataSheetItem : public QTableWidgetItem
{
public:
    DataSheetItem();
    DataSheetItem(const QString &text);

    QTableWidgetItem *clone() const Q_DECL_OVERRIDE;

    QVariant data(int role) const Q_DECL_OVERRIDE;
    void setData(int role, const QVariant &value) Q_DECL_OVERRIDE;
    QVariant display() const;

    inline QString formula() const
    {
        return QTableWidgetItem::data(Qt::DisplayRole).toString();
    }

    static QVariant computeFormula(const QString &formula,
                                   const QTableWidget *widget,
                                   const QTableWidgetItem *self = 0);

private:
    mutable bool isResolving;
};

#endif // DATASHEETITEM_H
