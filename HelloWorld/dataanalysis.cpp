#include "dataanalysis.h"

DataAnalysis::DataAnalysis(QWidget *parent)
    :QWidget(parent)
{
    // 农药成分

    QLabel *pesticide = new QLabel(QStringLiteral("农药成分"), this);
    QLabel *chineseName = new QLabel(QStringLiteral("中文名"), this);
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

    QGridLayout *pesticideLayout = new QGridLayout();
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
    chineseNameText->setEnabled(false);
    englishNameText->setEnabled(false);
    chemicalNameText->setEnabled(false);
    molecularText->setEnabled(false);

    // 作用对象
    QLabel *object = new QLabel(QStringLiteral("作用对象"), this);
    QLabel *ediblePart = new QLabel(QStringLiteral("可食用部分"), this);
    ediblePartText = new QLineEdit(this);
    QLabel *nonEdiblePart = new QLabel(QStringLiteral("不可食用部分"), this);
    nonEdiblePartText = new QLineEdit(this);
    QLabel *additivePart = new QLabel(QString("其他（根据用户自行添加，该项目包括土壤、田水等）"), this);
    additivePartText = new QLineEdit(this);
    QGridLayout *objectLayout = new QGridLayout();
    objectLayout->setMargin(10);
    objectLayout->setSpacing(10);
    objectLayout->addWidget(object, 0, 0);
    objectLayout->addWidget(ediblePart, 1, 1);
    objectLayout->addWidget(ediblePartText, 1, 2);
    objectLayout->addWidget(nonEdiblePart, 2, 1);
    objectLayout->addWidget(nonEdiblePartText, 2, 2);
    objectLayout->addWidget(additivePart, 3, 1);
    objectLayout->addWidget(additivePartText, 3, 2);
    objectLayout->setColumnStretch(0, 1);
    objectLayout->setColumnStretch(1, 1);
    objectLayout->setColumnStretch(2, 3);
    ediblePartText->setEnabled(false);
    nonEdiblePartText->setEnabled(false);
    additivePartText->setEnabled(false);

    //实验方法
    QLabel *operationMethod= new QLabel(QStringLiteral("实验方式及方式"), this);
    QLabel *method= new QLabel(QStringLiteral("施用方式"), this);
    methodText = new QLineEdit(this);
    QLabel *frequency= new QLabel(QStringLiteral("频率"), this);
    frequencyText = new QLineEdit(this);
    frequencyText->setPlaceholderText(QString::fromLocal8Bit("略"));
    QLabel *dosage= new QLabel(QStringLiteral("剂量"), this);
    dosageText = new QLineEdit(this);
    dosageText->setPlaceholderText(QString::fromLocal8Bit("略"));
    QLabel *location= new QLabel(QString("地点"), this);
    locationText = new QLineEdit(this);
    QGridLayout *methodLayout= new QGridLayout();
    methodLayout->addWidget(operationMethod, 0, 0);
    methodLayout->addWidget(method, 1, 1);
    methodLayout->addWidget(methodText, 1, 2);
    methodLayout->addWidget(frequency, 2, 1);
    methodLayout->addWidget(frequencyText, 2, 2);
    methodLayout->addWidget(dosage, 3, 1);
    methodLayout->addWidget(dosageText, 3, 2);
    methodLayout->addWidget(location, 4, 1);
    methodLayout->addWidget(locationText, 4, 2);
    methodLayout->setColumnStretch(0, 1);
    methodLayout->setColumnStretch(1, 1);
    methodLayout->setColumnStretch(2, 3);
    methodText->setEnabled(false);
    frequencyText->setEnabled(false);
    dosageText->setEnabled(false);
    locationText->setEnabled(false);
    /*布局*/
    mainLayout = new QVBoxLayout(this);
    // 农药成分
    mainLayout->addLayout(pesticideLayout);
    // 作用对象
    mainLayout->addLayout(objectLayout);
//    mainLayout->addStretch();
    //方法
    mainLayout->addLayout(methodLayout);

    // 初始化其他变量
    pesticide = NULL;
    key = 0;
    rSquared = 0;
    // 当前路径下的MRL文件夹
    this->currentDir = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
}

void DataAnalysis::receiveSelectedData(PesticideData *p, int key)
{
    if(!p->residues.keys().contains(key))
    {
        qDebug() << "key is ont in data";
        return;
    }
    this->pesticide = p;
    this->key = key;
    this->residues = p->residues[key];
//    fillWidget();
}

void DataAnalysis::fillWidget()
{
    PesticideData *d = this->pesticide;
    this->chineseNameText->setText(d->chineseName);
    this->englishNameText->setText(d->englishName);
    this->chemicalNameText->setText(d->chemicalName);
    this->molecularText->setText(d->molecular);

    this->ediblePartText->setText(d->edible);
    this->nonEdiblePartText->setText(d->nonedible);
    QString string;
    foreach(QString s , d->additive)
        string+=s + ";";
    this->additivePartText->setText(string);
    this->methodText->setText(d->method);
    this->frequencyText->setText(d->frequency);
    this->dosageText->setText(d->dosage);
    string.clear();
    foreach(QString s , d->location)
        string += s + ";";
    this->locationText->setText(string);
}

void DataAnalysis::preset()
{
    pesticide = new PesticideData;
    pesticide->chineseName = QString("甲氨基阿维菌素苯甲酸盐");
    pesticide->englishName = QString("Emamectin Benzoate");
    pesticide->chemicalName = QString("4'-表-甲胺基-4'-脱氧阿维菌素苯甲酸盐");
    pesticide->molecular = "1008.24";
    pesticide->dosage = "略略";
    pesticide->edible = "稻谷";
    pesticide->nonedible = "水稻秸秆";
    pesticide->method= "喷施";

    QMap<int, QVector<double>> m;
    std::vector<double> e = {0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.070, 0.120, 0.190, 0.220, 0.230, 0.260, 0.270, 0.280, 0.330, 0.490, 1.100, 1.200, 1.300, 1.400, 1.600, 1.600,1.600};

    m[5] = QVector<double>::fromStdVector(e);
    pesticide->residues = m;

    key = 5;
    residues = QVector<double>::fromStdVector(e);

}
