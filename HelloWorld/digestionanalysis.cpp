#include "digestionanalysis.h"

DigestionAnalysis::DigestionAnalysis(QWidget *parent)
    :DataAnalysis(parent)
{
    // 方程式、残留量取值计算、半衰期
    QGridLayout *residuesLayout= new QGridLayout();
    QLabel *equation= new QLabel(QString("方程式"), this);
    equationText = new QLineEdit(this);
    QLabel *residue= new QLabel(QString("残留量取值"), this);;
    residueText = new QLineEdit(this);
    QLabel *halflife = new QLabel(QString("半衰期"), this);;
    halflifeText =new QLineEdit(this);
    residuesLayout->addWidget(equation, 0, 0);
    residuesLayout->addWidget(equationText, 0, 1);
    residuesLayout->addWidget(residue, 1, 0);
    residuesLayout->addWidget(residueText, 1, 1);
    residuesLayout->addWidget(halflife, 2, 0);
    residuesLayout->addWidget(halflifeText, 2, 1);
    equationText->setEnabled(false);
    residueText->setEnabled(false);
    halflifeText->setEnabled(false);
    //残留量
    mainLayout->addLayout(residuesLayout);
//    DataAnalysis::preset();
//    plot();
//    fillWidget();
}


void DigestionAnalysis::receiveSelectedData(PesticideData *p, QMap<int, double> m, int radioIndex)
{
//    DataAnalysis::receiveSelectedData(p, key);
    this->pesticide = p;
    this->selectedData = m;
    this->radioIndex = radioIndex;
    fillWidget();
}

void DigestionAnalysis::fillWidget()
{
    DataAnalysis::fillWidget();
    plot();
    if(formulaString.size() != 2)
    {
        qDebug() << "formulaString size != 2";
        return ;
    }
    // 处理公式，提取变量K和RSQuare
    QString KString = formulaString[0].split('e').last().split('x').first();
    QString rSquaredString = formulaString[1].split('=').last();
    double rSquaredValue = rSquaredString.trimmed().toDouble();
    double K = KString.trimmed().toDouble();
    qDebug() << "rSquared = " << rSquaredValue << " and K = " << K;
    double halflifeValue;
    if(rSquaredValue >= 0.75)
        halflifeValue = ln(2)/(-K);
    else
        // 暂时先不计算
        halflifeValue = 0.0;
    this->equationText->setText(formulaString[0]);
    if(radioIndex == 0)
        this->residueText->setText("中值");
    else if(radioIndex == 1)
        this->residueText->setText("均值");
    else if(radioIndex == 2)
        this->residueText->setText("众数");
    this->halflifeText->setText(QString::number(halflifeValue));

}

void DigestionAnalysis::plot()
{
    if(this->pesticide == NULL)
    {
        QMessageBox::critical(NULL, QString("错误提示!"), QString("未有选择数据，回到数据定义选择残留量数据！"));
        return;
    }
    QString trendLineName = QString("Digestion_%1_%2").arg(
                this->pesticide->chineseName).arg(
                this->pesticide->chemicalName);
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
    excel->digestion = this->selectedData;
    excel->pictureSavePath = fileSavePath;
    formulaString = excel->makeMetabolicPlot();
    delete excel;
    qDebug() << "图标保存成功.";
}

