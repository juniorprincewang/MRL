#pragma execution_character_set("utf-8")
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
#include <QFile>
#include <QDir>
#include <QAxObject>
#include <QDebug>
#include <QScrollArea>
#include "qexcel.h"
#include "model.h"
#include "publicdata.h"



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
    QWidget *object;
    QVBoxLayout *objectLayout;
    QLineEdit *ediblePartText;
    QLineEdit *nonEdiblePartText;
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
    QWidget *location;
    QVBoxLayout *locationLayout;
    QList<QLineEdit *> locationList;
    // 残留水平
    QWidget *residue;
    QVBoxLayout *residueLayout;

    // 按钮
    QHBoxLayout *buttonLayout;
    QPushButton *previewButton;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    // 整体布局
    QVBoxLayout *mainLayout;
public slots:
    void addAdditivePart();
    void deleteAdditivePart();
    void addLocationText();
    void deleteLocationText();
    void addPhi();
    void deletePhi();
    void preview();
    void save();
    void cancel();
private:
    QString xlsFilePath;
    void saveToExcel(PesticideData*, QString);
    void testSaveToExcel();
    void generateExcelTemplate(QString xlsFilePath);
    void preset();
    bool checkValidation();
};


#endif // DATAINSERTION_H
