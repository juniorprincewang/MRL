#include "datainsertion.h"

DataInsertion::DataInsertion(QWidget *parent):
    QWidget(parent)
{
    // 农药成分
    pesticide = new QLabel(QStringLiteral("农药成分"), this);
    chineseName = new QLabel(QStringLiteral("中文名"), this);
    chineseNameText = new QLineEdit(this);
    englishName = new QLabel(QStringLiteral("英文名"), this);
    englishNameText = new QLineEdit(this);
    chemicalName = new QLabel(QStringLiteral("化学名称"), this);
    chemicalNameText = new QLineEdit(this);
    molecular = new QLabel(QStringLiteral("分子量"), this);
    molecularText = new QLineEdit(this);
    // 浮点型 范围：[-360, 360] 精度：小数点后2位
    QDoubleValidator *pDoubleValidator = new QDoubleValidator(this);
    molecularText->setValidator(pDoubleValidator);
    /*
    pesticideLayout = new QFormLayout();
    pesticideLayout->setMargin(10);
    pesticideLayout->setSpacing(10);
    pesticideLayout->addRow(pesticide);
    pesticideLayout->addRow(QStringLiteral("中文名"), chineseNameText);
    pesticideLayout->addRow(QStringLiteral("英文名"), englishNameText);
    pesticideLayout->addRow(QStringLiteral("化学名称"), chemicalNameText);
    pesticideLayout->addRow(QStringLiteral("分子量"), molecularText);
    */
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

    // 作用对象
    object = new QWidget(this);
    objectLayout = new QVBoxLayout();
    object->setLayout(objectLayout);
    QGridLayout *baseLayout = new QGridLayout();
    QLabel *objectTopLabel = new QLabel(QString("作用对象"), object);
    QLabel *ediblePart = new QLabel(QString("可食用部分"), object);
    ediblePartText = new QLineEdit(object);
    QLabel *nonEdiblePart = new QLabel(QString("不可食用部分"), object);
    nonEdiblePartText = new QLineEdit(object);
    QWidget *otherWidget = new QWidget(object);
    otherWidget->setObjectName("AddictivePart");
    QGridLayout *otherLayout = new QGridLayout();
    otherWidget->setLayout(otherLayout);
    QLabel *otherLabel = new QLabel(QString("其他部分"), otherWidget);
    QPushButton *addPartButton = new QPushButton(QString("添加其他"), otherWidget);
    QLineEdit *additivePartText = new QLineEdit(otherWidget);
    additivePartText->setObjectName("addictive");

    baseLayout->setMargin(10);
    baseLayout->setSpacing(10);
    baseLayout->addWidget(objectTopLabel, 0, 0);
    baseLayout->addWidget(ediblePart, 1, 1);
    baseLayout->addWidget(ediblePartText, 1, 2);
    baseLayout->addWidget(nonEdiblePart, 2, 1);
    baseLayout->addWidget(nonEdiblePartText, 2, 2);
    baseLayout->setColumnStretch(0, 1);
    baseLayout->setColumnStretch(1, 1);
    baseLayout->setColumnStretch(2, 3);
    objectLayout->addLayout(baseLayout);

    otherLayout->addWidget(addPartButton, 0, 0);
    otherLayout->addWidget(otherLabel, 0, 1);
    otherLayout->addWidget(additivePartText, 0, 2);
    objectLayout->addWidget(otherWidget);
    QObject::connect(addPartButton, &QPushButton::clicked, this, &DataInsertion::addAdditivePart);

    //实验方法
    operationMethod = new QLabel(QString("实验方式"), this);
    method = new QLabel(QString("施用方式"), this);
    methodText = new QLineEdit(this);
    frequency = new QLabel(QString("频率"), this);
    frequencyText = new QLineEdit(this);
    frequencyText->setPlaceholderText(QString("略"));
    dosage = new QLabel(QString("剂量"), this);
    dosageText = new QLineEdit(this);
    dosageText->setPlaceholderText(QString("略"));
    methodLayout = new QGridLayout();
    methodLayout->addWidget(operationMethod, 0, 0);
    methodLayout->addWidget(method, 1, 1);
    methodLayout->addWidget(methodText, 1, 2);
    methodLayout->addWidget(frequency, 2, 1);
    methodLayout->addWidget(frequencyText, 2, 2);
    methodLayout->addWidget(dosage, 3, 1);
    methodLayout->addWidget(dosageText, 3, 2);
    methodLayout->setColumnStretch(0, 1);
    methodLayout->setColumnStretch(1, 1);
    methodLayout->setColumnStretch(2, 3);
    // 实验地点
    location = new QWidget(this);
    locationLayout = new QVBoxLayout();
    location->setLayout(locationLayout);
    QLabel *locationTopLabel = new QLabel(QString("实验地点"), location);
    QPushButton *addLocButton = new QPushButton(QString("添加地点"), location);
    locationLayout->addWidget(locationTopLabel);
    QWidget *tempLoc = new QWidget(location);
    tempLoc->setObjectName("Location");
    QGridLayout *tempLocLayout= new QGridLayout();
    QLabel *locationLabel = new QLabel(QString("地点"), tempLoc);
    QLineEdit* locationText = new QLineEdit(tempLoc);
    locationText->setObjectName("location");
    tempLocLayout->addWidget(addLocButton, 0, 0);
    tempLocLayout->addWidget(locationLabel, 0, 1);
    tempLocLayout->addWidget(locationText, 0, 2);
//    tempLocLayout->setColumnStretch(0, 1);
//    tempLocLayout->setColumnStretch(1, 1);
//    tempLocLayout->setColumnStretch(2, 3);
    tempLoc->setLayout(tempLocLayout);
    this->locationLayout->addWidget(tempLoc);

    QObject::connect(addLocButton, &QPushButton::clicked, this, &DataInsertion::addLocationText);
    //残留水平
    residue = new QWidget(this);
    residueLayout = new QVBoxLayout();
    residue->setLayout(residueLayout);
    QWidget *residueWidget = new QWidget(residue);
    residueWidget->setObjectName("Residue");
    QLabel *residueTopLevel= new QLabel(QStringLiteral("残留水平"), residueWidget);
    QLabel *phi = new QLabel(QStringLiteral("实验时间（天）"), residueWidget);
    QLineEdit *phiText = new QLineEdit(this);
    phiText->setObjectName("phi");
    // 整形 范围：[1, 99]
    QIntValidator *pIntValidator = new QIntValidator(residueWidget);
//    pIntValidator->setRange(1, 99);
    phiText->setValidator(pIntValidator);
    QLabel *residueLabel = new QLabel(QStringLiteral("残留量"), residueWidget);
    QTextEdit *residueText = new QTextEdit(residueWidget);
    residueText->setObjectName("residue");

    QPushButton *addPhiButton = new QPushButton(QStringLiteral("添加实验数据"), residueWidget);
    QGridLayout *tempLayout = new QGridLayout();
    tempLayout->addWidget(residueTopLevel, 0, 0);
    tempLayout->addWidget(phi, 1, 1);
    tempLayout->addWidget(phiText, 1, 2);
    tempLayout->addWidget(residueLabel, 1, 3);
    tempLayout->addWidget(residueText, 1, 4);
    tempLayout->addWidget(addPhiButton, 2, 0);
    tempLayout->setColumnStretch(0, 1);
    tempLayout->setColumnStretch(1, 1);
    tempLayout->setColumnStretch(2, 3);
    tempLayout->setColumnStretch(3, 1);
    tempLayout->setColumnStretch(4, 3);
    residueWidget->setLayout(tempLayout);
    residueLayout->addWidget(residueWidget);
    QObject::connect(addPhiButton, &QPushButton::clicked, this, &DataInsertion::addPhi);

    // 预览，添加，修改按钮
    QPushButton *previewButton = new QPushButton(QStringLiteral("预览"), this);
    QPushButton *saveButton = new QPushButton(QStringLiteral("保存"), this);
    QPushButton *cancelButton= new QPushButton(QStringLiteral("取消"), this);
    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(previewButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    /*布局*/
    mainLayout = new QVBoxLayout();
    // 农药成分
    mainLayout->addLayout(pesticideLayout);
    // 作用对象
//    mainLayout->addLayout(objectLayout);
    mainLayout->addWidget(object);
//    mainLayout->addStretch();
    //方法
    mainLayout->addLayout(methodLayout);
    //地点
//    mainLayout->addLayout(locationLayout);
    mainLayout->addWidget(location);
    // 残留水平
//    mainLayout->addLayout(residueLayout);
    mainLayout->addWidget(residue);

    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    // 设置滚动轴
    QWidget *client = new QWidget();
    client->setLayout(mainLayout);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(client);
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(scrollArea);
//    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    QObject::connect(saveButton, &QPushButton::clicked, this, &DataInsertion::save);
    QObject::connect(previewButton, &QPushButton::clicked, this, &DataInsertion::preview);
    QObject::connect(cancelButton, &QPushButton::clicked, this, &DataInsertion::cancel);

    preset();
    // 在当前路径下生成MRL文件夹
    QDir dir(QDir::currentPath());
    if(!dir.mkdir(QString("MRL")))
        qDebug() << "the directory already exists or something wrong!";
}
void DataInsertion::preset()
{
    this->chineseNameText->setText("甲氨基阿维菌素苯甲酸盐");
    this->englishNameText->setText("Emamectin Benzoate");
    this->chemicalNameText->setText("4'-表-甲胺基-4'-脱氧阿维菌素苯甲酸盐");
    this->molecularText->setText("1008.24");

    this->ediblePartText->setText("稻谷");
    this->nonEdiblePartText->setText("水稻秸秆");

    QList<QWidget*> otherList =  this->object->findChildren<QWidget*>("AddictivePart", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, otherList)
    {
        temp->findChild<QLineEdit*>("addictive", Qt::FindDirectChildrenOnly)->setText(QString("土壤"));
    }
    this->methodText->setText("喷施");
    this->frequencyText->setText("略");
    this->dosageText->setText("略");


    QList<QWidget*> locationList =  this->location->findChildren<QWidget*>("Location", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, locationList)
    {
        temp->findChild<QLineEdit*>("location", Qt::FindDirectChildrenOnly)->setText(QString("黑龙江"));
    }
    QList<QWidget*> residueList =  this->residue->findChildren<QWidget*>("Residue", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, residueList)
    {
        temp->findChild<QLineEdit*>("phi", Qt::FindDirectChildrenOnly)->setText(QString::number(5));
        temp->findChild<QTextEdit*>("residue", Qt::FindDirectChildrenOnly)->setText("0.010\n0.010\n0.010\n0.010\n0.010\n0.010\n0.010\n0.070\n0.120\n0.190\n0.220\n0.230\n0.260\n0.270\n0.280\n0.330\n0.490\n1.100\n1.200\n1.300\n1.400\n1.600\n1.600\n1.600");
    }

}

void DataInsertion::addAdditivePart()
{
    QWidget *otherWidget = new QWidget(this->object);
    otherWidget->setObjectName("AddictivePart");
    QGridLayout *otherLayout = new QGridLayout();
    otherWidget->setLayout(otherLayout);
    QLabel *otherLabel = new QLabel(QString("其他部分"), otherWidget);
    QPushButton *deletePartButton = new QPushButton(QString("删除此行"), otherWidget);
    QLineEdit *additivePartText = new QLineEdit(otherWidget);
    additivePartText->setObjectName("addictive");
    otherLayout->addWidget(deletePartButton, 0, 0);
    otherLayout->addWidget(otherLabel, 0, 1);
    otherLayout->addWidget(additivePartText, 0, 2);
    objectLayout->addWidget(otherWidget);
    QObject::connect(deletePartButton, &QPushButton::clicked, this, &DataInsertion::deleteAdditivePart);

}

void DataInsertion::deleteAdditivePart()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    if(pButton)
    {
        QWidget* tempWidget = (pButton->parentWidget());
        this->objectLayout->removeWidget(tempWidget);
        delete tempWidget;
    }
}

