#include "datalist.h"

DataList::DataList(QWidget *parent)
    :QWidget(parent)
{
//    tableWidget = new QTableWidget(this);
    viewButton = new QPushButton("详细查看", this);
    fileListWidget = new QListWidget(this);
    mainLayout = new QVBoxLayout(this);
//    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(fileListWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(viewButton);
    mainLayout->addLayout(buttonLayout);

    QObject::connect(fileListWidget,
                     static_cast<void (QListWidget:: *)(QListWidgetItem*)>(&QListWidget::itemDoubleClicked),
                     this,
                     &DataList::preview);
    QObject::connect(viewButton, &QPushButton::clicked, this, &DataList::viewButtonClicked);
    // 当前路径下的MRL文件夹
    this->currentDir = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
    freshFileList();
}

void DataList::freshFileList()
{
    QDir rootDir(this->currentDir);
    QStringList filter;
    filter << "*.xls";
    rootDir.setNameFilters(filter) ;
    QFileInfoList list = rootDir.entryInfoList(filter, QDir::Files|QDir::NoDotAndDotDot);
    showFileList(list);
}

void DataList::showFileList(QFileInfoList list)
{
    fileListWidget->clear();
    for(unsigned int i=0; i<list.count(); i++)
    {
        QFileInfo tmpFileInfo = list.at(i);
        QString fileName = tmpFileInfo.fileName();
        QListWidgetItem *tmp = new QListWidgetItem(fileName);
        fileListWidget->addItem(tmp);
    }
}

void DataList::preview(QListWidgetItem *item)
{
    QString xlsFilePath = QString("%1/%2").arg(this->currentDir).arg(item->text());
    QFile xlsFile(xlsFilePath);

    if(!xlsFile.exists())
    {
        QMessageBox::critical(NULL, QString("警告"), QString("该文件%1不存在！").arg(xlsFilePath));
        return;
    }
    //打开文件，取得工作簿
    QExcel excel(xlsFilePath);
}

void DataList::viewButtonClicked()
{
    QListWidgetItem *item = this->fileListWidget->currentItem();
    if(NULL == item)
    {
        QMessageBox::critical(NULL, QString("警告"), QString("请先选中列表中的文件！"));
        return;
    }
    QString xlsFilePath = QString("%1/%2").arg(this->currentDir).arg(item->text());
    QFile xlsFile(xlsFilePath);

    if(!xlsFile.exists())
    {
        QMessageBox::critical(NULL, QString("警告"), QString("该文件%1不存在！").arg(xlsFilePath));
        return;
    }
    //打开文件，取得工作簿
    QExcel excel(xlsFilePath);
}

/*
 *******************************************************************************************************
 * 以下是DataDefinition类实现
 *******************************************************************************************************
*/

DataDefinition::DataDefinition(QWidget *parent)
    :QWidget(parent)
{
    QLabel *listLabel = new QLabel("文档选择（请单击以选择文档）", this);
    fileListWidget = new QListWidget(this);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(listLabel);
    mainLayout->addWidget(fileListWidget);

    QObject::connect(fileListWidget,
                     static_cast<void (QListWidget:: *)(QListWidgetItem*)>(&QListWidget::itemClicked),
                     this,
                     &DataDefinition::showFileInfo);

    // 当前路径下的MRL文件夹
    this->currentDir = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
    freshFileList();
}

void DataDefinition::freshFileList()
{
    QDir rootDir(this->currentDir);
    QStringList filter;
    filter << "*.xls";
    rootDir.setNameFilters(filter) ;
    QFileInfoList list = rootDir.entryInfoList(filter, QDir::Files|QDir::NoDotAndDotDot);
    showFileList(list);
}


void DataDefinition::showFileList(QFileInfoList list)
{
    fileListWidget->clear();
    for(unsigned int i=0; i<list.count(); i++)
    {
        QFileInfo tmpFileInfo = list.at(i);
        QString fileName = tmpFileInfo.fileName();
        QListWidgetItem *tmp = new QListWidgetItem(fileName);
        fileListWidget->addItem(tmp);
    }
}

