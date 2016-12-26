#ifndef DATASHEET_H
#define DATASHEET_H
#include <QWidget>
#include "datasheetdelegate.h"
#include "datasheetitem.h"
#include "exceldatastruct.h"

class QAction;
class QLabel;
class QLineEdit;
class QToolBar;
class QTableWidgetItem;
class QTableWidget;


class DataSheet : public QWidget
{
    Q_OBJECT

public:

    DataSheet(QWidget *parent = 0);
    void addColumn();
    void addColumns(QVector<DataStruct*> dataVector);
    void reloadColumns(QVector<DataStruct*> dataVector);

public slots:
//    void updateStatus(QTableWidgetItem *item);
    void updateColor(QTableWidgetItem *item);
    void updateLineEdit(QTableWidgetItem *item);
    void returnPressed();
    void selectColor();
    void selectFont();
    void clear();
    void showAbout();


    void actionSum();
    void actionSubtract();
    void actionAdd();
    void actionMultiply();
    void actionDivide();

protected:
    void setupContextMenu();
    void setupContents();


    void actionMath_helper(const QString &title, const QString &op);
    bool runInputDialog(const QString &title,
                        const QString &c1Text,
                        const QString &c2Text,
                        const QString &opText,
                        const QString &outText,
                        QString *cell1, QString *cell2, QString *outCell);
private:
    QToolBar *toolBar;
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
    QAction *aboutDataSheet;


    QLabel *cellLabel;
    QTableWidget *table;
    QLineEdit *formulaInput;

};

void decode_pos(const QString &pos, int *row, int *col);
QString encode_pos(int row, int col);


#endif // DATASHEET_H