void DataInsertion::addLocationText()
{
    QWidget *temp = new QWidget(this->location);
    temp->setObjectName("Location");
    QGridLayout *tempLayout= new QGridLayout();
    QLabel *locationLabel = new QLabel(QString("地点"), temp);
    QLineEdit* locationText = new QLineEdit(temp);
    locationText->setObjectName("location");
    QPushButton *deleteBtn = new QPushButton(QString("删除此行"), temp);
    tempLayout->addWidget(deleteBtn, 0, 0);
    tempLayout->addWidget(locationLabel, 0, 1);
    tempLayout->addWidget(locationText, 0, 2);
//    tempLayout->setColumnStretch(0, 1);
//    tempLayout->setColumnStretch(1, 1);
//    tempLayout->setColumnStretch(2, 3);
    temp->setLayout(tempLayout);
    this->locationLayout->addWidget(temp);

    QObject::connect(deleteBtn, &QPushButton::clicked, this, &DataInsertion::deleteLocationText);

}
void DataInsertion::deleteLocationText()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    if(pButton)
    {
        QWidget* tempWidget = (pButton->parentWidget());
        this->locationLayout->removeWidget(tempWidget);
        delete tempWidget;
    }
}

void DataInsertion::addPhi()
{
    QWidget *residueWidget = new QWidget(this->residue);
    residueWidget->setObjectName("Residue");
    QLabel *phi = new QLabel(QString("实验时间（天）"), residueWidget);
    QLineEdit *phiText = new QLineEdit(residueWidget);
    phiText->setObjectName("phi");
    // 整形 范围：[1, 99]
    QIntValidator *pIntValidator = new QIntValidator(residueWidget);
//    pIntValidator->setRange(1, 99);
    phiText->setValidator(pIntValidator);
    QLabel *residueLabel = new QLabel(QString("残留量"), residueWidget);
    QTextEdit *residueText = new QTextEdit(residueWidget);
    residueText->setObjectName("residue");
    QPushButton *deletePhiButton = new QPushButton(QString("删除此行数据"), residueWidget);
    QGridLayout *tempLayout = new QGridLayout();
    tempLayout->addWidget(deletePhiButton, 0, 0);
    tempLayout->addWidget(phi, 0, 1);
    tempLayout->addWidget(phiText, 0, 2);
    tempLayout->addWidget(residueLabel, 0, 3);
    tempLayout->addWidget(residueText, 0, 4);
    tempLayout->setColumnStretch(0, 1);
    tempLayout->setColumnStretch(1, 1);
    tempLayout->setColumnStretch(2, 3);
    tempLayout->setColumnStretch(3, 1);
    tempLayout->setColumnStretch(4, 3);
    residueWidget->setLayout(tempLayout);
    residueLayout->addWidget(residueWidget);
    QObject::connect(deletePhiButton, &QPushButton::clicked, this, &DataInsertion::deletePhi);
}

