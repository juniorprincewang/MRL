#include "assessdatainsertion.h"

AssessDataInsertion::AssessDataInsertion(QWidget *parent):
    QWidget(parent)
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
    // 浮点型 范围：[-360, 360] 精度：小数点后2位
    QDoubleValidator *pDoubleValidator = new QDoubleValidator(this);
    molecularText->setValidator(pDoubleValidator);

    pesticideLayout = new QGridLayout();
    pesticideLayout->setMargin(10);
    pesticideLayout->setSpacing(10);
    pesticideLayout->addWidget(pesticide,0, 0, 4, 1);
    pesticideLayout->addWidget(chineseName, 0, 1);
    pesticideLayout->addWidget(chineseNameText, 0, 2);
    pesticideLayout->addWidget(englishName, 1, 1);
    pesticideLayout->addWidget(englishNameText, 1, 2);
    pesticideLayout->addWidget(chemicalName, 2, 1);
    pesticideLayout->addWidget(chemicalNameText, 2, 2);
    pesticideLayout->addWidget(molecular, 3, 1);
    pesticideLayout->addWidget(molecularText, 3, 2);
    pesticideLayout->setColumnStretch(0, 1);
    pesticideLayout->setColumnStretch(1, 1);
    pesticideLayout->setColumnStretch(2, 3);

    // 毒性评价
    QLabel *toxicity = new QLabel(QStringLiteral("毒性评价"), this);
    QLabel *adi = new QLabel(QStringLiteral("每日允许驶入量（mg/kg）"), this);
    adiText = new QLineEdit(this);
    adiText->setValidator(pDoubleValidator);
    adiText->setPlaceholderText(QString::number(0));
    QLabel *arfd = new QLabel(QStringLiteral("急性参考剂量（mg/kg）"), this);
    arfdText = new QLineEdit(this);
    arfdText->setValidator(pDoubleValidator);
    arfdText->setPlaceholderText(QString::number(0));
    toxicityLayout = new QGridLayout();
    toxicityLayout->setMargin(10);
    toxicityLayout->setSpacing(10);
    toxicityLayout->addWidget(toxicity, 0, 0, 2, 1);
    toxicityLayout->addWidget(adi, 0, 1);
    toxicityLayout->addWidget(adiText, 0, 2);
    toxicityLayout->addWidget(arfd, 1, 1);
    toxicityLayout->addWidget(arfdText, 1, 2);
    toxicityLayout->setColumnStretch(0, 1);
    toxicityLayout->setColumnStretch(1, 1);
    toxicityLayout->setColumnStretch(2, 3);
    //残留水平
    diet = new QWidget(this);
    QWidget *tempWidget = new QWidget(diet);
    tempWidget->setObjectName("Residue");
    QLabel *residue = new QLabel(QStringLiteral("膳食暴露及人群信息"), tempWidget);
    QLabel *foodLabel = new QLabel(QStringLiteral("食物种类"), tempWidget);
    QLineEdit *foodText = new QLineEdit(tempWidget);
    foodText->setObjectName("food");
//    QLabel *intakeLabel= new QLabel(QStringLiteral("膳食量"), tempWidget);
//    QLineEdit *intakeText = new QLineEdit(tempWidget);
    QLabel *stmrLabel = new QLabel(QStringLiteral("残留量中值（mg/kg）"), tempWidget);
    QLineEdit *stmrText = new QLineEdit(tempWidget);
    stmrText->setValidator(pDoubleValidator);
    stmrText->setPlaceholderText(QString::number(0));
    stmrText->setObjectName("stmr");
    QLabel *stmrpLabel = new QLabel(QStringLiteral("加工因子矫正的中值（mg/kg）"), tempWidget);
    QLineEdit *stmrpText = new QLineEdit(tempWidget);
    stmrpText->setValidator(pDoubleValidator);
    stmrpText->setPlaceholderText(QString::number(0));
    stmrpText->setObjectName("stmrp");
    QLabel *hrLabel = new QLabel(QStringLiteral("最大残留量(mg/kg)"), tempWidget);
    QLineEdit *hrText = new QLineEdit(tempWidget);
    hrText->setValidator(pDoubleValidator);
    hrText->setPlaceholderText(QString::number(0));
    hrText->setObjectName("hr");
