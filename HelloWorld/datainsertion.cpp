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
    object = new QLabel(QStringLiteral("作用对象"), this);
    ediblePart = new QLabel(QStringLiteral("可食用部分"), this);
    ediblePartText = new QLineEdit(this);
    nonEdiblePart = new QLabel(QStringLiteral("不可食用部分"), this);
    nonEdiblePartText = new QLineEdit(this);
    QLineEdit *additivePartText = new QLineEdit(this);
    additivePartList<<additivePartText;
    additivePartButton = new QPushButton(QStringLiteral("添加其他"), this);
    objectLayout = new QGridLayout();
    objectLayout->setMargin(10);
    objectLayout->setSpacing(10);
    objectLayout->addWidget(object, 0, 0);
    objectLayout->addWidget(ediblePart, 1, 1);
    objectLayout->addWidget(ediblePartText, 1, 2);
    objectLayout->addWidget(nonEdiblePart, 2, 1);
    objectLayout->addWidget(nonEdiblePartText, 2, 2);
    objectLayout->addWidget(additivePartButton, 3, 1);
    objectLayout->addWidget(additivePartText, 3, 2);
    objectLayout->setColumnStretch(0, 1);
    objectLayout->setColumnStretch(1, 1);
    objectLayout->setColumnStretch(2, 3);
    QObject::connect(additivePartButton, &QPushButton::clicked, this, &DataInsertion::addAdditivePart);

    //实验方法
    operationMethod = new QLabel(QStringLiteral("实验方式"), this);
    method = new QLabel(QStringLiteral("施用方式"), this);
    methodText = new QLineEdit(this);
    frequency = new QLabel(QStringLiteral("频率"), this);
    frequencyText = new QLineEdit(this);
    frequencyText->setPlaceholderText(QString::fromLocal8Bit("略"));
    dosage = new QLabel(QStringLiteral("剂量"), this);
    dosageText = new QLineEdit(this);
    dosageText->setPlaceholderText(QString::fromLocal8Bit("略"));
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
    location = new QLabel(QStringLiteral("实验地点"), this);
    locationButton = new QPushButton(QStringLiteral("添加地点"), this);
    QLineEdit* locationText = new QLineEdit(this);
    locationList<<locationText;
    locationLayout = new QGridLayout();
    locationLayout->addWidget(location, 0, 0);
    locationLayout->addWidget(locationButton, 1, 1);
    locationLayout->addWidget(locationText, 1, 2);
    locationLayout->setColumnStretch(0, 1);
    locationLayout->setColumnStretch(1, 1);
    locationLayout->setColumnStretch(2, 3);
    QObject::connect(locationButton, &QPushButton::clicked, this, &DataInsertion::addLocationText);
    //残留水平
    residueLevel = new QLabel(QStringLiteral("残留水平"), this);
    QLabel *phi = new QLabel(QStringLiteral("实验时间（天）"), this);
    QLineEdit *phiText = new QLineEdit(this);
    // 整形 范围：[1, 99]
    QIntValidator *pIntValidator = new QIntValidator(this);
//    pIntValidator->setRange(1, 99);
    phiText->setValidator(pIntValidator);
    QLabel *residue = new QLabel(QStringLiteral("残留量"), this);
    QTextEdit *residueText = new QTextEdit(this);
    phiList<<phiText;
    residueList<<residueText;
    addPhiButton = new QPushButton(QStringLiteral("添加实验数据"), this);
    residueLayout = new QGridLayout();
    residueLayout->addWidget(residueLevel, 0, 0);
    residueLayout->addWidget(phi, 1, 1);
    residueLayout->addWidget(phiText, 1, 2);
    residueLayout->addWidget(residue, 1, 3);
    residueLayout->addWidget(residueText, 1, 4);
    residueLayout->addWidget(addPhiButton, 2, 1);
    residueLayout->setColumnStretch(0, 1);
    residueLayout->setColumnStretch(1, 1);
    residueLayout->setColumnStretch(2, 3);
    residueLayout->setColumnStretch(3, 1);
    residueLayout->setColumnStretch(4, 3);
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
    mainLayout = new QVBoxLayout(this);
    // 农药成分
    mainLayout->addLayout(pesticideLayout);
    // 作用对象
    mainLayout->addLayout(objectLayout);
//    mainLayout->addStretch();
    //方法
    mainLayout->addLayout(methodLayout);
    //地点
    mainLayout->addLayout(locationLayout);
    // 残留水平
    mainLayout->addLayout(residueLayout);

    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
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
    foreach(QLineEdit *l , this->additivePartList)
        l->setText("土壤");
    this->methodText->setText("喷施");
    this->frequencyText->setText("略");
    this->dosageText->setText("略");

    foreach(QLineEdit *l, this->locationList)
    {
        l->setText("黑龙江");
    }
    foreach(QLineEdit *l, this->phiList)
    {
        l->setText(QString::number(5));
    }
    foreach(QTextEdit *l, this->residueList)
    {
        l->setText("0.010\n0.010\n0.010\n0.010\n0.010\n0.010\n0.010\n0.070\n0.120\n0.190\n0.220\n0.230\n0.260\n0.270\n0.280\n0.330\n0.490\n1.100\n1.200\n1.300\n1.400\n1.600\n1.600\n1.600");
    }

}