void DataInsertion::deletePhi()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    if(pButton)
    {
        QWidget* tempWidget = (pButton->parentWidget());
        this->residueLayout->removeWidget(tempWidget);
        delete tempWidget;
    }
}

bool DataInsertion::checkValidation()
{
    if(this->chemicalNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("化学名称"));
        return false;
    }
    if(this->chineseNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("中文名"));
        return false;
    }
    if(this->englishNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("英文名"));
        return false;
    }
    if(this->molecularText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("分子量"));
        return false;
    }
    if(this->ediblePartText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("可食用部分"));
        return false;
    }
    if(this->nonEdiblePartText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("不可食用部分"));
        return false;
    }
    if(this->methodText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("施用方式"));
        return false;
    }
    if(this->frequencyText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("频率"));
        return false;
    }
    if(this->dosageText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("剂量"));
        return false;
    }

    QList<QWidget*> residueList =  this->residue->findChildren<QWidget*>("Residue", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, residueList)
    {
        QString string = temp->findChild<QLineEdit*>("phi", Qt::FindDirectChildrenOnly)->text();
        if(string.isEmpty())
        {
            QMessageBox::critical(NULL, QString("间隔期错误"), QString("实验时间不能为空"));
            return false;
        }
        bool ok;
        int phi = string.toInt(&ok);
        if(!ok)
        {
            QMessageBox::warning(NULL, QString("间隔期错误"), QString("实验时间无效!"));
            return false;
        }
        if(temp->findChild<QTextEdit*>("residue", Qt::FindDirectChildrenOnly)->toPlainText().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("实验残留量不能为空"));
            return false;
        }
    }

    QList<QWidget*> locationList =  this->location->findChildren<QWidget*>("Location", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, locationList)
    {
        if(temp->findChild<QLineEdit*>("location", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("实验地点不能为空"));
            return false;
        }
    }
    QList<QWidget*> partList =  this->objectLayout->findChildren<QWidget*>("AddictivePart", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, partList)
    {
        if(temp->findChild<QLineEdit*>("addictive", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("作用对象其他部分不能为空"));
            return false;
        }
    }
    return true;
}

