#include "datalist.h"

DataList::DataList(QWidget *parent)
    :QWidget(parent)
{

    QPushButton *viewButton = new QPushButton("详细查看", this);
    QPushButton *deleteButton = new QPushButton("删除文件", this);
    fileListWidget = new QListWidget(this);    
    mainLayout = new QVBoxLayout(this);
//    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(fileListWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(viewButton);
    mainLayout->addLayout(buttonLayout);


    QObject::connect(fileListWidget,
                     static_cast<void (QListWidget:: *)(QListWidgetItem*)>(&QListWidget::itemDoubleClicked),
                     this,
                     &DataList::preview);

    QObject::connect(viewButton, &QPushButton::clicked, this, &DataList::viewButtonClicked);
    QObject::connect(deleteButton, &QPushButton::clicked, this, &DataList::deleteButtonClicked);
    // 当前路径下的MRL文件夹
    this->currentDir = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
}

void DataList::deleteButtonClicked()
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
    QMessageBox::StandardButton rb = QMessageBox::information(NULL,
                             QString("删除确认"),
                             QString("确定删除文件%1？").arg(item->text()),
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        xlsFile.remove();
        QMessageBox::information(NULL, "删除提示", QString("成功删除文件%1。").arg(item->text()));
        freshFileList();
    }
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
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *client = new QWidget();
    client->setLayout(mainLayout);
    scrollArea->setWidget(client);
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(scrollArea);

    QObject::connect(fileListWidget,
                     static_cast<void (QListWidget:: *)(QListWidgetItem*)>(&QListWidget::itemClicked),
                     this,
                     &DataDefinition::showFileInfo);

    // 当前路径下的MRL文件夹
    this->currentDir = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
    filter << "*.xls";
}

