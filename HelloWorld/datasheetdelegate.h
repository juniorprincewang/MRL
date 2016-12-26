#ifndef DATASHEETDELEGATE_H
#define DATASHEETDELEGATE_H
#include "datasheet.h"

#include <QItemDelegate>

class DataSheetDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    DataSheetDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const Q_DECL_OVERRIDE;

private slots:
    void commitAndCloseEditor();
};
#endif // DATASHEETDELEGATE_H