void DataInsertion::preview()
{
    if(NULL == this->xlsFilePath)
    {
        QMessageBox::critical(NULL, QString("警告"), QString("先保存，在预览！"));
        return;
    }
    //打开文件，取得工作簿
    QExcel excel(xlsFilePath);

}
void DataInsertion::save()
{    
    if(!this->checkValidation())
        return;
//    qDebug() << "save";

    PesticideData *pesticide = new PesticideData();
    pesticide->chineseName = QString::fromLocal8Bit(chineseNameText->text().trimmed().toUtf8());
    pesticide->englishName = QString::fromLocal8Bit(englishNameText->text().trimmed().toUtf8());
    pesticide->chemicalName = QString::fromLocal8Bit(chemicalNameText->text().trimmed().toUtf8());
    pesticide->molecular = QString::fromLocal8Bit(molecularText->text().trimmed().toUtf8());
    pesticide->edible = QString::fromLocal8Bit(ediblePartText->text().trimmed().toUtf8());
    pesticide->nonedible = QString::fromLocal8Bit(nonEdiblePartText->text().trimmed().toUtf8());
    pesticide->method= QString::fromLocal8Bit(methodText->text().trimmed().toUtf8());
    pesticide->frequency= QString::fromLocal8Bit(frequencyText->text().trimmed().toUtf8());
    pesticide->dosage= QString::fromLocal8Bit(dosageText->text().trimmed().toUtf8());
    QVector<QString> locations;
    QList<QWidget*> locationList =  this->location->findChildren<QWidget*>("Location", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, locationList)
    {
        locations.push_back(temp->findChild<QLineEdit*>("location", Qt::FindDirectChildrenOnly)->text().trimmed());
    }
    pesticide->location = locations;
    QVector<QString> additive;
    QList<QWidget*> partList =  this->object->findChildren<QWidget*>("AddictivePart", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, partList)
    {
        additive.push_back(temp->findChild<QLineEdit*>("addictive", Qt::FindDirectChildrenOnly)->text().trimmed());
    }
    pesticide->additive = additive;

    QList<QWidget*> residueList =  this->residue->findChildren<QWidget*>("Residue", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, residueList)
    {
        bool ok;
        int phi = temp->findChild<QLineEdit*>("phi", Qt::FindDirectChildrenOnly)->text().toInt(&ok);
        QString plainText = temp->findChild<QTextEdit*>("residue", Qt::FindDirectChildrenOnly)->toPlainText();
        QStringList list = plainText.split("\n", QString::SkipEmptyParts);
        QVector<double> tempVector;
        int residueSize = list.size();
        for(int j=0; j<residueSize; j++)
        {
            double residues = list.at(j).toDouble(&ok);
            if(!ok)
            {
                QMessageBox::warning(NULL, QString("残留量错误"), QString("实验数据中残留量值无效!"));
                return;
            }
            tempVector.push_back(residues);
        }
        pesticide->residues[phi] = tempVector;

    }
    this->xlsFilePath = QString("%1/%2/限量分析_%3.xls").arg(QDir::currentPath()).arg("MRL").arg(pesticide->chineseName);
    saveToExcel(pesticide, this->xlsFilePath);
}

