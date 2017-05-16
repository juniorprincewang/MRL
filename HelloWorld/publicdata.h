#ifndef PUBLICDATA_H
#define PUBLICDATA_H
#include <QVector>
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

typedef struct food_data
{
    QString food;
//    double intake;
    // source 来源与以下四个数据。
    double stmr;
    double stmrp;
    double hr;
    double mrl;
//    QVector<double> source;
    double Fi;  //平均摄入量
    double LPi; // 最大摄入量
    double Ui; // 单个重量
    double Ei;  // 单个可食部分重量
    double CVi ;//差异因子
    double BWi; //体重
//    int choice = 0;
} FoodLimit;

typedef struct assess_data
{
    QString chineseName;
    QString englishName;
    QString chemicalName;
    QString molecular;
    QVector<FoodLimit*> foodInfo;
    double adi;     //每日允许摄入量
    double arfd;    //急性参考剂量
} AssessData;


/*
// 在当前路径下生成MRL文件夹
QDir dir(QDir::currentPath());
if(!dir.mkdir(QString("MRL")))
    qDebug() << "the directory already exists or something wrong!";
QString currentDir = ;

*/
#endif // PUBLICDATA_H
