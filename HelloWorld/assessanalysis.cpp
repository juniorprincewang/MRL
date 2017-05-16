#include "assessanalysis.h"

AssessAnalysis::AssessAnalysis(QWidget *parent)
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
    pesticideLayout->addWidget(pesticide, 0, 0, 4, 1);
    pesticideLayout->addWidget(molecular, 0, 1);
    pesticideLayout->addWidget(molecularText, 0, 2);
    pesticideLayout->addWidget(chineseName, 1, 1);
    pesticideLayout->addWidget(chineseNameText, 1, 2);
    pesticideLayout->addWidget(englishName, 2, 1);
    pesticideLayout->addWidget(englishNameText, 2, 2);
    pesticideLayout->addWidget(chemicalName, 3, 1);
    pesticideLayout->addWidget(chemicalNameText, 3, 2);
    pesticideLayout->setColumnStretch(0, 1);
    pesticideLayout->setColumnStretch(1, 1);
    pesticideLayout->setColumnStretch(2, 3);
    chineseNameText->setEnabled(false);
    englishNameText->setEnabled(false);
    chemicalNameText->setEnabled(false);
    molecularText->setEnabled(false);
    /*布局*/
    mainLayout = new QVBoxLayout();
    // 农药成分
    mainLayout->addLayout(pesticideLayout);
    // 设置滚动轴
    QWidget *client = new QWidget();
    client->setLayout(mainLayout);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(client);
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(scrollArea);

    // 当前路径下的MRL文件夹
    this->currentDir = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
}


/*
 * ******************************************************************
 * Acute Assess Analysis
 * ******************************************************************
 *
 */
AcuteAssessAnalysis::AcuteAssessAnalysis(QWidget *parent)
    :AssessAnalysis(parent)
{
    QLabel *assessTypeLabel = new QLabel(QString("评估类型"), this);
    assessTypeText = new QLineEdit(this);
    assessTypeText->setText("急性评估");
    QLabel *mrlLabel = new QLabel(QString("推荐最大残留限量"), this);
    mrlText = new QLineEdit(this);
    QLabel *NESTILabel = new QLabel(QString("国家估计短期摄入量（NESTI）"), this);
    NESTIText = new QLineEdit(this);
    QLabel *riskProbabilityLabel = new QLabel(QString("风险评估"), this);
    riskProbabilityText = new QLineEdit(this);
    QGridLayout *analysisLayout = new QGridLayout();
    analysisLayout->setMargin(10);
    analysisLayout->setSpacing(10);
    analysisLayout->addWidget(assessTypeLabel, 0, 0);
    analysisLayout->addWidget(assessTypeText, 0, 1, 1, 2);
    analysisLayout->addWidget(mrlLabel, 1, 0);
    analysisLayout->addWidget(mrlText, 1, 1, 1, 2);
    analysisLayout->addWidget(NESTILabel, 2, 0);
    analysisLayout->addWidget(NESTIText, 2, 1, 1, 2);
    analysisLayout->addWidget(riskProbabilityLabel, 3, 0);
    analysisLayout->addWidget(riskProbabilityText, 3, 1, 1, 2);
    analysisLayout->setColumnStretch(0, 1);
    analysisLayout->setColumnStretch(1, 1);
    analysisLayout->setColumnStretch(2, 3);
    assessTypeText->setEnabled(false);
    mrlText->setEnabled(false);
    NESTIText->setEnabled(false);
    riskProbabilityText->setEnabled(false);
    mainLayout->addLayout(analysisLayout);
    mainLayout->addStretch();
}
/*
void AcuteAssessAnalysis::getNESTI()
{
    //情形1,混合样本残留数据能够反映该产品在一顿饭消耗的残留水平
    double NESTI1 = (data->lp*data->hr)/data->bw;
    // 情形2
    // 情形2a, 单个未加工食品的可食部分重量小于个体每顿饭对该食品的最大消耗量。
    double NESTI2a = (data->u*data->hr*data->v + (data->lp - data->u)*data->hr)/data->bw;
    // 情形2b, 个未加工食品的可食部分重量超过个体每顿饭对该食品的最大消耗量。
    double NESTI2b = data->lp*data->hr*data->v/data->bw;
    // 情形3, 散装或多种混合的加工的食品，STMR-P 代表可能最高残留浓度。
    double NESTI3 = data->lp * data->stmrp/data->bw;

}
*/
void AcuteAssessAnalysis::receiveSelectedData(AssessData *data, QVector<double> result)
{
//    QString sumValue
//    QString dailyValue
//    QString percentileValue
    this->NESTIText->setText(QString::number(result.at(0)));
    this->riskProbabilityText->setText(QString::number(result.at(2)));
    this->chemicalNameText->setText(data->chemicalName);
    this->chineseNameText->setText(data->chineseName);
    this->englishNameText->setText(data->englishName);
    this->molecularText->setText(data->molecular);

}


/*
 * ******************************************************************
 * Chronic Assess Analysis
 * ******************************************************************
 *
 */
ChronicAssessAnalysis::ChronicAssessAnalysis(QWidget *parent)
    :AssessAnalysis(parent)
{
    QLabel *assessTypeLabel = new QLabel(QString("评估类型"), this);
    assessTypeText = new QLineEdit(this);
    assessTypeText->setText("慢性评估");
    QLabel *mrlLabel = new QLabel(QString("推荐最大残留限量"), this);
    mrlText = new QLineEdit(this);
    QLabel *NEDILabel = new QLabel(QString("国家估算每日摄入量（NEDI）"), this);
    NEDIText = new QLineEdit(this);
    QLabel *riskProbabilityLabel = new QLabel(QString("风险评估"), this);
    riskProbabilityText = new QLineEdit(this);
    QGridLayout *analysisLayout = new QGridLayout();
    analysisLayout->setMargin(10);
    analysisLayout->setSpacing(10);
    analysisLayout->addWidget(assessTypeLabel, 0, 0);
    analysisLayout->addWidget(assessTypeText, 0, 1, 1, 2);
    analysisLayout->addWidget(mrlLabel, 1, 0);
    analysisLayout->addWidget(mrlText, 1, 1, 1, 2);
    analysisLayout->addWidget(NEDILabel, 2, 0);
    analysisLayout->addWidget(NEDIText, 2, 1, 1, 2);
    analysisLayout->addWidget(riskProbabilityLabel, 3, 0);
    analysisLayout->addWidget(riskProbabilityText, 3, 1, 1, 2);
    analysisLayout->setColumnStretch(0, 1);
    analysisLayout->setColumnStretch(1, 1);
    analysisLayout->setColumnStretch(2, 3);
    assessTypeText->setEnabled(false);
    mrlText->setEnabled(false);
    NEDIText->setEnabled(false);
    riskProbabilityText->setEnabled(false);
    mainLayout->addLayout(analysisLayout);
    mainLayout->addStretch();
}

void ChronicAssessAnalysis::receiveSelectedData(AssessData *data, QVector<double> result)
{
//    this->NEDIText->setText(QString::number(result.at(0)));
//    this->riskProbabilityText->setText(QString::number(result.at(2)));
//    this->chemicalNameText->setText(data->chemicalName);
//    this->chineseNameText->setText(data->chineseName);
//    this->englishNameText->setText(data->englishName);
//    this->molecularText->setText(data->molecular);
}
