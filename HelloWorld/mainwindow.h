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

namespace Ui {
class MainWindow;
}

typedef struct data_struct
{
    QString regulator;
    QString chemical;
    QString crop;
    QString phi;
    QString rate;
    QVector<double> residues;
    QString unit;

} DataStruct;

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
    QGroupBox *dataPage;
    QGroupBox *modelPage;
    QGroupBox *recomPage;
    QAction *openAction;
private:
    // structs
    DataStruct *data;
    QString currentPath;

    void open();
    void addDataPage();
    void selectModelPage();
    void recomModelPage();
    void showResultPage();
private:
    // excel
    void copyPlot();
public slots:
    void onTreeWidgetClicked(QTreeWidgetItem *item, int column);
    void onTabWidgetClosed(int index);
    void onAddPushButtonClicked();
    void onPlotPushButtonClicked();
    void onResiduesTextEditTextChanged();
    void onCalculatePushButtonClicked();
};

#endif // MAINWINDOW_H