PesticideData *DataDefinition::getPesticideData(QString xlsFilePath)
{
    //打开文件，取得工作簿
    QExcel excel(xlsFilePath);
    excel.selectSheet(1);
    PesticideData *p = new PesticideData;
    p->chineseName = excel.getCellValue(1, 3).toString();
    p->englishName = excel.getCellValue(2, 3).toString();
    p->chemicalName = excel.getCellValue(3, 3).toString();
    p->molecular = excel.getCellValue(4, 3).toString();
    p->edible = excel.getCellValue(5,3).toString();
    p->nonedible = excel.getCellValue(6, 3).toString();
    QVector<QString> additive;
    for(int i=3; i< (1<<5); i++)
    {
        QVariant s = excel.getCellValue(7, i);
        if(s.isNull())
            break;
        additive.push_back(s.toString());
    }
    p->additive = additive;
    p->method = excel.getCellValue(8, 3).toString();
    p->frequency = excel.getCellValue(9, 3).toString();
    p->dosage = excel.getCellValue(10, 3).toString();
    QVector<QString> location;
    for(int i=2; i< (1<<5); i++)
    {
        QVariant s = excel.getCellValue(11, i);
        if(s.isNull())
            break;
        location.push_back(s.toString());
    }
    p->location = location;

    //取得工作表已使用范围
    int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;
    excel.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
//    qDebug() << bottomRightRow << bottomRightColumn ;
    double residue;
    bool ok;
    QMap<int, QVector<double>> map;
    for(int i=0; i<(bottomRightColumn-1)/4; i++)
    {
        int shift = 4*i;
        int phi = excel.getCellValue(12, 3+shift).toInt();
        QVector<double> residueVector;
        for(int j=15; j<=bottomRightRow; j++)
        {
            residue = excel.getCellValue(j, 2).toDouble(&ok);
            if(!ok)
                break;
            residueVector.push_back(residue);
        }
        map[phi] = residueVector;

    }
    p->residues = map;
    excel.close();
    return p;
}


/*
 *******************************************************************************************************
 * 以下是QQDataDefinition类实现
 *******************************************************************************************************
*/

QQDataDefinition::QQDataDefinition(QWidget *parent)
    :DataDefinition(parent)
{
    QLabel *tableLabel = new QLabel("实验时间（天）和残留量（标题栏为间隔期，每一列为对应的残留量，请单击以选择相应列数据。）", this);
    tableWidget = new QTableWidget(this);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);  //整列选中的方式
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //选择单行模式
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    selectButton = new QPushButton("选择列", this);
    mainLayout->addWidget(tableLabel);
    mainLayout->addWidget(tableWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(selectButton);
    mainLayout->addLayout(buttonLayout);
    QObject::connect(selectButton, &QPushButton::clicked, this, &QQDataDefinition::selectButtonClicked);
}


QMap<int, QVector<double>> QQDataDefinition::getPhi(QString xlsFilePath)
{
    //打开文件，取得工作簿
    QExcel excel(xlsFilePath);
    excel.selectSheet(1);

    //取得工作表已使用范围
    int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;
    excel.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
//    qDebug() << bottomRightRow << bottomRightColumn ;
    double residue;
    bool ok;
    QMap<int, QVector<double>> map;
    for(int i=0; i<(bottomRightColumn-1)/4; i++)
    {
        int shift = 4*i;
        int phi = excel.getCellValue(12, 3+shift).toInt();
//        qDebug() << phi;
        QVector<double> residueVector;
        for(int j=15; j<=bottomRightRow; j++)
        {
            residue = excel.getCellValue(j, 2).toDouble(&ok);
            if(!ok)
                break;
//            qDebug() << residue;
            residueVector.push_back(residue);
        }
        map[phi] = residueVector;

    }
    excel.close();
    return map;
}

void QQDataDefinition::selectButtonClicked()
{
    int currentColumn = this->tableWidget->currentColumn();
//    QMessageBox::information(NULL, "", QString("%1").arg(currentColumn));
    if(-1 == currentColumn)
    {
        QMessageBox::critical(NULL, "错误提示", "请先选择一列数据");
        return;
    }
    int key = this->phi.at(currentColumn);
    QMessageBox::StandardButton rb = QMessageBox::information(NULL,
                             QString("选择提示"),
                             QString("确定选择%1的间隔期为%2的数据？").arg(this->selectedFile).arg(key),
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        this->residues = this->phis[key];
        QMessageBox::information(NULL,
                                 QString("提示"),
                                 QString("已选择%1的间隔期为%2的数据!").arg(this->selectedFile).arg(key));
    }
    else
    {
        this->residues.clear();
        return ;
    }
    PesticideData *data = this->getPesticideData(this->xlsFilePath);
    emit sendSelectedData(data, key);
}