//    hrText->setPlaceholderText(QString::fromLocal8Bit("略"));
    QLabel *mrlLabel = new QLabel(QStringLiteral("荐残留值量（mg/kg）"), tempWidget);
    QLineEdit *mrlText = new QLineEdit(tempWidget);
    mrlText->setValidator(pDoubleValidator);
    mrlText->setPlaceholderText(QString::number(0));
    mrlText->setObjectName("mrl");
    QGridLayout *tempLayout = new QGridLayout();
//    residueLayout = new QGridLayout();
    tempLayout->addWidget(residue, 0, 0, 7, 1);
    tempLayout->addWidget(foodLabel, 0, 1);
    tempLayout->addWidget(foodText, 0, 2);
//    tempLayout->addWidget(intakeLabel, 1, 1);
//    tempLayout->addWidget(intakeLabel, 1, 2);
    tempLayout->addWidget(stmrLabel, 1, 1);
    tempLayout->addWidget(stmrText, 1, 2);
    tempLayout->addWidget(stmrpLabel, 2, 1);
    tempLayout->addWidget(stmrpText, 2, 2);
    tempLayout->addWidget(hrLabel, 3, 1);
    tempLayout->addWidget(hrText, 3, 2);
    tempLayout->addWidget(mrlLabel, 4, 1);
    tempLayout->addWidget(mrlText, 4, 2);

    tempLayout->setColumnStretch(0, 1);
    tempLayout->setColumnStretch(1, 1);
    tempLayout->setColumnStretch(2, 3);
    // 膳食暴露及人群信息
//    QLabel *diet = new QLabel(QStringLiteral("膳食暴露及人群信息"), tempWidget);
    QLabel *fiLabel = new QLabel(QStringLiteral("平均膳食量（g）"), tempWidget);
    QLineEdit *fiText = new QLineEdit(tempWidget);
    fiText->setValidator(pDoubleValidator);
    fiText->setPlaceholderText(QString::number(0));
    fiText->setObjectName("fi");
    QLabel *lp = new QLabel(QStringLiteral("最大膳食量（g）"), tempWidget);
    QLineEdit *lpText = new QLineEdit(tempWidget);
    lpText->setValidator(pDoubleValidator);
    lpText->setPlaceholderText(QString::number(0));
    lpText->setObjectName("lp");
    QLabel *u = new QLabel(QStringLiteral("单个农产品重量（g）"), tempWidget);
    QLineEdit *uText = new QLineEdit(tempWidget);
    uText->setValidator(pDoubleValidator);
    uText->setPlaceholderText(QString::number(0));
    uText->setObjectName("u");
    QLabel *e = new QLabel(QStringLiteral("单个农产品可食部分重量（g）"), tempWidget);
    QLineEdit *eText = new QLineEdit(tempWidget);
    eText->setValidator(pDoubleValidator);
    eText->setPlaceholderText(QString::number(0));
    eText->setObjectName("e");
    QLabel *v = new QLabel(QStringLiteral("差异因子"), tempWidget);
    QLineEdit *vText = new QLineEdit(tempWidget);
    vText->setValidator(pDoubleValidator);
    vText->setPlaceholderText(QString::number(0));
    vText->setObjectName("v");
    QLabel *bw = new QLabel(QStringLiteral("体重（kg）"), tempWidget);
    QLineEdit *bwText = new QLineEdit(tempWidget);
    bwText->setValidator(pDoubleValidator);
    bwText->setPlaceholderText(QString::number(0));
    bwText->setObjectName("bw");

//    tempLayout->addWidget(diet, 0, 0, 4);
    tempLayout->addWidget(fiLabel, 5, 1);
    tempLayout->addWidget(fiText, 5, 2);
    tempLayout->addWidget(lp, 6, 1);
    tempLayout->addWidget(lpText, 6, 2);
    tempLayout->addWidget(u, 7, 1);
    tempLayout->addWidget(uText, 7, 2);
    tempLayout->addWidget(e, 8, 1);
    tempLayout->addWidget(eText, 8, 2);
    tempLayout->addWidget(v, 9, 1);
    tempLayout->addWidget(vText, 9, 2);
    tempLayout->addWidget(bw, 10, 1);
    tempLayout->addWidget(bwText, 10, 2);
    addResidueButton = new QPushButton(QString("添加其他"), tempWidget);
    QObject::connect(addResidueButton, &QPushButton::clicked, this, &AssessDataInsertion::addResidueText);
    tempLayout->addWidget(addResidueButton, 10, 0);
    tempWidget->setLayout(tempLayout);
    dietLayout = new QVBoxLayout();

    dietLayout->addWidget(tempWidget);
    diet->setLayout(dietLayout);

    // 预览，添加，修改按钮
    saveButton = new QPushButton(QStringLiteral("保存"), this);
    cancelButton= new QPushButton(QStringLiteral("取消"), this);
    buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    /*布局*/
    mainLayout = new QVBoxLayout();
    // 农药成分
    mainLayout->addLayout(pesticideLayout);
    // 作用对象
    mainLayout->addLayout(toxicityLayout);
