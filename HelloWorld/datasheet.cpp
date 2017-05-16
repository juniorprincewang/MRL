#include <QtWidgets>

#include "datasheet.h"


DataSheet::DataSheet(int rows, int cols, QWidget *parent)
        : QWidget(parent)
{
    table = new QTableWidget(rows, cols, this);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->adjustSize();
    table->horizontalHeader()->setSizeAdjustPolicy(QTableWidget::AdjustToContents);

    table->setSizeAdjustPolicy(QTableWidget::AdjustToContents);

    table->setItemPrototype(table->item(rows - 1, cols - 1));
    table->setItemDelegate(new DataSheetDelegate());

    updateColor(0);
    setupContents();

    connect(table, &QTableWidget::currentItemChanged,
            this, &DataSheet::updateColor);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(table);
//    connect(formulaInput, &QLineEdit::returnPressed, this, &DataSheet::returnPressed);


//    setWindowTitle(tr("DataSheet"));
}

DataSheet::DataSheet(int rows, int cols, QStringList headers, QWidget *parent)
        : QWidget(parent)
{
    table = new QTableWidget(rows, cols, this);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    table->horizontalHeader()->setStretchLastSection(true);
    table->adjustSize();
    table->horizontalHeader()->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    table->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    int col = 0;
    foreach(QString header, headers)
        table->setHorizontalHeaderItem(col, new QTableWidgetItem(header));

    table->setItemPrototype(table->item(rows - 1, cols - 1));
    table->setItemDelegate(new DataSheetDelegate());

    updateColor(0);
    setupContents();

    connect(table, &QTableWidget::currentItemChanged,
            this, &DataSheet::updateColor);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(table);
}

void DataSheet::setHeader(QStringList headers)
{
    int col = 0;
    foreach(QString header, headers)
    {
        table->setHorizontalHeaderItem(col, new QTableWidgetItem(header));
        col++;
    }
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

//    colorAction->setIcon(pix);
}

