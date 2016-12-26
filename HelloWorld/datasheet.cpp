#include "datasheet.h"
#include <QtWidgets>

DataSheet::DataSheet(QWidget *parent)
        : QWidget(parent)
{

//    formulaInput = new QLineEdit(this);


//    cellLabel = new QLabel(toolBar);
//    cellLabel->setMinimumSize(80, 0);

//    toolBar->addWidget(cellLabel);
//    toolBar->addWidget(formulaInput);

    table = new QTableWidget(8, 1, this);
    table->setObjectName("viewTable");
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);


//    table->setAutoScroll(true);
    table->setItemPrototype(new QTableWidgetItem());
//    table->setItemDelegate(new DataSheetDelegate());
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
//            this, &DataSheet::updateStatus);
//    connect(table, &QTableWidget::currentItemChanged,
//            this, &DataSheet::updateColor);
//    connect(table, &QTableWidget::currentItemChanged,
//            this, &DataSheet::updateLineEdit);
//    connect(table, &QTableWidget::itemChanged,
//            this, &DataSheet::updateStatus);
//    connect(formulaInput, &QLineEdit::returnPressed, this, &DataSheet::returnPressed);
//    connect(table, &QTableWidget::itemChanged,
//            this, &DataSheet::updateLineEdit);

//    setWindowTitle(tr("DataSheet"));

}

void DataSheet::updateColor(QTableWidgetItem *item)
{
    QPixmap pix(16, 16);
    QColor col;
    if (item)
        col = item->backgroundColor();
    if (!col.isValid())
        col = palette().base().color();

    QPainter pt(&pix);
    pt.fillRect(0, 0, 16, 16, col);

    QColor lighter = col.light();
    pt.setPen(lighter);
    QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
    pt.drawPolyline(lightFrame, 3);

    pt.setPen(col.dark());
    QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };
    pt.drawPolyline(darkFrame, 3);

    pt.end();

    colorAction->setIcon(pix);
}

void DataSheet::updateLineEdit(QTableWidgetItem *item)
{
    if (item != table->currentItem())
        return;
    if (item)
        formulaInput->setText(item->data(Qt::EditRole).toString());
    else
        formulaInput->clear();
}

void DataSheet::returnPressed()
{
    QString text = formulaInput->text();
    int row = table->currentRow();
    int col = table->currentColumn();
    QTableWidgetItem *item = table->item(row, col);
    if (!item)
        table->setItem(row, col, new DataSheetItem(text));
    else
        item->setData(Qt::EditRole, text);
    table->viewport()->update();
}

void DataSheet::selectColor()
{
    QTableWidgetItem *item = table->currentItem();
    QColor col = item ? item->backgroundColor() : table->palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    QList<QTableWidgetItem*> selected = table->selectedItems();
    if (selected.count() == 0)
        return;

    foreach (QTableWidgetItem *i, selected) {
        if (i)
            i->setBackgroundColor(col);
    }

    updateColor(table->currentItem());
}

void DataSheet::selectFont()
{
    QList<QTableWidgetItem*> selected = table->selectedItems();
    if (selected.count() == 0)
        return;

    bool ok = false;
    QFont fnt = QFontDialog::getFont(&ok, font(), this);

    if (!ok)
        return;
    foreach (QTableWidgetItem *i, selected) {
        if (i)
            i->setFont(fnt);
    }
}

