#include "resultsheet.h"
#include <QtWidgets>

ResultSheet::ResultSheet(QWidget *parent)
        : QWidget(parent)
{

//    formulaInput = new QLineEdit(this);


//    cellLabel = new QLabel(toolBar);
//    cellLabel->setMinimumSize(80, 0);

//    toolBar->addWidget(cellLabel);
//    toolBar->addWidget(formulaInput);

    table = new QTableWidget(8, 1, this);
    table->setObjectName("resultTable");
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);


//    table->setAutoScroll(true);
    table->setItemPrototype(new QTableWidgetItem());
//    table->setItemDelegate(new ResultSheetDelegate());
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setVisible(false);
    table->horizontalHeader()->setSectionsClickable(false);//设置表头不可点击（默认点击后进行排序）
    table->verticalHeader()->setStretchLastSection(true);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    table->setFocusPolicy(Qt::NoFocus); //取消选中单元格时的虚线框
    table->setSelectionBehavior(QAbstractItemView::SelectColumns); //选择整列
    table->setSelectionMode(QAbstractItemView::SingleSelection); //选择单行模式
    table->setMouseTracking(true);  //跟踪鼠标一定要先设的值
    table->setFrameShape(QFrame::NoFrame);//设置无边框
    table->setShowGrid(false); //设置不显示格子线



//    for(int i=0; i<cols; i++)
//    {
//        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
//    }
    setupContents();


//    updateColor(0);
//    setupContents();

//    connect(table, &QTableWidget::currentItemChanged,
//            this, &ResultSheet::updateStatus);
//    connect(table, &QTableWidget::currentItemChanged,
//            this, &ResultSheet::updateColor);
//    connect(table, &QTableWidget::currentItemChanged,
//            this, &ResultSheet::updateLineEdit);
//    connect(table, &QTableWidget::itemChanged,
//            this, &ResultSheet::updateStatus);
//    connect(formulaInput, &QLineEdit::returnPressed, this, &ResultSheet::returnPressed);
//    connect(table, &QTableWidget::itemChanged,
//            this, &ResultSheet::updateLineEdit);

//    setWindowTitle(tr("ResultSheet"));

}
/*
void ResultSheet::reloadColumns(QVector<DataStruct *> dataVector)
{
    int removeCol = dataVector.size();
    qDebug() << "reloadColumns-removeCol "<< removeCol;
    for(int col = 1; col<=removeCol; col++)
    {
        table->removeColumn(col);
    }
    this->addColumns(dataVector);
}

void ResultSheet::addColumns(QVector<DataStruct *> dataVector)
{
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = table->font();
    titleFont.setBold(true);
    int colNum = dataVector.size();
    for(int col=1; col<= colNum; col++)
    {
        DataStruct* dataStruct = dataVector[col-1];
        table->insertColumn(col);
        table->setItem(0, col, new QTableWidgetItem(QString("%1").arg(col)));
        table->item(0, col)->setBackgroundColor(titleBackground);
//        table->item(0, col)->setToolTip("This column shows the purchase date, double click to change");
        table->item(0, col)->setFont(titleFont);
        //
        table->setItem(1, col, new QTableWidgetItem(dataStruct->regulator));
        table->setItem(2, col, new QTableWidgetItem(dataStruct->chemical));
        table->setItem(3, col, new QTableWidgetItem(dataStruct->crop));
        table->setItem(4, col, new QTableWidgetItem(dataStruct->phi));
        table->setItem(5, col, new QTableWidgetItem(dataStruct->rate));
        table->setItem(6, col, new QTableWidgetItem(dataStruct->unit));
        QVector<double> residueVector = dataStruct->residues;

        for(int r_row=0; r_row<residueVector.size(); r_row++)
        {
            QString r_value = QString::number(residueVector[r_row]);
//            qDebug() << r_value;
            table->setItem(7+r_row, col, new QTableWidgetItem(r_value));
        }

    }
}

void ResultSheet::addColumn()
{
    int colCount = table->columnCount();
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = table->font();
    titleFont.setBold(true);
    table->insertColumn(colCount);
//    table->setItem(0, colCount, new ResultSheetItem("Date"));
    table->setItem(0, colCount, new QTableWidgetItem(QString("%1").arg(colCount)));
    table->item(0, colCount)->setBackgroundColor(titleBackground);
    table->item(0, colCount)->setToolTip("This column shows the purchase date, double click to change");
    table->item(0, colCount)->setFont(titleFont);

    table->setItem(1, colCount, new QTableWidgetItem("11111"));
    table->setItem(2, colCount, new QTableWidgetItem("15/6/2006"));
    table->setItem(3, colCount, new QTableWidgetItem("15/6/2006"));
    table->setItem(4, colCount, new QTableWidgetItem("21/5/2006"));
    table->setItem(5, colCount, new QTableWidgetItem("16/6/2006"));
    table->setItem(6, colCount, new QTableWidgetItem("16/6/2006"));

}
*/