void QQDataDefinition::showFileInfo(QListWidgetItem *item)
{
    QString xlsFilePath = QString("%1/%2").arg(this->currentDir).arg(item->text());
    QFile xlsFile(xlsFilePath);

    if(!xlsFile.exists())
    {
        QMessageBox::critical(NULL, QString("警告"), QString("该文件%1不存在！").arg(xlsFilePath));
        return;
    }
    this->selectedFile = item->text();
    this->xlsFilePath = xlsFilePath;
    this->phis =  this->getPhi(xlsFilePath);
    this->reloadTableWidget(this->phis);
}

void QQDataDefinition::reloadTableWidget(QMap<int, QVector<double> > map)
{
    phi.clear();
    residues.clear();
    tableWidget->setRowCount(0);//连行也清除掉

    QColor titleBackground(Qt::lightGray);
    QFont titleFont = this->tableWidget->font();
    titleFont.setBold(true);
    // 必须设置行和列，否则setItem无法显示。
    this->tableWidget->setRowCount(1<<16);
    this->tableWidget->setColumnCount(map.size());
    int col = 0;
    QStringList header;
    QMap<int, QVector<double>>::const_iterator i = map.constBegin();
    for(; i!= map.constEnd(); i++, col++)
    {
        header << QString::number(i.key());
        phi << i.key();
//        this->tableWidget->item(0, col)->setBackgroundColor(titleBackground);
//        this->tableWidget->item(0, col)->setFont(titleFont);
//        table->item(0, col)->setToolTip("This column shows the purchase date, double click to change");
        //
        QVector<double> residueVector = i.value();

        for(int r_row=0; r_row<residueVector.size(); r_row++)
        {
            QString r_value = QString::number(residueVector[r_row]);
            this->tableWidget->setItem(r_row, col, new QTableWidgetItem(r_value));
        }
    }
    this->tableWidget->setHorizontalHeaderLabels(header);
}

/*
 *******************************************************************************************************
 * 以下是DigestionDataDefinition类实现
 *******************************************************************************************************
*/


DigestionDataDefinition::DigestionDataDefinition(QWidget *parent)
    :DataDefinition(parent)
{
    checkBoxLayout = new QHBoxLayout();
    radioLayout = new QHBoxLayout();
    checkBoxGroup = new QButtonGroup(this);
    radioGroup = new QButtonGroup(this);
    QLabel *checkBoxLabel = new QLabel(this);
    checkBoxLabel->setText(QString("选择实验时间对应的数据（多选）"));
    // 设置不互斥
    checkBoxGroup->setExclusive(false);
    QLabel *radioLabel = new QLabel(this);
    radioLabel->setText(QString("选择实验数据的计算方法（单选）"));
    QRadioButton *meanRadio = new QRadioButton(this);
    meanRadio->setText(QString::fromLocal8Bit("均值"));
    QRadioButton *medianRadio= new QRadioButton(this);
    medianRadio->setText(QString::fromLocal8Bit("中值"));
    QRadioButton *modeRadio= new QRadioButton(this);
    modeRadio->setText(QString::fromLocal8Bit("众数"));
    radioGroup->addButton(medianRadio);
    radioGroup->addButton(meanRadio);
    radioGroup->addButton(modeRadio);
    radioLayout->addWidget(radioLabel);
    radioLayout->addWidget(medianRadio);
    radioLayout->addWidget(meanRadio);
    radioLayout->addWidget(modeRadio);
    radioLayout->addStretch();
    checkBoxLayout->setSpacing(10);
    checkBoxLayout->setContentsMargins(10, 10, 10, 10);

    selectButton = new QPushButton(QString("确认选择"), this);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(selectButton);
    mainLayout->addWidget(checkBoxLabel);
    mainLayout->addLayout(checkBoxLayout);
    mainLayout->addLayout(radioLayout);
    mainLayout->addLayout(buttonLayout);
    QObject::connect(selectButton, &QPushButton::clicked, this, &DigestionDataDefinition::selectButtonClicked);
}