bool DataSheet::runInputDialog(const QString &title,
                                 const QString &c1Text,
                                 const QString &c2Text,
                                 const QString &opText,
                                 const QString &outText,
                                 QString *cell1, QString *cell2, QString *outCell)
{
    QStringList rows, cols;
    for (int c = 0; c < table->columnCount(); ++c)
        cols << QChar('A' + c);
    for (int r = 0; r < table->rowCount(); ++r)
        rows << QString::number(1 + r);

    QDialog addDialog(this);
    addDialog.setWindowTitle(title);

    QGroupBox group(title, &addDialog);
    group.setMinimumSize(250, 100);

    QLabel cell1Label(c1Text, &group);
    QComboBox cell1RowInput(&group);
    int c1Row, c1Col;
    decode_pos(*cell1, &c1Row, &c1Col);
    cell1RowInput.addItems(rows);
    cell1RowInput.setCurrentIndex(c1Row);

    QComboBox cell1ColInput(&group);
    cell1ColInput.addItems(cols);
    cell1ColInput.setCurrentIndex(c1Col);

    QLabel operatorLabel(opText, &group);
    operatorLabel.setAlignment(Qt::AlignHCenter);

    QLabel cell2Label(c2Text, &group);
    QComboBox cell2RowInput(&group);
    int c2Row, c2Col;
    decode_pos(*cell2, &c2Row, &c2Col);
    cell2RowInput.addItems(rows);
    cell2RowInput.setCurrentIndex(c2Row);
    QComboBox cell2ColInput(&group);
    cell2ColInput.addItems(cols);
    cell2ColInput.setCurrentIndex(c2Col);

    QLabel equalsLabel("=", &group);
    equalsLabel.setAlignment(Qt::AlignHCenter);

    QLabel outLabel(outText, &group);
    QComboBox outRowInput(&group);
    int outRow, outCol;
    decode_pos(*outCell, &outRow, &outCol);
    outRowInput.addItems(rows);
    outRowInput.setCurrentIndex(outRow);
    QComboBox outColInput(&group);
    outColInput.addItems(cols);
    outColInput.setCurrentIndex(outCol);

    QPushButton cancelButton(tr("Cancel"), &addDialog);
    connect(&cancelButton, &QAbstractButton::clicked, &addDialog, &QDialog::reject);

    QPushButton okButton(tr("OK"), &addDialog);
    okButton.setDefault(true);
    connect(&okButton, &QAbstractButton::clicked, &addDialog, &QDialog::accept);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(&okButton);
    buttonsLayout->addSpacing(10);
    buttonsLayout->addWidget(&cancelButton);

    QVBoxLayout *dialogLayout = new QVBoxLayout(&addDialog);
    dialogLayout->addWidget(&group);
    dialogLayout->addStretch(1);
    dialogLayout->addItem(buttonsLayout);

    QHBoxLayout *cell1Layout = new QHBoxLayout;
    cell1Layout->addWidget(&cell1Label);
    cell1Layout->addSpacing(10);
    cell1Layout->addWidget(&cell1ColInput);
    cell1Layout->addSpacing(10);
    cell1Layout->addWidget(&cell1RowInput);

    QHBoxLayout *cell2Layout = new QHBoxLayout;
    cell2Layout->addWidget(&cell2Label);
    cell2Layout->addSpacing(10);
    cell2Layout->addWidget(&cell2ColInput);
    cell2Layout->addSpacing(10);
    cell2Layout->addWidget(&cell2RowInput);

    QHBoxLayout *outLayout = new QHBoxLayout;
    outLayout->addWidget(&outLabel);
    outLayout->addSpacing(10);
    outLayout->addWidget(&outColInput);
    outLayout->addSpacing(10);
    outLayout->addWidget(&outRowInput);

    QVBoxLayout *vLayout = new QVBoxLayout(&group);
    vLayout->addItem(cell1Layout);
    vLayout->addWidget(&operatorLabel);
    vLayout->addItem(cell2Layout);
    vLayout->addWidget(&equalsLabel);
    vLayout->addStretch(1);
    vLayout->addItem(outLayout);

    if (addDialog.exec()) {
        *cell1 = cell1ColInput.currentText() + cell1RowInput.currentText();
        *cell2 = cell2ColInput.currentText() + cell2RowInput.currentText();
        *outCell = outColInput.currentText() + outRowInput.currentText();
        return true;
    }

    return false;
}