void DataInsertion::generateExcelTemplate(QString xlsFilePath)
{

    //创建文件，取得工作簿
    QExcel excel;
    //插入数据
    excel.selectSheet("Sheet1");
    excel.setCellValue("A1", QStringLiteral("农药信息"));
    excel.mergeCells("A1:A4");
    excel.setCellValue("B1", QStringLiteral("中文名"));
    excel.setCellValue("B2", QStringLiteral("英文名"));
    excel.setCellValue("B3", QStringLiteral("化学名称"));
    excel.setCellValue("B4", QStringLiteral("分子量"));
    excel.setCellValue("A5", QStringLiteral("作用对象"));
    excel.mergeCells("A5:A7");
    excel.setCellValue("B5", QStringLiteral("可食部分"));
    excel.setCellValue("B6", QStringLiteral("不可食部分"));
    excel.setCellValue("B7", QStringLiteral("其他（根据用户自行添加，该项目包括土壤、田水等）"));
    excel.setCellValue("A8", QStringLiteral("实验方式"));
    excel.mergeCells("A8:A10");
    excel.setCellValue("B8", QStringLiteral("施用方式"));
    excel.setCellValue("B9", QStringLiteral("频率"));
    excel.setCellValue("B10", QStringLiteral("剂量"));
    excel.setCellValue("A11", QStringLiteral("实验地点"));

    excel.setCellValue("A12", QStringLiteral("残留水平"));
    excel.setCellValue("B12", QStringLiteral("实验时间(天)"));
    excel.setCellValue("B13", QStringLiteral("残留量"));
    excel.mergeCells("B13:E13");
    excel.setCellValue("B14", QStringLiteral("原值"));
    excel.setCellValue("C14", QStringLiteral("中值"));
    excel.setCellValue("D14", QStringLiteral("均值"));
    excel.setCellValue("E14", QStringLiteral("众数"));

//        excel.mergeCells("A8:A10");

    excel.saveAs(xlsFilePath);
    excel.close();
}

