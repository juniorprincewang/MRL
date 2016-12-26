#ifndef RESULTSHEET_H
#define RESULTSHEET_H

#include <QWidget>

class QAction;
class QLabel;
class QLineEdit;
class QToolBar;
class QTableWidgetItem;
class QTableWidget;


class ResultSheet : public QWidget
{
    Q_OBJECT

public:

    ResultSheet(QWidget *parent = 0);
    void addColumn();
    void addColumns();
    void reloadColumns();

public slots:


private:
    QTableWidget *table;
    void setupContents();
};


#endif // RESULTSHEET_H