void DataDefinition::freshFileList()
{
    QDir rootDir(this->currentDir);    
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
            residue = excel.getCellValue(j, 2+shift).toDouble(&ok);
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
    QObject::connect(selectButton, &QPushButton::clicked,
                     this, &QQDataDefinition::selectButtonClicked);
    // 过滤文件
    filter.clear();
    filter << "限量分析_*.xls";
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
            residue = excel.getCellValue(j, 2+shift).toDouble(&ok);
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
    if(rb != QMessageBox::Yes)
    {
        this->residues.clear();
        return ;
    }
    this->residues = this->phis[key];
//    qDebug() <<"data->residues[key] = " << data->residues[key].size();
    PesticideData *data = this->getPesticideData(this->xlsFilePath);
    emit sendSelectedData(data, key);
    QMessageBox::information(NULL,
                             QString("提示"),
                             QString("已选择%1的间隔期为%2的数据!").arg(this->selectedFile).arg(key));
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
    QObject::connect(selectButton, &QPushButton::clicked,
                     this, &DigestionDataDefinition::selectButtonClicked);
    // 过滤文件
    filter.clear();
    filter << "限量分析_*.xls";
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
//    bool ok;
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

/*
 *******************************************************************************************************
 * 以下是AssessDataDefinition类实现
 *******************************************************************************************************
*/
AssessDataDefinition::AssessDataDefinition(QWidget *parent)
    :DataDefinition(parent)
{
    // 农药成分
    QLabel * pesticide = new QLabel(QStringLiteral("农药成分"), this);
    QLabel * chineseName = new QLabel(QStringLiteral("中文名"), this);
    chineseNameText = new QLineEdit(this);
    QLabel *englishName = new QLabel(QStringLiteral("英文名"), this);
    englishNameText = new QLineEdit(this);
    QLabel *chemicalName = new QLabel(QStringLiteral("化学名称"), this);
    chemicalNameText = new QLineEdit(this);
    QLabel *molecular = new QLabel(QStringLiteral("分子量"), this);
    molecularText = new QLineEdit(this);
    pesticideLayout = new QGridLayout();
    pesticideLayout->setMargin(10);
    pesticideLayout->setSpacing(10);
    pesticideLayout->addWidget(pesticide, 0, 0);
    pesticideLayout->addWidget(chineseName, 1, 1);
    pesticideLayout->addWidget(chineseNameText, 1, 2);
    pesticideLayout->addWidget(englishName, 2, 1);
    pesticideLayout->addWidget(englishNameText, 2, 2);
    pesticideLayout->addWidget(chemicalName, 3, 1);
    pesticideLayout->addWidget(chemicalNameText, 3, 2);
    pesticideLayout->addWidget(molecular, 4, 1);
    pesticideLayout->addWidget(molecularText, 4, 2);
    pesticideLayout->setColumnStretch(0, 1);
    pesticideLayout->setColumnStretch(1, 1);
    pesticideLayout->setColumnStretch(2, 3);

    QGridLayout *toxicLayout = new QGridLayout();
    QLabel *toxicityLabel = new QLabel(this);
    toxicityLabel->setText(QString("毒性评价"));
    QLabel*adiLabel = new QLabel(QString("每日允许驶入量（ADI）"), this);
    adiEdit= new QLineEdit(this);
    QLabel *arfdLabel = new QLabel(QString("急性参考剂量（ARfD）"), this);
    arfdEdit = new QLineEdit(this);
    toxicLayout->addWidget(toxicityLabel, 0, 0);
    toxicLayout->addWidget(adiLabel, 1, 1);
    toxicLayout->addWidget(adiEdit, 1, 2);
    toxicLayout->addWidget(arfdLabel, 2, 1);
    toxicLayout->addWidget(arfdEdit, 2, 2);
    toxicLayout->setColumnStretch(0, 1);
    toxicLayout->setColumnStretch(1, 1);
    toxicLayout->setColumnStretch(2, 3);

    /*
    toxicityLayout = new QHBoxLayout();
    residueLayout = new QHBoxLayout();
    populationLayout = new QHBoxLayout();
    populationGroup = new QButtonGroup(this);
    toxicityGroup = new QButtonGroup(this);
    residueGroup = new QButtonGroup(this);
    QLabel *toxicityLabel = new QLabel(this);
    toxicityLabel->setText(QString("毒性评价（单选）"));
    QRadioButton *adiRadio = new QRadioButton(this);
    adiRadio->setText(QString::fromLocal8Bit("每日允许驶入量（ADI）"));
    QRadioButton *arfdRadio = new QRadioButton(this);
    arfdRadio->setText(QString::fromLocal8Bit("急性参考剂量（ARfD）"));
    toxicityGroup->addButton(adiRadio);
    toxicityLayout->addWidget(adiRadio);
    toxicityGroup->addButton(arfdRadio);
    toxicityLayout->addWidget(arfdRadio);

    QLabel *residueLabel = new QLabel(this);
    residueLabel->setText(QString("残留水平（单选）"));
    QRadioButton *stmrRadio = new QRadioButton(this);
    stmrRadio->setText(QString::fromLocal8Bit("中值（STMR）"));
    QRadioButton *stmrpRadio= new QRadioButton(this);
    stmrpRadio->setText(QString::fromLocal8Bit("加工因子矫正的中值（STMR-P）"));
    QRadioButton *hrRadio= new QRadioButton(this);
    hrRadio->setText(QString::fromLocal8Bit("最大残留值(HR)"));
    QRadioButton *mrlRadio= new QRadioButton(this);
    mrlRadio->setText(QString::fromLocal8Bit("推荐残留值（MRL）"));
    residueGroup->addButton(stmrRadio);
    residueLayout->addWidget(stmrRadio);
    residueGroup->addButton(stmrpRadio);
    residueLayout->addWidget(stmrpRadio);
    residueGroup->addButton(hrRadio);
    residueLayout->addWidget(hrRadio);
    residueGroup->addButton(mrlRadio);
    residueLayout->addWidget(mrlRadio);

    // 设置不互斥
    populationGroup->setExclusive(false);
    QLabel *populationLabel = new QLabel(this);
    populationLabel->setText(QString("膳食暴露及人群信息（单选）"));
    QCheckBox *fiRadio= new QCheckBox(this);
    fiRadio->setText(QString::fromLocal8Bit("平均消费量（Fi）"));
    QCheckBox *lpRadio= new QCheckBox(this);
    lpRadio->setText(QString::fromLocal8Bit("最大消费量（LP）"));
    QCheckBox *uRadio= new QCheckBox(this);
    uRadio->setText(QString::fromLocal8Bit("农产品单个重量（U）"));
    QCheckBox *vRadio= new QCheckBox(this);
    vRadio->setText(QString::fromLocal8Bit("差异因子（V）"));
    QCheckBox *bwRadio= new QCheckBox(this);
    bwRadio->setText(QString::fromLocal8Bit("体重（BW）"));

    populationGroup->addButton(fiRadio);
    populationGroup->addButton(lpRadio);
    populationGroup->addButton(uRadio);
    populationGroup->addButton(vRadio);
    populationGroup->addButton(bwRadio);
    populationLayout->addWidget(fiRadio);
    populationLayout->addWidget(lpRadio);
    populationLayout->addWidget(uRadio);
    populationLayout->addWidget(vRadio);
    populationLayout->addWidget(bwRadio);

    populationLayout->setSpacing(10);
    populationLayout->setContentsMargins(10, 10, 10, 10);
    */

    selectButton = new QPushButton(QString("确认选择"), this);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(selectButton);
    // DataSheet
    QLabel *sheetLabel = new QLabel(QString("风险概率表"), this);
    dataSheet = new DataSheet(65536, 10, this);


    mainLayout->addLayout(pesticideLayout);
//    mainLayout->addWidget(toxicityLabel);
//    mainLayout->addLayout(toxicityLayout);
//    mainLayout->addWidget(residueLabel);
//    mainLayout->addLayout(residueLayout);
//    mainLayout->addWidget(populationLabel);
//    mainLayout->addLayout(populationLayout);
    mainLayout->addLayout(toxicLayout);
    mainLayout->addWidget(sheetLabel);
    mainLayout->addWidget(dataSheet);
    mainLayout->addLayout(buttonLayout);
    QObject::connect(selectButton, &QPushButton::clicked,
                     this, &AcuteDataDefinition::selectButtonClicked);
    // 过滤文件
    filter.clear();
    filter << "评估数据_*.xls";
}

void AssessDataDefinition::showFileInfo(QListWidgetItem *item)
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

    assessData = getAssessDataFromFile(xlsFilePath);
    this->chineseNameText->setText(assessData->chineseName);
    this->englishNameText->setText(assessData->englishName);
    this->chemicalNameText->setText(assessData->chemicalName);
    this->molecularText->setText(assessData->molecular);
    this->adiEdit->setText(QString::number(assessData->adi));
    this->arfdEdit->setText(QString::number(assessData->arfd));
//    result = this->dataSheet->updateAcuteContents(assessData);
    /*
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
    }
    */
}

