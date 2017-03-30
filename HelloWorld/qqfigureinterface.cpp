#include "qqfigureinterface.h"

QQFigureInterface::QQFigureInterface(QWidget *parent)
    :FigureInterface(parent)
{
    tableLabel->setText("间隔期和残留量（标题栏为间隔期，每一列为对应的残留量，请若修改请回来数据定义项。");
    selectButton->setText("生成QQ图");
    QObject::connect(selectButton, &QPushButton::clicked, this, &QQFigureInterface::selectButtonClicked);
}

void QQFigureInterface::selectButtonClicked()
{
    if(this->pesticide == NULL)
    {
        QMessageBox::critical(NULL, QString("错误提示!"), QString("未有选择数据，回到数据定义选择残留量数据！"));
        return;
    }
    QString trendLineName = QString("%1_%2_%3_%4").arg(
                this->pesticide->chineseName).arg(
                this->pesticide->chemicalName).arg(
                this->pesticide->dosage).arg(
                this->key);

    QString picturePath = QString("%1/%2.jpg").arg(this->currentDir).arg(trendLineName);
    plot(picturePath);
    ImageViewer* imageViewer = new ImageViewer(this);
    imageViewer->loadFile(picturePath);
    imageViewer->show();
}

void QQFigureInterface::plot(QString &fileSavePath)
{

    if(this->pesticide == NULL)
    {
        QMessageBox::critical(NULL, QString("错误提示!"), QString("未有选择数据，回到数据定义选择残留量数据！"));
        return;
    }

    Excel * excel = new Excel();
    excel->residues = this->pesticide->residues[key];
    QString trendLineName = QString("%1_%2_%3_%4").arg(
                this->pesticide->chineseName).arg(
                this->pesticide->chemicalName).arg(
                this->pesticide->dosage).arg(
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
    this->rSquared= excel->savePlot();
    delete excel;
    qDebug() << "图标保存成功，rSquaredValue = "<<this->rSquared;

}

void QQFigureInterface::receiveSelectedData(PesticideData *p, int key )
{
    if(!p->residues.keys().contains(key))
    {
        qDebug() << "key is ont in data";
        return;
    }
    this->pesticide = p;
    this->key = key;
    fillTableWidget();
}
