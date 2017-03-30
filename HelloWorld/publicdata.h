#ifndef PUBLICDATA_H
#define PUBLICDATA_H

typedef struct pesticide_data
{
    QString chineseName;
    QString englishName;
    QString chemicalName;
    QString molecular;
    QString edible;
    QString nonedible;
    QVector<QString > additive;
    QString method;
    QString frequency;
    QString dosage;
    QVector<QString> location;
    QMap<int, QVector<double>> residues;

} PesticideData;

/*
// 在当前路径下生成MRL文件夹
QDir dir(QDir::currentPath());
if(!dir.mkdir(QString("MRL")))
    qDebug() << "the directory already exists or something wrong!";
QString currentDir = ;

*/
#endif // PUBLICDATA_H
