#ifndef DATAINSERTION_H
#define DATAINSERTION_H
/*
 * 数据新建Panel
 */
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QVector>
#include <QMap>
#include <QMessageBox>
#include <QList>

struct PesticideData
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

};


class DataInsertion: public QWidget
{
    Q_OBJECT
public:
    DataInsertion(QWidget *parent = 0);
private:
    // 农药成分
//    QFormLayout *pesticideLayout;
    QGridLayout *pesticideLayout;
    QLabel *pesticide;
    QLabel *chineseName;
    QLineEdit *chineseNameText;
    QLabel *englishName;
    QLineEdit *englishNameText;
    QLabel *chemicalName;
    QLineEdit *chemicalNameText;
    QLabel *molecular;
    QLineEdit *molecularText;
    // 作用对象
    QGridLayout *objectLayout;
    QLabel *object;
    QLabel *ediblePart;
    QLineEdit *ediblePartText;
    QLabel *nonEdiblePart;
    QLineEdit *nonEdiblePartText;
    QLabel *additivePart;
    QPushButton *additivePartButton;
    QList<QLineEdit*>additivePartList;
    // 实验方式
    QGridLayout *methodLayout;
    QLabel *operationMethod;
    QLabel *method;
    QLineEdit *methodText;
    QLabel *frequency;
    QLineEdit *frequencyText;
    QLabel *dosage;
    QLineEdit *dosageText;
    // 作用地点
    QGridLayout *locationLayout;
    QLabel *location;
    QPushButton *locationButton;
    QList<QLineEdit *> locationList;
    // 残留水平
    QGridLayout *residueLayout;
    QLabel *residueLevel;
//    QLabel *phi;
//    QLineEdit *phiText;
//    QLabel *residue;
//    QTextEdit *residueText;
    QList<QLineEdit*> phiList;
    QList<QTextEdit*> residueList;
    QPushButton *addPhiButton;
    // 按钮
    QHBoxLayout *buttonLayout;
    QPushButton *previewButton;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    // 整体布局
    QVBoxLayout *mainLayout;
public slots:
    void addAdditivePart();
    void addLocationText();
    void addPhi();
    void preview();
    void save();
    void cancel();
};


#endif // DATAINSERTION_H
