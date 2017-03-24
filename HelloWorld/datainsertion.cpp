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
    dosage = new QLabel(QStringLiteral("剂量"), this);
    dosageText = new QLineEdit(this);
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
    QLabel *phi = new QLabel(QStringLiteral("间隔期"), this);
    QLineEdit *phiText = new QLineEdit(this);
    QLabel *residue = new QLabel(QStringLiteral("残留量"), this);
    QTextEdit *residueText = new QTextEdit(this);
    phiList<<phiText;
    residueList<<residueText;
    addPhiButton = new QPushButton(QStringLiteral("添加PHI"), this);
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
    QLabel *phi2 = new QLabel(QStringLiteral("间隔期"), this);
    QLineEdit *phiText2 = new QLineEdit(this);
    QLabel *residue2 = new QLabel(QStringLiteral("残留量"), this);
    QTextEdit *residueText2 = new QTextEdit(this);
    this->phiList << phiText2;
    this->residueList << residueText2;
    this->residueLayout->addWidget(phi2, rowCount, 1);
    this->residueLayout->addWidget(phiText2, rowCount, 2);
    this->residueLayout->addWidget(residue2, rowCount, 3);
    this->residueLayout->addWidget(residueText2, rowCount, 4);
}

void DataInsertion::preview()
{

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

    if(this->chemicalNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("化学名称"));
        return;
    }
    if(this->chineseNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("中文名"));
        return;
    }
    if(this->englishNameText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("英文名"));
        return;
    }
    if(this->molecularText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("分子量"));
        return;
    }
    if(this->ediblePartText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("可食用部分"));
        return;
    }
    if(this->nonEdiblePartText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("不可食用部分"));
        return;
    }
    if(this->methodText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("施用方式"));
        return;
    }
    if(this->frequencyText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("频率"));
        return;
    }
    if(this->dosageText->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("剂量"));
        return;
    }
//    if(this->locationText->text().isEmpty())
//    {
//        QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("地点"));
//        return;
//    }
    foreach (QLineEdit* l, this->phiList)
    {
        if(l->text().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("phi不能为空"));
            return;
        }
    }

    foreach (QTextEdit* l, this->residueList)
    {
        if(l->toPlainText().isEmpty())
        {
            QMessageBox::critical(NULL, QString("Critical"), QStringLiteral("residue不能为空"));
            return;
        }
    }
    PesticideData *pesticide = new PesticideData();
    pesticide->chineseName = QString::fromLocal8Bit(chineseNameText->text().trimmed().toUtf8());
    pesticide->englishName = QString::fromLocal8Bit(englishNameText->text().trimmed().toUtf8());
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

    pesticide->method= QString::fromLocal8Bit(methodText->text().trimmed().toUtf8());
    pesticide->method= QString::fromLocal8Bit(methodText->text().trimmed().toUtf8());



}
void DataInsertion::cancel()
{

}