void DataSheet::actionSum()
{
    int row_first = 0;
    int row_last = 0;
    int row_cur = 0;

    int col_first = 0;
    int col_last = 0;
    int col_cur = 0;

    QList<QTableWidgetItem*> selected = table->selectedItems();

    if (!selected.isEmpty()) {
        QTableWidgetItem *first = selected.first();
        QTableWidgetItem *last = selected.last();
        row_first = table->row(first);
        row_last = table->row(last);
        col_first = table->column(first);
        col_last = table->column(last);
    }

    QTableWidgetItem *current = table->currentItem();

    if (current) {
        row_cur = table->row(current);
        col_cur = table->column(current);
    }

    QString cell1 = encode_pos(row_first, col_first);
    QString cell2 = encode_pos(row_last, col_last);
    QString out = encode_pos(row_cur, col_cur);

    if (runInputDialog(tr("Sum cells"), tr("First cell:"), tr("Last cell:"),
                       QString("%1").arg(QChar(0x03a3)), tr("Output to:"),
                       &cell1, &cell2, &out)) {
        int row;
        int col;
        decode_pos(out, &row, &col);
        table->item(row, col)->setText(tr("sum %1 %2").arg(cell1, cell2));
    }
}

void DataSheet::actionMath_helper(const QString &title, const QString &op)
{
    QString cell1 = "C1";
    QString cell2 = "C2";
    QString out = "C3";

    QTableWidgetItem *current = table->currentItem();
    if (current)
        out = encode_pos(table->currentRow(), table->currentColumn());

    if (runInputDialog(title, tr("Cell 1"), tr("Cell 2"), op, tr("Output to:"),
                       &cell1, &cell2, &out)) {
        int row, col;
        decode_pos(out, &row, &col);
        table->item(row, col)->setText(tr("%1 %2 %3").arg(op, cell1, cell2));
    }
}

void DataSheet::actionAdd()
{
    actionMath_helper(tr("Addition"), "+");
}

void DataSheet::actionSubtract()
{
    actionMath_helper(tr("Subtraction"), "-");
}

void DataSheet::actionMultiply()
{
    actionMath_helper(tr("Multiplication"), "*");
}
void DataSheet::actionDivide()
{
    actionMath_helper(tr("Division"), "/");
}

void DataSheet::clear()
{
    foreach (QTableWidgetItem *i, table->selectedItems())
        i->setText("");
}

void DataSheet::reloadColumns(QVector<DataStruct *> dataVector)
{
    int removeCol = dataVector.size();
    qDebug() << "reloadColumns-removeCol "<< removeCol;
    for(int col = 1; col<=removeCol; col++)
    {
        table->removeColumn(col);
    }
    this->addColumns(dataVector);
}

void DataSheet::addColumns(QVector<DataStruct *> dataVector)
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