void DataInsertion::saveToExcel(PesticideData *data, QString xlsFilePath)
{
    //创建文件，取得工作簿
    QExcel excel;
    //插入数据
    excel.selectSheet("Sheet1");
    excel.setCellValue("A1", QStringLiteral("农药信息"));
    excel.mergeCells("A1:A4");
    excel.setCellValue("B1", QStringLiteral("中文名"));
    excel.setCellValue("B2", QStringLiteral("英文名"));
    excel.setCellValue("B3", QStringLiteral("化学名称"));
    excel.setCellValue("B4", QStringLiteral("分子量"));

    excel.setCellValue("C1", (data->chineseName));
    excel.setCellValue("C2", (data->englishName));
    excel.setCellValue("C3", (data->chemicalName));
    excel.setCellValue("C4", (data->molecular));

    excel.setCellValue("A5", QStringLiteral("作用对象"));
    excel.mergeCells("A5:A7");
    excel.setCellValue("B5", QStringLiteral("可食部分"));
    excel.setCellValue("B6", QStringLiteral("不可食部分"));
    excel.setCellValue("B7", QStringLiteral("其他（根据用户自行添加，该项目包括土壤、田水等）"));
    excel.setCellValue("C5", (data->edible));
    excel.setCellValue("C6", (data->nonedible));
    for(int i=0; i< data->additive.size(); i++)
    {
        excel.setCellValue(7, 3+i, (data->additive.at(i)));
    }

    excel.setCellValue("A8", QStringLiteral("实验方式"));
    excel.mergeCells("A8:A10");
    excel.setCellValue("B8", QStringLiteral("施用方式"));
    excel.setCellValue("B9", QStringLiteral("频率"));
    excel.setCellValue("B10", QStringLiteral("剂量"));
    excel.setCellValue("C8", (data->method));
    excel.setCellValue("C9", (data->frequency));
    excel.setCellValue("C10", (data->dosage));
    excel.setCellValue("A11", QStringLiteral("实验地点"));
    for(int i=0; i< data->location.size(); i++)
    {
        excel.setCellValue(11, 2+i, (data->location.at(i)));
    }

    excel.setCellValue("A12", QStringLiteral("残留水平"));
    int phiCount = 0;
    QMap<int, QVector<double>>::const_iterator i = data->residues.constBegin();
    for(; i!= data->residues.constEnd(); i++, phiCount++)
    {
        int shift = 4*phiCount;
        excel.setCellValue(12, 2+shift, QStringLiteral("实验时间(天)"));
        excel.setCellValue(13, 2+shift, QStringLiteral("残留量"));
        excel.mergeCells(13, 2+shift, 13, 5+4*phiCount);
        excel.setCellValue(14, 2+shift, QStringLiteral("原值"));
        excel.setCellValue(14, 3+shift, QStringLiteral("中值"));
        excel.setCellValue(14, 4+shift, QStringLiteral("均值"));
        excel.setCellValue(14, 5+shift, QStringLiteral("众数"));
        excel.setCellValue(12, 3+shift, (i.key()));
        QVector<double> residuesVec = i.value();
        for(int row=0; row < residuesVec.size(); row++)
        {
            excel.setCellValue(15+row, 2+shift, (residuesVec.at(row)));
        }
        Model model;
        excel.setCellValue(15, 3+shift, model.getMedian(residuesVec.toStdVector()));
        excel.setCellValue(15, 4+shift, model.getMean(residuesVec.toStdVector()));
        excel.setCellValue(15, 5+shift, model.getMode(residuesVec.toStdVector()));
    }

    excel.saveAs(xlsFilePath);
    excel.close();
}