void DigestionDataDefinition::showFileInfo(QListWidgetItem *item)
{
    QString xlsFilePath = QString("%1/%2").arg(this->currentDir).arg(item->text());
    QFile xlsFile(xlsFilePath);

    if(!xlsFile.exists())
    {
        QMessageBox::critical(NULL, QString("警告"), QString("该文件%1不存在！").arg(xlsFilePath));
        return;
    }
    this->selectedFile = item->text();
    this->xlsFilePath = xlsFilePath;


    QLayoutItem *w;
    while( (w = checkBoxLayout->takeAt(0)) != NULL)
    {
        delete w->widget();
        delete w;
    }
    // 遍历按钮，获取选中状态
    QList<QAbstractButton*> list = checkBoxGroup->buttons();
    foreach (QAbstractButton *pCheckBox, list)
    {
        delete pCheckBox;
    }

    map =  getPhi(xlsFilePath);
    QMap<int, QVector<double>>::const_iterator i = map.constBegin();
    for(; i!= map.constEnd(); i++)
    {
//        header << QString::number(i.key());
//        phi << i.key();
        QCheckBox *pCheckBox = new QCheckBox(this);
        // 添加CheckBox
        pCheckBox->setText(QString::fromLocal8Bit("%1").arg(i.key()));
        checkBoxLayout->addWidget(pCheckBox);
        checkBoxGroup->addButton(pCheckBox);
        /*
        QVector<double> residueVector = i.value();
        for(int r_row=0; r_row<residueVector.size(); r_row++)
        {
            QString r_value = QString::number(residueVector[r_row]);
            this->tableWidget->setItem(r_row, col, new QTableWidgetItem(r_value));
        }
        */
    }
}

void DigestionDataDefinition::selectButtonClicked()
{
    bool isSelected = false;
    // 遍历 radio buttongroup
    QList<QAbstractButton*> radioList = radioGroup->buttons();
    foreach(QAbstractButton* b, radioList)
    {
        if(b->isChecked())
        {
            radioIndex = radioList.indexOf(b);
            isSelected = true;
        }
    }
    if(!isSelected)
    {
        QMessageBox::critical(NULL, "错误提示", "请先选择实验数据的计算方式。");
        return;
    }
    isSelected = false;
    selectData.clear();
    // 遍历checkbox ButtonGroup
    QList<QAbstractButton*> checkList = checkBoxGroup->buttons();
    foreach(QAbstractButton* b, checkList)
    {
        if(b->isChecked())
        {
             int day = b->text().toInt();
             double value = map[day].at(radioIndex);
             selectData[day] = value;
             isSelected = true;
        }
    }
    if(!isSelected)
    {
        QMessageBox::critical(NULL, "错误提示", "请先选择实验数据。");
        return;
    }

    PesticideData *data = getPesticideData(this->xlsFilePath);
    emit sendSelectedData(data, selectData, radioIndex);
    QMessageBox::information(NULL, QString("提示"), QString("选择完毕"));
}

QMap<int, QVector<double>> DigestionDataDefinition::getPhi(QString xlsFilePath)
{
    //打开文件，取得工作簿
    QExcel excel(xlsFilePath);
    excel.selectSheet(1);

    //取得工作表已使用范围
    int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;
    excel.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
//    qDebug() << bottomRightRow << bottomRightColumn ;
    double residue;
    bool ok;
    QMap<int, QVector<double>> map;
    for(int i=0; i<(bottomRightColumn-1)/4; i++)
    {
        int shift = 4*i;
        int phi = excel.getCellValue(12, 3+shift).toInt();
//        qDebug() << phi;
        QVector<double> residueVector;

        residue = excel.getCellValue(15, 3+shift).toDouble();   // 中值
        residueVector.push_back(residue);
        residue = excel.getCellValue(15, 4+shift).toDouble();   // 均值
        residueVector.push_back(residue);
        residue = excel.getCellValue(15, 5+shift).toDouble();   // 众数
        residueVector.push_back(residue);
        map[phi] = residueVector;
    }
    excel.close();
    return map;
}