//    mainLayout->addStretch();
    //地点
//    mainLayout->addLayout(dietLayout);
    mainLayout->addWidget(diet);

    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
//    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    QObject::connect(saveButton, &QPushButton::clicked, this, &AssessDataInsertion::save);
    QObject::connect(cancelButton, &QPushButton::clicked, this, &AssessDataInsertion::cancel);

    preset();
    // 在当前路径下生成MRL文件夹
    QDir dir(QDir::currentPath());
    if(!dir.mkdir(QString("MRL")))
        qDebug() << "the directory already exists or something wrong!";
//    this->xlsFilePath = QString("%1/%2/%3.xls").arg(QDir::currentPath()).arg("MRL").arg("AssessTemplate");
//    generateExcelTemplate(xlsFilePath);
    QWidget *client = new QWidget();
    client->setLayout(mainLayout);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(client);
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(scrollArea);
}

void AssessDataInsertion::addResidueText()
{
//    int rowCount = this->objectLayout->rowCount();
    /*
    QLineEdit *additivePartText = new QLineEdit(this);
    this->additivePartList<<additivePartText;
    this->objectLayout->addWidget(additivePartText, rowCount, 2);
    */
    QWidget *tempWidget = new QWidget(diet);
    QPushButton *deleteButton = new QPushButton("删除此行", tempWidget);
    //残留水平
//    QLabel *residue = new QLabel(QStringLiteral("残留水平(mg/kg)"), tempWidget);
    QLabel *foodLabel = new QLabel(QStringLiteral("食物种类"), tempWidget);
    QLineEdit *foodText = new QLineEdit(tempWidget);
    foodText->setObjectName("food");
    QLabel *stmrLabel = new QLabel(QStringLiteral("残留量中值（mg/kg）"), tempWidget);
    QLineEdit *stmrText = new QLineEdit(tempWidget);
    stmrText->setObjectName("stmr");
    QDoubleValidator *pDoubleValidator = new QDoubleValidator(tempWidget);
    stmrText->setValidator(pDoubleValidator);
    stmrText->setPlaceholderText(QString::number(0));
    QLabel *stmrpLabel = new QLabel(QStringLiteral("加工因子矫正的中值（mg/kg）"), tempWidget);
    QLineEdit *stmrpText = new QLineEdit(tempWidget);
    stmrpText->setObjectName("stmrp");
    stmrpText->setValidator(pDoubleValidator);
    stmrpText->setPlaceholderText(QString::number(0));
    QLabel *hrLabel = new QLabel(QStringLiteral("最大残留量(mg/kg)"), tempWidget);
    QLineEdit *hrText = new QLineEdit(tempWidget);
    hrText->setObjectName("hr");
    hrText->setValidator(pDoubleValidator);
    hrText->setPlaceholderText(QString::number(0));
//    hrText->setPlaceholderText(QString::fromLocal8Bit("略"));
    QLabel *mrlLabel = new QLabel(QStringLiteral("荐残留值量（mg/kg）"), tempWidget);
    QLineEdit *mrlText = new QLineEdit(tempWidget);
    mrlText->setObjectName("mrl");
    mrlText->setValidator(pDoubleValidator);
    mrlText->setPlaceholderText(QString::number(0));
    QLabel *fiLabel = new QLabel(QStringLiteral("平均膳食量（g）"), tempWidget);
    QLineEdit *fiText = new QLineEdit(tempWidget);
    fiText->setObjectName("fi");
    fiText->setValidator(pDoubleValidator);
    fiText->setPlaceholderText(QString::number(0));
    QLabel *lp = new QLabel(QStringLiteral("最大膳食量（g）"), tempWidget);
    QLineEdit *lpText = new QLineEdit(tempWidget);
    lpText->setObjectName("lp");
    lpText->setValidator(pDoubleValidator);
    lpText->setPlaceholderText(QString::number(0));
    QLabel *u = new QLabel(QStringLiteral("单个农产品重量（g）"), tempWidget);
    QLineEdit *uText = new QLineEdit(tempWidget);
    uText->setObjectName("u");
    uText->setValidator(pDoubleValidator);
    uText->setPlaceholderText(QString::number(0));
    QLabel *e = new QLabel(QStringLiteral("单个农产品可食部分重量（g）"), tempWidget);
    QLineEdit *eText = new QLineEdit(tempWidget);
    eText->setValidator(pDoubleValidator);
    eText->setPlaceholderText(QString::number(0));
    eText->setObjectName("e");
    QLabel *v = new QLabel(QStringLiteral("差异因子"), tempWidget);
    QLineEdit *vText = new QLineEdit(tempWidget);
    vText->setObjectName("v");
    vText->setValidator(pDoubleValidator);
    vText->setPlaceholderText(QString::number(0));
    QLabel *bw = new QLabel(QStringLiteral("体重（kg）"), tempWidget);
    QLineEdit *bwText = new QLineEdit(tempWidget);
    bwText->setObjectName("bw");
    bwText->setValidator(pDoubleValidator);
    bwText->setPlaceholderText(QString::number(0));
//    deleteButton->parent()
    QObject::connect(deleteButton,
                     &QPushButton::clicked,
                     this,
                     &AssessDataInsertion::deleteResidueText);
    QGridLayout *tempLayout = new QGridLayout();
    tempLayout->addWidget(deleteButton, 0, 0, 10, 1);
    tempLayout->addWidget(foodLabel, 0, 1);
    tempLayout->addWidget(foodText, 0, 2);
    tempLayout->addWidget(stmrLabel, 1, 1);
    tempLayout->addWidget(stmrText, 1, 2);
    tempLayout->addWidget(stmrpLabel, 2, 1);
    tempLayout->addWidget(stmrpText, 2, 2);
    tempLayout->addWidget(hrLabel, 3, 1);
    tempLayout->addWidget(hrText, 3, 2);
    tempLayout->addWidget(mrlLabel, 4, 1);
    tempLayout->addWidget(mrlText, 4, 2);
    tempLayout->addWidget(fiLabel, 5, 1);
    tempLayout->addWidget(fiText, 5, 2);
    tempLayout->addWidget(lp, 6, 1);
    tempLayout->addWidget(lpText, 6, 2);
    tempLayout->addWidget(u, 7, 1);
    tempLayout->addWidget(uText, 7, 2);
    tempLayout->addWidget(e, 8, 1);
    tempLayout->addWidget(eText, 8, 2);
    tempLayout->addWidget(v, 9, 1);
    tempLayout->addWidget(vText, 9, 2);
    tempLayout->addWidget(bw, 10, 1);
    tempLayout->addWidget(bwText, 10, 2);
    tempLayout->setColumnStretch(0, 1);
    tempLayout->setColumnStretch(1, 1);
    tempLayout->setColumnStretch(2, 3);

    tempWidget->setObjectName("Residue");
    tempWidget->setLayout(tempLayout);
    this->dietLayout->addWidget(tempWidget);

//    this->dietLayout->addLayout(tempLayout);
}

