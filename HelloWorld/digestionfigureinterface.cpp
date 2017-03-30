#include "digestionfigureinterface.h"

DigestionFigureInterface::DigestionFigureInterface(QWidget *parent)
    :FigureInterface(parent)
{
    tableLabel->setText("选择的实验时间和残留量浓度表格");
    selectButton->setText("生成代谢消解图");
    QObject::connect(selectButton, &QPushButton::clicked, this, &DigestionFigureInterface::selectButtonClicked);
//    FigureInterface::preset();
}

void DigestionFigureInterface::selectButtonClicked()
{
    if(this->pesticide == NULL)
    {
        QMessageBox::critical(NULL, QString("错误提示!"), QString("未有选择数据，回到数据定义选择残留量数据！"));
        return;
    }
    QString trendLineName = QString("Digestion_%1_%2_%3").arg(
                this->pesticide->chineseName).arg(
                this->pesticide->chemicalName).arg(
                this->key);

    QString picturePath = QString("%1/%2.jpg").arg(this->currentDir).arg(trendLineName);
    plot(picturePath);
    ImageViewer* imageViewer = new ImageViewer(this);
    imageViewer->loadFile(picturePath);
    imageViewer->show();
}

void DigestionFigureInterface::plot(QString &fileSavePath)
{

    if(this->pesticide == NULL)
    {
        QMessageBox::critical(NULL, QString("错误提示!"), QString("未有选择数据，回到数据定义选择残留量数据！"));
        return;
    }

    Excel * excel = new Excel();
    excel->residues = this->pesticide->residues[key];
    QString trendLineName = QString("Digestion_%1_%2_%3").arg(
                this->pesticide->chineseName).arg(
                this->pesticide->chemicalName).arg(
                this->key);
    excel->trendLinesName = trendLineName;

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
    excel->pictureSavePath = fileSavePath;
    excel->digestion = this->selectData;
    excel->makeMetabolicPlot();
    delete excel;
    qDebug() << "图标保存成功.";

}

void DigestionFigureInterface::receiveSelectedData(PesticideData *p, QMap<int,double> m, int index)
{
    this->pesticide = p;
    this->selectData = m;
    fillTableWidget();
}


void DigestionFigureInterface::fillTableWidget()
{
    QMap<int, double> map = this->selectData;
    // 必须设置行和列，否则setItem无法显示。
    this->tableWidget->setRowCount(1<<16);
    this->tableWidget->setColumnCount(map.size());
    QStringList header;

    QMap<int, double>::const_iterator i = this->selectData.constBegin();
    int col = 0;
    for(; i!= this->selectData.constEnd(); i++, col++)
    {
        header << QString::number(i.key());
        this->tableWidget->setItem(0, col, new QTableWidgetItem(QString::number(i.value())));
    }

    this->tableWidget->setHorizontalHeaderLabels(header);
}
