#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QString>
#include "model.h"

#include "excel.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QDialog>
#include <QDebug>
#include <QTreeView>
#include <QDockWidget>
#include <QListWidget>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
// for imageviewer
#include "imageviewer/imageviewer.h"
#include <QCommandLineParser>
//
#include <QDir>
#include <QFileDialog>
#include "datasheet.h"
#include "exceldatastruct.h"


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // widgets
    Ui::MainWindow *ui;
    QTreeWidget *treeWidget;
    QTabWidget *tabWidget;
//    QWidget *dataPage;
//    QWidget *modelPage;
//    DataSheet *viewPage;
    QGroupBox *viewPage;
    QGroupBox *dataPage;
    QGroupBox *modelPage;
    QGroupBox *recomPage;
    QGroupBox *resultPage;
    QAction *openAction;
    QAction *saveDataAction;
    QAction *aboutMainWindow;
    QAction *exitAction;
    QAction *printAction;
private:
    // 图像r squared 值
    double rSquared = 0.0;
    // structs
    DataStruct *data;
    QVector<DataStruct*> dataVector;
    QString currentPath;
    // 生成菜单和工具栏的Action
    void createAction();
    void setupMenuBar();
    void open();
    void addDataPage();
    void viewData();
    void selectModelPage();
    void recomModelPage();
    void showResultPage();

private:
    // copy excel
//    void copyPlot();

    void makePlot(QString &fileSavePath);
public slots:
    void onTreeWidgetClicked(QTreeWidgetItem *item, int column);
    void onTabWidgetClosed(int index);
    void onAddPushButtonClicked();
    void onPlotPushButtonClicked();
    void onResiduesTextEditTextChanged();
    void onCalculatePushButtonClicked();
    void onSelectViewPushButtonClicked();
    void onReloadViewPushButtonClicked();
    void onResultReflushPushButtionClicked();


    // menu
    void showAbout();
    void print();
    void saveData();

};

#endif // MAINWINDOW_H
