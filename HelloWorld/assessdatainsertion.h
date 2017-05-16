#pragma execution_character_set("utf-8")
#ifndef ASSESSDATAINSERTION_H
#define ASSESSDATAINSERTION_H
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

class AssessDataInsertion : public QWidget
{
    Q_OBJECT
public:
    AssessDataInsertion(QWidget *parent=0);
private:
    // 农药成分
    QGridLayout *pesticideLayout;
//    QLabel *pesticide;
//    QLabel *chineseName;
    QLineEdit *chineseNameText;
//    QLabel *englishName;
    QLineEdit *englishNameText;
//    QLabel *chemicalName;
    QLineEdit *chemicalNameText;
//    QLabel *molecular;
    QLineEdit *molecularText;
    // 毒性评价
    QGridLayout *toxicityLayout;
//    QLabel *toxicity;   //毒性评价
//    QLabel *adi;    //每日允许驶入量
    QLineEdit *adiText;
//    QLabel *arfd;    //急性参考剂量
    QLineEdit *arfdText;
    QWidget *diet;
    // 残留水平
//    QGridLayout *residueLayout;
//    QLabel *residue;    // 残留水平
//    QLabel *stmr;     //    中值
//    QLineEdit *stmrText;
//    QLabel *stmrp;  //  加工因子矫正的中值（STMR-P）
//    QLineEdit *stmrpText;
//    QLabel *hr;     //  最大值(HR)
//    QLineEdit *hrText;
//    QLabel *mrl;     //  荐残留值（MRL）
//    QLineEdit *mrlText;
    QPushButton *addResidueButton;
    QList<QLabel*> labelList;
    QList<QTextEdit*> textList;
    // 膳食暴露及人群信息
    QVBoxLayout *dietLayout;
////    QLabel *diet;
////    QLabel *fi; //平均消费量（Fi）
//    QLineEdit *fiText;
////    QLabel *lp; //最大消费量（LP）
//    QLineEdit *lpText;
////    QLabel *u; //农产品单个重量（U）
//    QLineEdit *uText;
////    QLabel *v; //差异因子（V）
//    QLineEdit *vText;
////    QLabel *bw; //体重（BW）
//    QLineEdit *bwText;
    // 按钮
    QHBoxLayout *buttonLayout;
    QPushButton *saveButton;
    QPushButton *cancelButton;
    // 整体布局
    QVBoxLayout *mainLayout;
public slots:
    void addResidueText();
    void deleteResidueText();
    void save();
    void cancel();
private:
    QString xlsFilePath;
    bool checkValidation();
    void saveToExcel(AssessData*, QString);
    void preset();
    void generateExcelTemplate(QString xlsFilePath);

};


#endif // ASSESSDATAINSERTION_H