void DataInsertion::addAdditivePart()
{
    int rowCount = this->objectLayout->rowCount();
    QLineEdit *additivePartText = new QLineEdit(this);
    this->additivePartList<<additivePartText;
    this->objectLayout->addWidget(additivePartText, rowCount, 2);
}

void DataInsertion::addLocationText()
{
    int rowCount = this->locationLayout->rowCount();
    QLineEdit *locationText = new QLineEdit(this);
    this->locationList<<locationText;
    this->locationLayout->addWidget(locationText, rowCount, 2);
}

void DataInsertion::addPhi()
{
    int rowCount = this->residueLayout->rowCount();
    QLabel *phi2 = new QLabel(QStringLiteral("实验时间（天）"), this);
    QLineEdit *phiText2 = new QLineEdit(this);
    // 整形
    QIntValidator *pIntValidator = new QIntValidator(this);
    phiText2->setValidator(pIntValidator);
    QLabel *residue2 = new QLabel(QStringLiteral("残留量"), this);
    QTextEdit *residueText2 = new QTextEdit(this);
    this->phiList << phiText2;
    this->residueList << residueText2;
    this->residueLayout->addWidget(phi2, rowCount, 1);
    this->residueLayout->addWidget(phiText2, rowCount, 2);
    this->residueLayout->addWidget(residue2, rowCount, 3);
    this->residueLayout->addWidget(residueText2, rowCount, 4);
}

bool DataInsertion::checkValidation()
{
    if(this->chemicalNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("化学名称"));
        return false;
    }
    if(this->chineseNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("中文名"));
        return false;
    }
    if(this->englishNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("英文名"));
        return false;
    }
    if(this->molecularText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("分子量"));
        return false;
    }
    if(this->ediblePartText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("可食用部分"));
        return false;
    }
    if(this->nonEdiblePartText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("不可食用部分"));
        return false;
    }
    if(this->methodText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("施用方式"));
        return false;
    }
    if(this->frequencyText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("频率"));
        return false;
    }
    if(this->dosageText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("剂量"));
        return false;
    }

    foreach (QLineEdit* l, this->phiList)
    {
        if(l->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("phi不能为空"));
            return false;
        }
    }

    foreach (QTextEdit* l, this->residueList)
    {
        if(l->toPlainText().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("residue不能为空"));
            return false;
        }
    }
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

//    QString plainText = this->residueText->toPlainText();
//    QStringList list = plainText.split("\n", QString::SkipEmptyParts);
//    QVector<double> residueVector;

//    for(int i=0; i<list.size(); i++)
//    {
//        bool ok;
//        double residue = list.at(i).toDouble(&ok);
//        if(!ok)
//        {
//            QMessageBox::warning(NULL, "Residues Value Format Error!", QString("%1 at line %2 is invalid!").arg(list.at(i)).arg(i+1));
//            return;
//        }
//        residueVector.push_back(residue);
//    }
//    foreach (QLineEdit* l, this->additivePartList)
//    {
//        if(l->text().isEmpty())
//        {
//            QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("其他部分"));
//            return;
//        }
//    }
    if(!this->checkValidation())
        return;

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
    QVector<QString> location;
    foreach(QLineEdit*l, locationList)
    {
        location.push_back(l->text().trimmed().toUtf8());
    }
    pesticide->location = location;
    QVector<QString> additive;
    foreach(QLineEdit*l, this->additivePartList)
    {
        additive.push_back(l->text().trimmed().toUtf8());
    }
    pesticide->additive = additive;

    int phiSize = phiList.size();
    for(int i=0; i< phiSize; i++)
    {
        bool ok;
        int phi = phiList.at(i)->text().toInt(&ok);
        if(!ok)
        {
            QMessageBox::warning(NULL, QStringLiteral("间隔期错误"), QString("phi at line %1 is invalid!%!").arg(i+1));
            return;
        }
        QVector<double> temp;
        QString plainText = residueList.at(i)->toPlainText();
        QStringList list = plainText.split("\n", QString::SkipEmptyParts);

        int residueSize = list.size();
        for(int j=0; j<residueSize; j++)
        {
            double residue = list.at(j).toDouble(&ok);
            if(!ok)
            {
                QMessageBox::warning(NULL, QStringLiteral("残留量错误"), QString("%residue at line %1 is invalid!%!").arg(i+1));
                return;
            }
            temp.push_back(residue);
        }
        pesticide->residues[phi] = temp;
    }

    this->xlsFilePath = QString("%1/%2/%3.xls").arg(QDir::currentPath()).arg("MRL").arg(pesticide->chineseName);
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