void DataInsertion::testSaveToExcel()
{
    // 在当前路径下生成MRL文件夹
    QDir dir(QDir::currentPath());
    if(!dir.mkdir(QString("MRL")))
        qDebug() << "the directory already exists or something wrong!";
    QString currentPath = QString("%1/%2/%3").arg(QDir::currentPath()).arg("MRL").arg("temp.xls");
    qDebug() << currentPath;
    //创建文件，取得工作簿
    QExcel excel;
    //插入数据
    excel.selectSheet("Sheet1");
    excel.mergeCells("A1:A4");
    excel.setCellValue("A1", QStringLiteral("农药信息"));

    excel.saveAs(currentPath);
    excel.close();
    qDebug()<<"App End";
}
    void WriteTest()
    {
        QAxObject *excel = new QAxObject();
        excel->setControl("Excel.Application");
        excel->dynamicCall("SetVisible (bool Visible)","true");
        excel->setProperty("DisplayAlerts", false);
        QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
        workbooks->dynamicCall("Open(const QString&)", "D:/C++/Projects/QT/build-HelloWorld-unknown-Debug/MRL/temp.xlsx");
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
        QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);
        QAxObject *range = worksheet->querySubObject("Cells(int,int)", 1, 1);
        range->dynamicCall("Value", "这就是这样啊");
        workbook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators("D:/C++/Projects/QT/build-HelloWorld-unknown-Debug/MRL/temp.xlsx"));
        workbook->dynamicCall("Close()");
        excel->dynamicCall("Quit()");
        delete excel;
        excel = NULL;
    }
void DataInsertion::cancel()
{
//    testSaveToExcel();
}