void AssessDataInsertion::deleteResidueText()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    if(pButton)
    {
        QWidget* tempWidget = (pButton->parentWidget());
//        qDebug() << pButton->text();
//        qDebug()<< tempWidget->objectName();
        this->dietLayout->removeWidget(tempWidget);
        delete tempWidget;
    }
}

bool AssessDataInsertion::checkValidation()
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
    if(this->adiText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("每日允许摄入量"));
        return false;
    }
    if(this->arfdText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("急性参考剂量"));
        return false;
    }


    QList<QWidget*> dietList =  this->diet->findChildren<QWidget*>("Residue", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, dietList)
    {
        if(temp->findChild<QLineEdit*>("food", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中食物种类为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("hr", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中最大残留量为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("stmr", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中残留量中值为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("stmrp", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中加工因子矫正的中值为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("mrl", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中推荐残留量为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("fi", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中平均膳食量为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("lp", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中最大膳食量为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("u", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中单个农产品重量为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("e", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中单个农产品可食部分重量为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("v", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中差异因子为空"));
            return false;
        }
        if(temp->findChild<QLineEdit*>("bw", Qt::FindDirectChildrenOnly)->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QString("膳食和人群信息中体重为空"));
            return false;
        }
    }

    /*
    if(this->stmrText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("中值(STMR)"));
        return false;
    }
//    if(this->stmrpText->text().isEmpty())
//    {
//        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("加工因子矫正的中值（STMR-P）"));
//        return false;
//    }
    if(this->hrText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("最大值(HR)"));
        return false;
    }
    if(this->mrlText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("推荐残留值（MRL）"));
        return false;
    }
    if(this->fiText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("平均消费量（Fi）"));
        return false;
    }
    if(this->lpText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("最大消费量（LP）"));
        return false;
    }
    if(this->uText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("农产品单个重量（U）"));
        return false;
    }
    if(this->vText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("差异因子（V）"));
        return false;
    }
    if(this->bwText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("体重（BW）"));
        return false;
    }
    */
    return true;
}

void AssessDataInsertion::preset()
{
    this->chineseNameText->setText("硫双威");
    this->englishNameText->setText("thiodicarb");
    this->chemicalNameText->setText("3,7,9,13-四甲基-5,11-二氧杂-2,8,14-三硫杂-4,7,9,12-四氮杂十五烷-3,12-二烯-6,10-二酮");
    this->molecularText->setText("354.5");

    this->adiText->setText("0.03");
    this->arfdText->setText("0.02");
    QList<QWidget*> widgets = this->diet->findChildren<QWidget*>("Residue", Qt::FindDirectChildrenOnly);
//    qDebug() <<"widgets size = " <<widgets.size();
    for(int i=0; i<widgets.size(); i++)
    {
        QWidget* w = widgets.takeAt(i);
        w->findChild<QLineEdit*>("food")->setText("结球生菜");
        w->findChild<QLineEdit*>("hr")->setText("0.1");
        w->findChild<QLineEdit*>("stmr")->setText("0.08");
        w->findChild<QLineEdit*>("stmrp")->setText("0.08");
        w->findChild<QLineEdit*>("mrl")->setText("0.08");
        w->findChild<QLineEdit*>("fi")->setText("0.012");
        w->findChild<QLineEdit*>("lp")->setText("213");
        w->findChild<QLineEdit*>("v")->setText("3");
        w->findChild<QLineEdit*>("e")->setText("512");
        w->findChild<QLineEdit*>("u")->setText("539");
        w->findChild<QLineEdit*>("bw")->setText("65");
    }
}

/*
 * 未作改动，还是原来的模板
*/
void AssessDataInsertion::generateExcelTemplate(QString xlsFilePath)
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
    excel.setCellValue("A5", QStringLiteral("毒性评价"));
    excel.mergeCells("A5:A6");
    excel.setCellValue("B5", QStringLiteral("每日允许驶入量"));
    excel.setCellValue("B6", QStringLiteral("急性参考剂量"));
    excel.setCellValue("A7", QStringLiteral("残留水平"));
    excel.mergeCells("A7:A10");
    excel.setCellValue("B7", QStringLiteral("残留中值"));
    excel.setCellValue("B8", QStringLiteral("加工因子矫正的中值"));
    excel.setCellValue("B9", QStringLiteral("最大残留值"));
    excel.setCellValue("B10", QStringLiteral("推荐残留值"));

    excel.setCellValue("A11", QStringLiteral("膳食暴露及人群信息"));
    excel.mergeCells("A11:A15");
    excel.setCellValue("B11", QStringLiteral("平均消费量"));
    excel.setCellValue("B12", QStringLiteral("最大消费量"));
    excel.setCellValue("B13", QStringLiteral("单个农产品重量"));
    excel.setCellValue("B14", QStringLiteral("单个农产品可食部分重量"));
    excel.setCellValue("B15", QStringLiteral("差异因子"));
    excel.setCellValue("B16", QStringLiteral("体重"));

    excel.saveAs(xlsFilePath);
    excel.close();
}


void AssessDataInsertion::save()
{

    if(!this->checkValidation())
        return;
    AssessData *data = new AssessData();
    data->chineseName = QString::fromLocal8Bit(chineseNameText->text().trimmed().toUtf8());
    data->englishName = QString::fromLocal8Bit(englishNameText->text().trimmed().toUtf8());
    data->chemicalName = QString::fromLocal8Bit(chemicalNameText->text().trimmed().toUtf8());
    data->molecular = QString::fromLocal8Bit(molecularText->text().trimmed().toUtf8());
    data->adi = QString::fromLocal8Bit(adiText->text().trimmed().toUtf8()).toDouble();
    data->arfd = QString::fromLocal8Bit(arfdText->text().trimmed().toUtf8()).toDouble();
//    this->dietLayout->takeAt(0);
    QVector<FoodLimit*> result;
    QList<QWidget*> dietList =  this->diet->findChildren<QWidget*>("Residue", Qt::FindDirectChildrenOnly);
    foreach(QWidget* temp, dietList)
    {
        FoodLimit *foods = new FoodLimit();
        foods->food = temp->findChild<QLineEdit*>("food", Qt::FindDirectChildrenOnly)->text().trimmed();
        foods->hr = temp->findChild<QLineEdit*>("hr", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->stmr = temp->findChild<QLineEdit*>("stmr", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->stmrp = temp->findChild<QLineEdit*>("stmrp", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->mrl = temp->findChild<QLineEdit*>("mrl", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->Fi = temp->findChild<QLineEdit*>("fi", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->LPi = temp->findChild<QLineEdit*>("lp", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->Ui = temp->findChild<QLineEdit*>("u", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->Ei = temp->findChild<QLineEdit*>("e", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->CVi = temp->findChild<QLineEdit*>("v", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        foods->BWi = temp->findChild<QLineEdit*>("bw", Qt::FindDirectChildrenOnly)->text().trimmed().toDouble();
        result.push_back(foods);
    }
    data->foodInfo = result;
    this->xlsFilePath = QString("%1/%2/评估数据_%3.xls").arg(QDir::currentPath()).arg("MRL").arg(data->chineseName);
    saveToExcel(data, this->xlsFilePath);
    QMessageBox::warning(NULL, QStringLiteral("保存提醒"), QString("保存成功"));
}

void AssessDataInsertion::saveToExcel(AssessData* data, QString xlsFilePath)
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

    excel.setCellValue("A5", QStringLiteral("毒性评价"));
    excel.mergeCells("A5:A6");
    excel.setCellValue("B5", QStringLiteral("每日允许驶入量"));
    excel.setCellValue("B6", QStringLiteral("急性参考剂量"));
    excel.setCellValue("C5", (data->adi));
    excel.setCellValue("C6", (data->arfd));
    excel.setCellValue("B7", QStringLiteral("食物"));
    excel.setCellValue("A8", QStringLiteral("残留水平"));
    excel.mergeCells("A8:A11");
    excel.setCellValue("B8", QStringLiteral("残留中值"));
    excel.setCellValue("B9", QStringLiteral("加工因子矫正的中值"));
    excel.setCellValue("B10", QStringLiteral("最大残留值"));
    excel.setCellValue("B11", QStringLiteral("推荐残留值"));
    excel.setCellValue("A12", QStringLiteral("膳食暴露及人群信息"));
    excel.mergeCells("A12:A16");
    excel.setCellValue("B12", QStringLiteral("平均消费量"));
    excel.setCellValue("B13", QStringLiteral("最大消费量"));
    excel.setCellValue("B14", QStringLiteral("单个农产品重量"));
    excel.setCellValue("B15", QStringLiteral("单个农产品可食部分重量"));
    excel.setCellValue("B16", QStringLiteral("差异因子"));
    excel.setCellValue("B17", QStringLiteral("体重"));
    QVector<FoodLimit*> food = data->foodInfo;
    for(int i=0; i<food.size(); i++)
    {
        excel.setCellValue(7, 3+i, (food[i]->food));
        excel.setCellValue(8, 3+i, (food[i]->stmr));
        excel.setCellValue(9, 3+i, (food[i]->stmrp));
        excel.setCellValue(10, 3+i, (food[i]->hr));
        excel.setCellValue(11, 3+i, (food[i]->mrl));

        excel.setCellValue(12, 3+i, (food[i]->Fi));
        excel.setCellValue(13, 3+i, (food[i]->LPi));
        excel.setCellValue(14, 3+i, (food[i]->Ui));
        excel.setCellValue(15, 3+i, (food[i]->Ei));
        excel.setCellValue(16, 3+i, (food[i]->CVi));
        excel.setCellValue(17, 3+i, (food[i]->BWi));

    }

    excel.saveAs(xlsFilePath);
    excel.close();
}


void AssessDataInsertion::cancel()
{
//    testSaveToExcel();
}

