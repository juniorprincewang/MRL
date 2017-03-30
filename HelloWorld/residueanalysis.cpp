#include "residueanalysis.h"

ResidueAnalysis::ResidueAnalysis(QWidget *parent)
    :DataAnalysis(parent)
{
    // 分布，残留计算方法，推荐残留值
    QGridLayout *residuesLayout= new QGridLayout();
    QLabel *distribution= new QLabel(QString("分布"), this);
    distributionText = new QLineEdit(this);
    QLabel *calcMethod= new QLabel(QString("残留计算方法"), this);;
    calcMethodText = new QLineEdit(this);
    QLabel *recommendation = new QLabel(QString("推荐残留值"), this);;
    recommendationText =new QLineEdit(this);
    residuesLayout->addWidget(distribution, 0, 0);
    residuesLayout->addWidget(distributionText, 0, 1);
    residuesLayout->addWidget(calcMethod, 1, 0);
    residuesLayout->addWidget(calcMethodText, 1, 1);
    residuesLayout->addWidget(recommendation, 2, 0);
    residuesLayout->addWidget(recommendationText, 2, 1);
    distributionText->setEnabled(false);
    calcMethodText->setEnabled(false);
    recommendationText->setEnabled(false);
    //残留量
    mainLayout->addLayout(residuesLayout);
//    DataAnalysis::preset();
//    fillWidget();

}


void ResidueAnalysis::receiveSelectedData(PesticideData *p, int key)
{
    DataAnalysis::receiveSelectedData(p, key);
    qDebug()<< "Residue Analysis receiveSelectedData";
    fillWidget();
}

void ResidueAnalysis::fillWidget()
{
    DataAnalysis::fillWidget();
    if(isShapiroFranciaNormality())
        this->distributionText->setText(QString("对数正态分布"));
    else
        this->distributionText->setText(QString("非对数正态分布"));
    this->calcMethodText->setText("NDF");
    this->recommendationText->setText("31241");
}

void ResidueAnalysis::plot()
{
    if(this->pesticide == NULL)
    {
        QMessageBox::critical(NULL, QString("错误提示!"), QString("未有选择数据，回到数据定义选择残留量数据！"));
        return;
    }
    QString trendLineName = QString("%1_%2_%3").arg(
                this->pesticide->chineseName).arg(
                this->pesticide->chemicalName).arg(
                this->key);
    QString fileSavePath = QString("%1/%2.jpg").arg(this->currentDir).arg(trendLineName);


    QDir dir(fileSavePath);
    if(dir.exists())
    {
        QMessageBox box;
        box.setText(QStringLiteral("确定"));
        box.setInformativeText(QStringLiteral("文件已存在，是否覆盖?"));
        box.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel );
        int ret = box.exec();
        if(QMessageBox::Save != ret)
        {
            qDebug() << "未保存成功！";
            return;
        }
    }
    Excel * excel = new Excel();
    excel->residues = this->residues;
    excel->trendLinesName = trendLineName;

    excel->pictureSavePath = fileSavePath;
    this->rSquared = excel->savePlot();
    delete excel;
    qDebug() << "图标保存成功，rSquaredValue = "<<this->rSquared;
}

bool ResidueAnalysis::isShapiroFranciaNormality()
{
    //生成QQ图
    plot();
    // 对数验证
    Model model(this->residues.toStdVector());

    int normality = model.ShapiroFranciaNormalityTest(this->rSquared);
    if(normality == 3)
        return true;
    return false;
}