void DataSheet::returnPressed()
{
//    QString text = formulaInput->text();
    QString text = "returnPressed";
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
    decode_position(*cell1, &c1Row, &c1Col);
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
    decode_position(*cell2, &c2Row, &c2Col);
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
    decode_position(*outCell, &outRow, &outCol);
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

    QString cell1 = encode_position(row_first, col_first);
    QString cell2 = encode_position(row_last, col_last);
    QString out = encode_position(row_cur, col_cur);

    if (runInputDialog(tr("Sum cells"), tr("First cell:"), tr("Last cell:"),
                       QString("%1").arg(QChar(0x03a3)), tr("Output to:"),
                       &cell1, &cell2, &out)) {
        int row;
        int col;
        decode_position(out, &row, &col);
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
        out = encode_position(table->currentRow(), table->currentColumn());

    if (runInputDialog(title, tr("Cell 1"), tr("Cell 2"), op, tr("Output to:"),
                       &cell1, &cell2, &out)) {
        int row, col;
        decode_position(out, &row, &col);
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

QVector<double> DataSheet::updateAcuteContents(AssessData *data)
{
    QVector<FoodLimit*> foodVec = data->foodInfo;
    int row = 0;
    foreach(FoodLimit *food, foodVec)
    {
        table->setItem(row, 0, new DataSheetItem(food->food));
        table->setItem(row, 1, new DataSheetItem(QString::number(food->Fi)));
        table->setItem(row, 2, new DataSheetItem(QString::number(food->stmr)));
        table->setItem(row, 3, new DataSheetItem());
        table->setItem(row, 4, new DataSheetItem(QString("* B%1 C%2").arg(row+1).arg(row+1)));
//        table->setItem(row, 5, new DataSheetItem("ADI*63"));
        table->setItem(row, 6, new DataSheetItem());
        row++;
    }
    table->setItem(0, 5, new DataSheetItem(QString("ADI*63")));
    table->setSpan(0, 5, row, 1);
    table->setSpan(0, 6, row, 1);
    table->setItem(row, 5, new DataSheetItem(QString("%1").arg(data->adi*63)));
    table->item(row, 5)->setBackgroundColor(Qt::lightGray);
    table->setItem(row, 0, new DataSheetItem("Total:"));
    table->item(row,0)->setBackgroundColor(Qt::lightGray);
    table->setItem(row, 4, new DataSheetItem(QString("sum E1 E%1").arg(row)));
    table->item(row,4)->setBackgroundColor(Qt::lightGray);
    table->setItem(row, 6, new DataSheetItem(QString("/ E%1 F%2").arg(row+1).arg(row+1)));
    table->item(row, 6)->setBackgroundColor(Qt::lightGray);
    QString sumValue = table->item(row, 4)->text();
    QString dailyValue = table->item(row, 5)->text();
    QString percentileValue = table->item(row, 6)->text();
    QVector<double> result;
    result.push_back(sumValue.toDouble());
    result.push_back(dailyValue.toDouble());
    result.push_back(percentileValue.toDouble());
    return result;
}

QVector<double> DataSheet::updateChronicContents(AssessData *data)
{
    QVector<FoodLimit*> foodVec = data->foodInfo;
    int row = 0;
    foreach(FoodLimit *food, foodVec)
    {
        table->setItem(row, 0, new DataSheetItem(food->food));
        table->setItem(row, 1, new DataSheetItem(QString::number(food->hr)));
        table->setItem(row, 2, new DataSheetItem(QString::number(food->BWi)));
        table->setItem(row, 3, new DataSheetItem(QString::number(food->LPi)));
        table->setItem(row, 4, new DataSheetItem(QString::number(food->Ui)));
        table->setItem(row, 5, new DataSheetItem(QString::number(food->Ei)));
        table->setItem(row, 6, new DataSheetItem(QString::number(food->stmrp)));
        table->setItem(row, 7, new DataSheetItem(QString::number(food->CVi)));
        // IESTI
        double IESTI = 0.0;
        if(food->Ui < 25)
        {
            IESTI = food->LPi*food->hr/food->BWi;
        }
        else if(food->Ei < food->LPi)
        {
            IESTI = (food->Ei*food->hr*food->CVi+(food->LPi-food->Ei)*food->hr)/food->BWi;
        }
        else if(food->Ei >= food->LPi)
        {
            IESTI = food->LPi*food->hr*food->CVi/food->BWi;
        }
        table->setItem(row, 8, new DataSheetItem(QString("%1").arg(IESTI)));
        // ARfD
        double ARfd = IESTI / data->arfd;
        table->setItem(row, 9, new DataSheetItem(QString("%1").arg(ARfd)));
        row++;
    }

//    QString sumValue = table->item(row, 4)->text();
//    QString dailyValue = table->item(row, 5)->text();
//    QString percentileValue = table->item(row, 6)->text();
    QVector<double> result;
//    result.push_back(sumValue.toDouble());
//    result.push_back(dailyValue.toDouble());
//    result.push_back(percentileValue.toDouble());
    return result;
}

void DataSheet::setupContents()
{
    QColor titleBackground(Qt::lightGray);
    QFont titleFont = table->font();
    titleFont.setBold(true);

    /*
    // column 0
    table->setItem(0, 0, new DataSheetItem("Item"));
    table->item(0, 0)->setBackgroundColor(titleBackground);
    table->item(0, 0)->setToolTip("This column shows the purchased item/service");
    table->item(0, 0)->setFont(titleFont);

    table->setItem(1, 0, new DataSheetItem("AirportBus"));
    table->setItem(2, 0, new DataSheetItem("Flight (Munich)"));
    table->setItem(3, 0, new DataSheetItem("Lunch"));
    table->setItem(4, 0, new DataSheetItem("Flight (LA)"));
    table->setItem(5, 0, new DataSheetItem("Taxi"));
    table->setItem(6, 0, new DataSheetItem("Dinner"));
    table->setItem(7, 0, new DataSheetItem("Hotel"));
    table->setItem(8, 0, new DataSheetItem("Flight (Oslo)"));
    table->setItem(9, 0, new DataSheetItem("Total:"));

    table->item(9, 0)->setFont(titleFont);
    table->item(9, 0)->setBackgroundColor(Qt::lightGray);

    // column 1
    table->setItem(0, 1, new DataSheetItem("Date"));
    table->item(0, 1)->setBackgroundColor(titleBackground);
    table->item(0, 1)->setToolTip("This column shows the purchase date, double click to change");
    table->item(0, 1)->setFont(titleFont);

    table->setItem(1, 1, new DataSheetItem("15/6/2006"));
    table->setItem(2, 1, new DataSheetItem("15/6/2006"));
    table->setItem(3, 1, new DataSheetItem("15/6/2006"));
    table->setItem(4, 1, new DataSheetItem("21/5/2006"));
    table->setItem(5, 1, new DataSheetItem("16/6/2006"));
    table->setItem(6, 1, new DataSheetItem("16/6/2006"));
    table->setItem(7, 1, new DataSheetItem("16/6/2006"));
    table->setItem(8, 1, new DataSheetItem("18/6/2006"));

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

void decode_position(const QString &pos, int *row, int *col)
{
    if (pos.isEmpty()) {
        *col = -1;
        *row = -1;
    } else {
        *col = pos.at(0).toLatin1() - 'A';
        *row = pos.right(pos.size() - 1).toInt() - 1;
    }
}

QString encode_position(int row, int col)
{
    return QString(col + 'A') + QString::number(row + 1);
}
/*****************************************************************************************
 * datasheetdelegate
 *****************************************************************************************
*/

DataSheetDelegate::DataSheetDelegate(QObject *parent)
        : QItemDelegate(parent) {}

QWidget *DataSheetDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &,
                                          const QModelIndex &index) const
{
/*    if (index.column() == 1) {
        QDateTimeEdit *editor = new QDateTimeEdit(parent);
        editor->setDisplayFormat("dd/M/yyyy");
        editor->setCalendarPopup(true);
        return editor;
    }
    else */if(index.column() == COL_SOURCE)
    {
        QComboBox *editor = new QComboBox(parent);
        editor->setEditable(true);

        QStringList values;
        values << "残留中值" << "加工因子矫正的中值" << "残留最大值" << "推荐残留值";
        editor->addItems(values);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        int selectedItem = editor->findText(currentText);
        if(selectedItem == -1)
            editor->setEditText(index.model()->data(index, Qt::DisplayRole).toString());
        else
            editor->setCurrentIndex(selectedItem);
        connect(editor, &QComboBox::currentTextChanged, this, &DataSheetDelegate::comboBoxChanged);

//        editor->installEventFilter(const_cast<DataSheetDelegate*>(this));
        return editor;
    }
    QLineEdit *editor = new QLineEdit(parent);

    // create a completer with the strings in the column as model
    QStringList allStrings;
    for (int i = 1; i<index.model()->rowCount(); i++) {
        QString strItem(index.model()->data(index.sibling(i, index.column()),
            Qt::EditRole).toString());

        if (!allStrings.contains(strItem))
            allStrings.append(strItem);
    }

    QCompleter *autoComplete = new QCompleter(allStrings);
    editor->setCompleter(autoComplete);
    connect(editor, &QLineEdit::editingFinished, this, &DataSheetDelegate::commitAndCloseEditor);
    return editor;
}

void DataSheetDelegate::comboBoxChanged()
{
//    QComboBox* send = qobject_cast<QComboBox*>(sender());
//    qDebug() << send;
//    qDebug() << send->parent();
//    DataSheet *p = qobject_cast<DataSheet*>(send->parent());
//    qDebug() << p;

}

void DataSheetDelegate::commitAndCloseEditor()
{
    QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void DataSheetDelegate::setEditorData(QWidget *editor,
    const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit*>(editor);
    if (edit) {
        edit->setText(index.model()->data(index, Qt::EditRole).toString());
        return;
    }

//    QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
//    if (dateEditor) {
//        dateEditor->setDate(QDate::fromString(
//                                index.model()->data(index, Qt::EditRole).toString(),
//                                "d/M/yyyy"));
//        return;
//    }

    QComboBox *comboEditor = qobject_cast<QComboBox *>(editor);
    if(comboEditor)
    {
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        int selectedItem = comboEditor->findText(currentText);
        if(selectedItem == -1)
            comboEditor->setEditText(index.model()->data(index, Qt::DisplayRole).toString());
        else
            comboEditor->setCurrentIndex(selectedItem);

        return;
    }

}

void DataSheetDelegate::setModelData(QWidget *editor,
    QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *edit = qobject_cast<QLineEdit *>(editor);
    if (edit) {
        model->setData(index, edit->text());
        return;
    }

//    QDateTimeEdit *dateEditor = qobject_cast<QDateTimeEdit *>(editor);
//    if (dateEditor)
//    {
//        model->setData(index, dateEditor->date().toString("dd/M/yyyy"));
//        return;
//    }
    QComboBox *comboEditor = qobject_cast<QComboBox *>(editor);
    if(comboEditor)
    {
        model->setData(index, comboEditor->currentText());

        return;
    }

}


/*
 * datasheetitem
 *
*/
DataSheetItem::DataSheetItem()
        : QTableWidgetItem(), isResolving(false)
{
}

DataSheetItem::DataSheetItem(const QString &text)
        : QTableWidgetItem(text), isResolving(false)
{
}

QTableWidgetItem *DataSheetItem::clone() const
{
    DataSheetItem *item = new DataSheetItem();
    *item = *this;
    return item;
}

QVariant DataSheetItem::data(int role) const
{
    if (role == Qt::EditRole /*|| role == Qt::StatusTipRole*/)
        return formula();

    if (role == Qt::DisplayRole)
        return display();

    QString t = display().toString();
    bool isNumber = false;
    int number = t.toInt(&isNumber);

    if (role == Qt::TextColorRole) {
        if (!isNumber)
            return QVariant::fromValue(QColor(Qt::black));
        else if (number < 0)
            return QVariant::fromValue(QColor(Qt::red));
        return QVariant::fromValue(QColor(Qt::blue));
    }

     if (role == Qt::TextAlignmentRole)
         if (!t.isEmpty() && (t.at(0).isNumber() || t.at(0) == '-'))
             return (int)(Qt::AlignRight | Qt::AlignVCenter);

     return QTableWidgetItem::data(role);
 }

void DataSheetItem::setData(int role, const QVariant &value)
{
    QTableWidgetItem::setData(role, value);
    if (tableWidget())
        tableWidget()->viewport()->update();
}

QVariant DataSheetItem::display() const
{
    // avoid circular dependencies
    if (isResolving)
        return QVariant();

    isResolving = true;
    QVariant result = computeFormula(formula(), tableWidget(), this);
    isResolving = false;
    return result;
}

QVariant DataSheetItem::computeFormula(const QString &formula,
                                         const QTableWidget *widget,
                                         const QTableWidgetItem *self)
{
    // check if the s tring is actually a formula or not
    QStringList list = formula.split(' ');
    if (list.isEmpty() || !widget)
        return formula; // it is a normal string

    QString op = list.value(0).toLower();

    int firstRow = -1;
    int firstCol = -1;
    int secondRow = -1;
    int secondCol = -1;

    if (list.count() > 1)
        decode_position(list.value(1), &firstRow, &firstCol);

    if (list.count() > 2)
        decode_position(list.value(2), &secondRow, &secondCol);

    const QTableWidgetItem *start = widget->item(firstRow, firstCol);
    const QTableWidgetItem *end = widget->item(secondRow, secondCol);
    double firstVal = start ? start->text().toDouble() : 0.0;
    double secondVal = end ? end->text().toDouble() : 0.0;


    QVariant result;
    if (op == "sum") {
        double sum = 0;
        for (int r = firstRow; r <= secondRow; ++r) {
            for (int c = firstCol; c <= secondCol; ++c) {
                const QTableWidgetItem *tableItem = widget->item(r, c);
                if (tableItem && tableItem != self)
                    sum += tableItem->text().toDouble();
            }
        }

        result = sum;
    } else if (op == "+") {
        result = (firstVal + secondVal);
    } else if (op == "-") {
        result = (firstVal - secondVal);
    } else if (op == "*") {
//        qDebug() << "formula = " << formula;
//        qDebug() << firstRow << " " << firstCol;
//        qDebug() << secondRow << " " << secondCol;
//        qDebug() << start->text() << " end"<< end->text();
        result = (firstVal * secondVal);
//        qDebug()<< "**************" <<firstVal << "*"<<secondVal<<"="<< result;

    } else if (op == "/") {
        if (secondVal == 0)
            result = QString("nan");
        else
            result = (firstVal / secondVal);
    } else if (op == "=") {
        if (start)
            result = start->text();
    } else {
        result = formula;
    }

    return result;
}