void ResultSheet::setupContents()
{
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = table->font();
    titleFont.setBold(true);

    //table->setHorizontalHeaderItem(0, new QTableWidgetItem("qqq"));
    // column 0
//    table->setItem(0, 0, new QTableWidgetItem("Item"));
//    table->item(0, 0)->setBackgroundColor(titleBackground);
//    table->item(0, 0)->setToolTip("This column shows the purchased item/service");
//    table->item(0, 0)->setFont(titleFont);
    table->setItem(0, 0, new QTableWidgetItem(" "));
    table->setItem(1, 0, new QTableWidgetItem("Regulator:"));
    table->setItem(2, 0, new QTableWidgetItem("Chemical:"));
    table->setItem(3, 0, new QTableWidgetItem("Crop:"));
    table->setItem(4, 0, new QTableWidgetItem("PHI:"));
    table->setItem(5, 0, new QTableWidgetItem("App. Rate:"));
    table->setItem(6, 0, new QTableWidgetItem("Unit:"));
    table->setItem(7, 0, new QTableWidgetItem("Residues"));


//    table->item(9, 0)->setFont(titleFont);
//    table->item(9, 0)->setBackgroundColor(Qt::lightGray);

    // column 1

/*
    table->setItem(9, 1, new ResultSheetItem());
    table->item(9, 1)->setBackgroundColor(Qt::lightGray);

    // column 2
    table->setItem(0, 2, new ResultSheetItem("Price"));
    table->item(0, 2)->setBackgroundColor(titleBackground);
    table->item(0, 2)->setToolTip("This column shows the price of the purchase");
    table->item(0, 2)->setFont(titleFont);

    table->setItem(1, 2, new ResultSheetItem("150"));
    table->setItem(2, 2, new ResultSheetItem("2350"));
    table->setItem(3, 2, new ResultSheetItem("-14"));
    table->setItem(4, 2, new ResultSheetItem("980"));
    table->setItem(5, 2, new ResultSheetItem("5"));
    table->setItem(6, 2, new ResultSheetItem("120"));
    table->setItem(7, 2, new ResultSheetItem("300"));
    table->setItem(8, 2, new ResultSheetItem("1240"));

    table->setItem(9, 2, new ResultSheetItem());
    table->item(9, 2)->setBackgroundColor(Qt::lightGray);

    // column 3
    table->setItem(0, 3, new ResultSheetItem("Currency"));
    table->item(0, 3)->setBackgroundColor(titleBackground);
    table->item(0, 3)->setToolTip("This column shows the currency");
    table->item(0, 3)->setFont(titleFont);

    table->setItem(1, 3, new ResultSheetItem("NOK"));
    table->setItem(2, 3, new ResultSheetItem("NOK"));
    table->setItem(3, 3, new ResultSheetItem("EUR"));
    table->setItem(4, 3, new ResultSheetItem("EUR"));
    table->setItem(5, 3, new ResultSheetItem("USD"));
    table->setItem(6, 3, new ResultSheetItem("USD"));
    table->setItem(7, 3, new ResultSheetItem("USD"));
    table->setItem(8, 3, new ResultSheetItem("USD"));

    table->setItem(9, 3, new ResultSheetItem());
    table->item(9,3)->setBackgroundColor(Qt::lightGray);

    // column 4
    table->setItem(0, 4, new ResultSheetItem("Ex. Rate"));
    table->item(0, 4)->setBackgroundColor(titleBackground);
    table->item(0, 4)->setToolTip("This column shows the exchange rate to NOK");
    table->item(0, 4)->setFont(titleFont);

    table->setItem(1, 4, new ResultSheetItem("1"));
    table->setItem(2, 4, new ResultSheetItem("1"));
    table->setItem(3, 4, new ResultSheetItem("8"));
    table->setItem(4, 4, new ResultSheetItem("8"));
    table->setItem(5, 4, new ResultSheetItem("7"));
    table->setItem(6, 4, new ResultSheetItem("7"));
    table->setItem(7, 4, new ResultSheetItem("7"));
    table->setItem(8, 4, new ResultSheetItem("7"));

    table->setItem(9, 4, new ResultSheetItem());
    table->item(9,4)->setBackgroundColor(Qt::lightGray);

    // column 5
    table->setItem(0, 5, new ResultSheetItem("NOK"));
    table->item(0, 5)->setBackgroundColor(titleBackground);
    table->item(0, 5)->setToolTip("This column shows the expenses in NOK");
    table->item(0, 5)->setFont(titleFont);

    table->setItem(1, 5, new ResultSheetItem("* C2 E2"));
    table->setItem(2, 5, new ResultSheetItem("* C3 E3"));
    table->setItem(3, 5, new ResultSheetItem("* C4 E4"));
    table->setItem(4, 5, new ResultSheetItem("* C5 E5"));
    table->setItem(5, 5, new ResultSheetItem("* C6 E6"));
    table->setItem(6, 5, new ResultSheetItem("* C7 E7"));
    table->setItem(7, 5, new ResultSheetItem("* C8 E8"));
    table->setItem(8, 5, new ResultSheetItem("* C9 E9"));

    table->setItem(9, 5, new ResultSheetItem("sum F2 F9"));
    table->item(9,5)->setBackgroundColor(Qt::lightGray);

*/
}

