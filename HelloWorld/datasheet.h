#pragma execution_character_set("utf-8")
#ifndef DATASHEET_H
#define DATASHEET_H

#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QAction>
#include <QItemDelegate>
#include <QTableWidgetItem>
#include <QString>
//#include <QtWidgets>
#include <QObject>
#include "publicdata.h"

class DataSheet : public QWidget
{
    Q_OBJECT

public:
    DataSheet(int rows, int cols, QStringList headers, QWidget *parent = 0);
    DataSheet(int rows, int cols, QWidget *parent = 0);
    QVector<double> updateAcuteContents(AssessData *data);
    QVector<double> updateChronicContents(AssessData *data);
    void setHeader(QStringList headers);

public slots:
    void updateColor(QTableWidgetItem *item);
    void returnPressed();
    void selectColor();
    void selectFont();
    void clear();

    void actionSum();
    void actionAdd();
    void actionSubtract();
    void actionMultiply();
    void actionDivide();

protected:
    void setupContents();

    void createActions();

    void actionMath_helper(const QString &title, const QString &op);
    bool runInputDialog(const QString &title,
                        const QString &c1Text,
                        const QString &c2Text,
                        const QString &opText,
                        const QString &outText,
                        QString *cell1, QString *cell2, QString *outCell);
private:
    QAction *colorAction;
    QAction *fontAction;
    QAction *firstSeparator;
    QAction *cell_sumAction;
    QAction *cell_addAction;
    QAction *cell_subAction;
    QAction *cell_mulAction;
    QAction *cell_divAction;
    QAction *secondSeparator;
    QAction *clearAction;

    QAction *printAction;

    QTableWidget *table;

};



void decode_position(const QString &pos, int *row, int *col);
QString encode_position(int row, int col);

enum Columns
{
    COL_NAME,
    COL_FI,
    COL_STMR,
    COL_SOURCE,
    COL_NEDI,
    COL_ALL,
    COL_PERCENT
};

class DataSheetItem : public QTableWidgetItem
{
public:
    DataSheetItem();
    DataSheetItem(const QString &text);

    QTableWidgetItem *clone() const override;

    QVariant data(int role) const override;
    void setData(int role, const QVariant &value) override;
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




class DataSheetDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    DataSheetDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

private slots:
    void commitAndCloseEditor();
    void comboBoxChanged();
};

#endif // DATASHEET_H