void AssessDataDefinition::selectButtonClicked()
{
    if(NULL == assessData)
    {
        QMessageBox::critical(NULL, "错误提示", "请先在文件列表中选择实验数据");
        return;
    }
    emit sendSelectedData(assessData, result);
    QMessageBox::information(NULL, QString("提示"), QString("选择完毕"));
}

AssessData *AssessDataDefinition::getAssessDataFromFile(QString xlsFilePath)
{
    //打开文件，取得工作簿
    QExcel excel(xlsFilePath);
    excel.selectSheet(1);
    AssessData *data = new AssessData;
    data->chineseName = excel.getCellValue(1, 3).toString();
    data->englishName = excel.getCellValue(2, 3).toString();
    data->chemicalName = excel.getCellValue(3, 3).toString();
    data->molecular= excel.getCellValue(4, 3).toString();
    data->adi = excel.getCellValue(5, 3).toDouble();
    data->arfd= excel.getCellValue(6, 3).toDouble();
    QVector<FoodLimit*> food;
    //取得工作表已使用范围
    int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;
    excel.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
    for(int j=3; j <=bottomRightColumn; j++)
    {
        FoodLimit *f = new FoodLimit;
        f->food = excel.getCellValue(7, j).toString();
        f->stmr= excel.getCellValue(8, j).toDouble();
        f->stmrp= excel.getCellValue(9, j).toDouble();
        f->hr = excel.getCellValue(10, j).toDouble();
        f->mrl= excel.getCellValue(11, j).toDouble();
        f->Fi= excel.getCellValue(12, j).toDouble();
        f->LPi= excel.getCellValue(13, j).toDouble();
        f->Ui= excel.getCellValue(14, j).toDouble();
        f->Ei= excel.getCellValue(15, j).toDouble();
        f->CVi= excel.getCellValue(16, j).toDouble();
        f->BWi= excel.getCellValue(17, j).toDouble();
        food.push_back(f);
    }
    data->foodInfo = food;

    excel.close();
    return data;
}



/*
 *******************************************************************************************************
 * 以下是AcuteDataDefinition类实现
 *******************************************************************************************************
*/

AcuteDataDefinition::AcuteDataDefinition(QWidget *parent)
    :AssessDataDefinition(parent)
{
    QStringList headers;
    headers << QString("食物种类") <<QString("膳食量(kg)") << QString("参考限量(mg/kg)")
            << QString("限量来源") <<QString("NEDI(mg)") << QString("日允许摄入量（mg）")
            << QString("风险概率（%）");
    dataSheet->setHeader(headers);

}

void AcuteDataDefinition::showFileInfo(QListWidgetItem *item)
{
    AssessDataDefinition::showFileInfo(item);
    result = this->dataSheet->updateAcuteContents(assessData);
}


/*
 *******************************************************************************************************
 * 以下是ChronicDataDefinition类实现
 *******************************************************************************************************
*/

ChronicDataDefinition::ChronicDataDefinition(QWidget *parent)
    :AssessDataDefinition(parent)
{
    QStringList headers;
    headers << QString("食物种类") << QString("最高残留值(mg/kg)")
            << QString("体重(kg)") << QString("最大膳食消费量(g/人)")
            << QString("食物单位重量(g)")
            << QString("食物可食部分重量(g)") << QString("加工产品的STMR(mg/kg)")
            << QString("变异系数") <<QString("国际短期计算摄入量-IESTI")
            << QString("&ARfD");
    dataSheet->setHeader(headers);
}

void ChronicDataDefinition::showFileInfo(QListWidgetItem *item)
{
    AssessDataDefinition::showFileInfo(item);
    result = this->dataSheet->updateChronicContents(assessData);
}