void DataSheet::addColumn()
{
    int colCount = table->columnCount();
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = table->font();
    titleFont.setBold(true);
    table->insertColumn(colCount);
//    table->setItem(0, colCount, new DataSheetItem("Date"));
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

void DataSheet::setupContents()
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
    table->setItem(9, 1, new DataSheetItem());
    table->item(9, 1)->setBackgroundColor(Qt::lightGray);

    // column 2
    table->setItem(0, 2, new DataSheetItem("Price"));
    table->item(0, 2)->setBackgroundColor(titleBackground);
    table->item(0, 2)->setToolTip("This column shows the price of the purchase");
    table->item(0, 2)->setFont(titleFont);

    table->setItem(1, 2, new DataSheetItem("150"));
    table->setItem(2, 2, new DataSheetItem("2350"));
    table->setItem(3, 2, new DataSheetItem("-14"));
    table->setItem(4, 2, new DataSheetItem("980"));
    table->setItem(5, 2, new DataSheetItem("5"));
    table->setItem(6, 2, new DataSheetItem("120"));
    table->setItem(7, 2, new DataSheetItem("300"));
    table->setItem(8, 2, new DataSheetItem("1240"));

    table->setItem(9, 2, new DataSheetItem());
    table->item(9, 2)->setBackgroundColor(Qt::lightGray);

    // column 3
    table->setItem(0, 3, new DataSheetItem("Currency"));
    table->item(0, 3)->setBackgroundColor(titleBackground);
    table->item(0, 3)->setToolTip("This column shows the currency");
    table->item(0, 3)->setFont(titleFont);

    table->setItem(1, 3, new DataSheetItem("NOK"));
    table->setItem(2, 3, new DataSheetItem("NOK"));
    table->setItem(3, 3, new DataSheetItem("EUR"));
    table->setItem(4, 3, new DataSheetItem("EUR"));
    table->setItem(5, 3, new DataSheetItem("USD"));
    table->setItem(6, 3, new DataSheetItem("USD"));
    table->setItem(7, 3, new DataSheetItem("USD"));
    table->setItem(8, 3, new DataSheetItem("USD"));

    table->setItem(9, 3, new DataSheetItem());
    table->item(9,3)->setBackgroundColor(Qt::lightGray);

    // column 4
    table->setItem(0, 4, new DataSheetItem("Ex. Rate"));
    table->item(0, 4)->setBackgroundColor(titleBackground);
    table->item(0, 4)->setToolTip("This column shows the exchange rate to NOK");
    table->item(0, 4)->setFont(titleFont);

    table->setItem(1, 4, new DataSheetItem("1"));
    table->setItem(2, 4, new DataSheetItem("1"));
    table->setItem(3, 4, new DataSheetItem("8"));
    table->setItem(4, 4, new DataSheetItem("8"));
    table->setItem(5, 4, new DataSheetItem("7"));
    table->setItem(6, 4, new DataSheetItem("7"));
    table->setItem(7, 4, new DataSheetItem("7"));
    table->setItem(8, 4, new DataSheetItem("7"));

    table->setItem(9, 4, new DataSheetItem());
    table->item(9,4)->setBackgroundColor(Qt::lightGray);

    // column 5
    table->setItem(0, 5, new DataSheetItem("NOK"));
    table->item(0, 5)->setBackgroundColor(titleBackground);
    table->item(0, 5)->setToolTip("This column shows the expenses in NOK");
    table->item(0, 5)->setFont(titleFont);

    table->setItem(1, 5, new DataSheetItem("* C2 E2"));
    table->setItem(2, 5, new DataSheetItem("* C3 E3"));
    table->setItem(3, 5, new DataSheetItem("* C4 E4"));
    table->setItem(4, 5, new DataSheetItem("* C5 E5"));
    table->setItem(5, 5, new DataSheetItem("* C6 E6"));
    table->setItem(6, 5, new DataSheetItem("* C7 E7"));
    table->setItem(7, 5, new DataSheetItem("* C8 E8"));
    table->setItem(8, 5, new DataSheetItem("* C9 E9"));

    table->setItem(9, 5, new DataSheetItem("sum F2 F9"));
    table->item(9,5)->setBackgroundColor(Qt::lightGray);
    */
}

const char *htmlText =
"<HTML>"
"<p><b>This demo shows use of <c>QTableWidget</c> with custom handling for"
" individual cells.</b></p>"
"<p>Using a customized table item we make it possible to have dynamic"
" output in different cells. The content that is implemented for this"
" particular demo is:"
"<ul>"
"<li>Adding two cells.</li>"
"<li>Subtracting one cell from another.</li>"
"<li>Multiplying two cells.</li>"
"<li>Dividing one cell with another.</li>"
"<li>Summing the contents of an arbitrary number of cells.</li>"
"</HTML>";

void DataSheet::showAbout()
{
    QMessageBox::about(this, "About DataSheet", htmlText);
}

void decode_pos(const QString &pos, int *row, int *col)
{
    if (pos.isEmpty()) {
        *col = -1;
        *row = -1;
    } else {
        *col = pos.at(0).toLatin1() - 'A';
        *row = pos.right(pos.size() - 1).toInt() - 1;
    }
}

QString encode_pos(int row, int col)
{
    return QString(col + 'A') + QString::number(row + 1);
}


