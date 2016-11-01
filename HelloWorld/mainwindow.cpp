#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDockWidget>
#include <QListWidget>
#include <QLabel>
#include <QMessageBox>
#include <QTabWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGroupBox>
// for imageviewer
#include "imageviewer/imageviewer.h"
#include <QCommandLineParser>
//
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // UI setting
    ui->setupUi(this);
    setWindowTitle(tr("食品中农药残留限量制定及风险评估软件"));


    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu *file = QMainWindow::menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    QMenu *edit = QMainWindow::menuBar()->addMenu(tr("&Edit"));
    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(Qt::TopToolBarArea, toolBar);
    statusBar();

    QWidget* window = new QWidget(this);
    window->setWindowTitle("Enter your age");

    QSpinBox *spinbox = new QSpinBox(window);
    QSlider *slider = new QSlider(Qt::Horizontal, window);

    spinbox->setRange(0, 130);
    slider->setRange(0, 130);
    void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    QObject::connect(spinbox, spinBoxSignal, slider, &QSlider::setValue);
    void (QSlider:: *sliderSignal)(int) = &QSlider::valueChanged;
    QObject::connect(slider, sliderSignal, spinbox, &QSpinBox::setValue);
    spinbox->setValue(30);

    treeWidget = new QTreeWidget(window);
    QStringList headers;
    headers << "Name" ;
    treeWidget->setHeaderLabels(headers);
    treeWidget->setHeaderHidden(true);

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this,    SLOT(onTreeWidgetClicked(QTreeWidgetItem*, int)));
    QTreeWidgetItem *modelData = new QTreeWidgetItem(treeWidget, QStringList() << "数据");
    QTreeWidgetItem *modelSelect = new QTreeWidgetItem(treeWidget, QStringList() << "模型");
    QTreeWidgetItem *modelRecom = new QTreeWidgetItem(treeWidget, QStringList() << "结果");

    new QTreeWidgetItem(modelData, QStringList() << "数据录入");
//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(dataInput, QStringList() << "leaf2");
//    leaf2->setCheckState(leaf2->columnCount()-1 , Qt::Checked);
    new QTreeWidgetItem(modelSelect, QStringList() << QString("模型选择"));
    new QTreeWidgetItem(modelSelect, QStringList() << QString("模型推荐"));

    new QTreeWidgetItem(modelRecom, QStringList() << "MRL推荐");

    QList<QTreeWidgetItem *> topLevel;
    topLevel << modelData << modelSelect << modelRecom;
    treeWidget->insertTopLevelItems(0, topLevel);

    treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    treeWidget.setSortingEnabled(true);
//        treeWidget.show();
//    treeWidget->setAlternatingRowColors(true);
//    treeWidget->setStyleSheet("QTreeWidget::item{height:75px;}; show-decoration-selected: 1;");
////    treeWidget->setStyleSheet("show-decoration-selected: 1;");
//                //"selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5,stop: 0 #FF92BB, stop: 1 white};"
//                //


    tabWidget = new QTabWidget(window);
    tabWidget->setTabsClosable(true);
    QObject::connect(this->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabWidgetClosed(int)));
    tabWidget->setMovable(true);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(treeWidget);
    hBoxLayout->addWidget(tabWidget);
//    hBoxLayout->addWidget(spinbox);
//    hBoxLayout->addWidget(slider);
    window->setLayout(hBoxLayout);
    setCentralWidget(window);
//    window.show();
//    QLabel a(this);
//    a.setText("Label");
//    setCentralWidget(&a);

//    QDockWidget *contents = new QDockWidget(tr("Content of this"), this);
////    contents->setAllowedAreas(Qt::LeftDockWidgetArea
////                                      | Qt::RightDockWidgetArea);
////    QListWidget* headingList = new QListWidget(contents);
////    headingList->insertItem();
//    contents->setWidget(&window);
//    addDockWidget(Qt::LeftDockWidgetArea, contents);
    // data initial
    this->data = NULL;
    this->dataPage = NULL;
    this->modelPage = NULL;
    this->recomPage = NULL;
    QDir dir(QDir::currentPath());
    if(!dir.mkdir(QString("MRL")))
        qDebug() << "the directory already exists or something wrong!";
    this->currentPath = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
    qDebug() << this->currentPath;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addDataPage()
{
    if(this->tabWidget->indexOf(this->dataPage) != -1)
    {
        this->tabWidget->setCurrentWidget(this->dataPage);
        return;
    }
//    this->dataPage = new QWidget();
    QFormLayout *pLayout = new QFormLayout();
    this->dataPage = new QGroupBox(tr("Add Your Data"), this);
    // widgets
    QLineEdit *pRegulatorLineEdit = new QLineEdit(this->dataPage);
    QLineEdit *pChemicalLineEdit = new QLineEdit(this->dataPage);
    QLineEdit *pCropLineEdit = new QLineEdit(this->dataPage);
    QLineEdit *pPHILineEdit = new QLineEdit(this->dataPage);
    QComboBox *pUnitComboBox = new QComboBox(this->dataPage);
    QLineEdit *pRateLineEdit = new QLineEdit(this->dataPage);
    QTextEdit *pResiduesTextEdit = new QTextEdit(this->dataPage);
    QPushButton *pAddPushButton = new QPushButton(this->dataPage);
    QPushButton *pPlotPushButton = new QPushButton(this->dataPage);
    // deal with widgets
    pRegulatorLineEdit->setObjectName("regulator");
    pChemicalLineEdit->setObjectName("chemical");
    pCropLineEdit->setObjectName("crop");
    pPHILineEdit->setObjectName("phi");
    pUnitComboBox->setObjectName("unit");
    pRateLineEdit->setObjectName("rate");
    pResiduesTextEdit->setObjectName("residues");
    pUnitComboBox->setEditable(true);
    pUnitComboBox->addItems(QStringList() << "mg/kg" << "μg/kg");
    pAddPushButton->setText(QString("Add"));
    QObject::connect(pAddPushButton, SIGNAL(clicked()), this, SLOT(onAddPushButtonClicked()));
    pPlotPushButton->setText(QString("Plot"));
    QObject::connect(pPlotPushButton, &QPushButton::clicked, this, &MainWindow::onPlotPushButtonClicked);
//    QObject::connect(pResiduesTextEdit,&QTextEdit::textChanged, this, &MainWindow::onResiduesTextEditTextChanged);
    // add to layout
    pLayout->addRow(QStringLiteral("Regulator:"), pRegulatorLineEdit);
    pLayout->addRow(QStringLiteral("Chemical:"), pChemicalLineEdit);
    pLayout->addRow(QStringLiteral("Crop:"), pCropLineEdit);
    pLayout->addRow(QStringLiteral("PHI:"), pPHILineEdit);
    pLayout->addRow(QStringLiteral("Unit:"), pUnitComboBox);
    pLayout->addRow(QStringLiteral("App. Rate:"), pRateLineEdit);
    pLayout->addRow(QStringLiteral("Residues:"), pResiduesTextEdit);
    pLayout->addRow(pAddPushButton);
    pLayout->addRow(pPlotPushButton);
    pLayout->setSpacing(10);
    pLayout->setMargin(10);
    this->dataPage->setLayout(pLayout);
//    this->dataPage->setLayout(pLayout);
    int indexTab = this->tabWidget->addTab(this->dataPage, QString("ADD DATA"));
    this->tabWidget->setCurrentIndex(indexTab);
    qDebug() << QString("Tab index %1").arg(indexTab);
}

void MainWindow::selectModelPage()
{
    if(this->tabWidget->indexOf(this->modelPage) != -1)
    {
        this->tabWidget->setCurrentWidget(this->modelPage);
        return;
    }
    this->modelPage = new QGroupBox(tr("Make Your Choice"), this);
    // widgets
    QCheckBox *pChineseCheckBox = new QCheckBox(tr("&Chinese Method"));
    QCheckBox *pEUICheckBox = new QCheckBox(tr("&EU I"));
    QCheckBox *pEUIICheckBox = new QCheckBox(tr("EU II"));
    QCheckBox *pCali1CheckBox = new QCheckBox(tr("California 1"));
    QCheckBox *pCali2CheckBox = new QCheckBox(tr("California 2"));
    QCheckBox *pOECDCheckBox = new QCheckBox(tr("OEDC Method"));
    QCheckBox *pNAFTACheckBox = new QCheckBox(tr("NAFTA Method"));
    QPushButton *pSelectPushButton = new QPushButton();
//    pChineseCheckBox->setTristate(true);
    //set widgets
    pSelectPushButton->setText(QString("Calculate"));
    // set VBoxLayout
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pChineseCheckBox);
    vbox->addWidget(pEUICheckBox);
    vbox->addWidget(pEUIICheckBox);
    vbox->addWidget(pCali1CheckBox);
    vbox->addWidget(pCali2CheckBox);
    vbox->addWidget(pOECDCheckBox);
    vbox->addWidget(pNAFTACheckBox);
    vbox->addWidget(pSelectPushButton);
    vbox->addStretch(1);
    // set modelpage
    this->modelPage->setFlat(true);
    this->modelPage->setLayout(vbox);

    int indexTab = this->tabWidget->addTab(this->modelPage, QString("Select Model"));
    this->tabWidget->setCurrentIndex(indexTab);
    qDebug() << QString("Tab index %1").arg(indexTab);
}

void MainWindow::recomModelPage()
{
    if( this->tabWidget->indexOf(this->recomPage) != -1)
    {
        this->tabWidget->setCurrentWidget(this->recomPage);
        return;
    }
    this->recomPage = new QGroupBox(tr("Recommend Model"), this);
    // widgets
    QPushButton *pRecomPushButton = new QPushButton();

    // set widgets
    pRecomPushButton->setText(QString("Recommend Model"));
    QVBoxLayout *vbox = new QVBoxLayout(this->recomPage);
    vbox->addWidget(pRecomPushButton);
    this->recomPage->setLayout(vbox);
    this->recomPage->setFlat(true);
    //
    int indexTab = this->tabWidget->addTab(this->recomPage, QString("Recommend Model"));
    this->tabWidget->setCurrentIndex(indexTab);
    qDebug() << QString("Tab index %1").arg(indexTab);

}

void MainWindow::onPlotPushButtonClicked()
{
    if(this->data == NULL)
    {
        QMessageBox::critical(NULL, "Generating Plot Error!", QString("No Data Yet!"));
        return;
    }

//    QVector<double> residues = this->data->residues;

    Excel * excel = new Excel();
    excel->residues = this->data->residues;
    QString trendLineName = QString("%1_%2_%3_%4").arg(this->data->regulator).arg(this->data->chemical).arg(
                this->data->crop).arg(this->data->phi);
    excel->trendLinesName = trendLineName;
//    excel->import(QString("E:\\学习资料\\农科院程序\\mrl-calculator.xls"));
    QString picturePath = QString("%1/%2.jpg").arg(this->currentPath).arg(trendLineName);
    qDebug() << picturePath;
    QDir dir(this->currentPath);
    if(dir.exists(picturePath))
    {
        QMessageBox::question(NULL, QString("Warning"), QString::fromLocal8Bit("文件已存在，是否覆盖"));
        QMessageBox box;
        box.setText(QString::fromLocal8Bit( "确定" ));
        box.setInformativeText(QString::fromLocal8Bit("文件已存在，是否覆盖?"));
        box.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel );
        int ret = box.exec();
        if(QMessageBox::Save != ret)
        {
            qDebug() << "Not Saved";
            return;
        }
    }
    excel->pictureSavePath = picturePath;
    excel->savePlot();
////    excel->addChart("Data");
//    excel->~Excel();
//    free(excel);
//    excel=NULL;
//    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));
//    QCommandLineParser commandLineParser;
//    commandLineParser.addHelpOption();
//    commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"), ImageViewer::tr("Image file to open."));
//    commandLineParser.process(QCoreApplication::arguments());
    ImageViewer* imageViewer = new ImageViewer(this);
//    if (!commandLineParser.positionalArguments().isEmpty()
//            && !imageViewer->loadFile(commandLineParser.positionalArguments().front()))
//    {
//        return;
//    }

    imageViewer->loadFile(picturePath);
    imageViewer->show();
}

void MainWindow::onAddPushButtonClicked()
{
    if(this->dataPage == NULL)
        return;
    QTextEdit* residues = this->dataPage->findChild<QTextEdit*>("residues", Qt::FindDirectChildrenOnly);
    QString plainText = residues->toPlainText();
    QStringList list = plainText.split("\n", QString::SkipEmptyParts);
    QVector<double> residueVector;
//    qDebug() << list.size();
    for(int i=0; i<list.size(); i++)
    {
        bool ok;
        double residue = list.at(i).toDouble(&ok);
        if(!ok)
        {
            QMessageBox::warning(NULL, "Residues Value Format Error!", QString("%1 at line %2 is invalid!").arg(list.at(i)).arg(i+1));
            return;
        }
        residueVector.push_back(residue);
    }
    DataStruct *data = new DataStruct;
    QLineEdit* regulator = this->dataPage->findChild<QLineEdit*>("regulator", Qt::FindDirectChildrenOnly);
    if(regulator->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("Your regulator isn't inserted!"));
        return;
    }
    data->regulator = QString::fromLocal8Bit(regulator->text().toUtf8());
    QLineEdit *chemical = this->dataPage->findChild<QLineEdit*>("chemical", Qt::FindDirectChildrenOnly);
    if(chemical->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("Your chemical isn't inserted!"));
        return;
    }
    data->chemical = QString::fromLocal8Bit(chemical->text().toUtf8());
    QLineEdit *crop = this->dataPage->findChild<QLineEdit*>("crop", Qt::FindDirectChildrenOnly);
    if(crop->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("Your crop isn't inserted!"));
        return;
    }
    data->crop = QString::fromLocal8Bit(crop->text().toUtf8());
    QLineEdit *phi = this->dataPage->findChild<QLineEdit*>("phi", Qt::FindDirectChildrenOnly);
    data->phi = QString::fromLocal8Bit(phi->text().toUtf8());
    QLineEdit *rate = this->dataPage->findChild<QLineEdit*>("rate", Qt::FindDirectChildrenOnly);
    data->rate = QString::fromLocal8Bit(rate->text().toUtf8());
    QComboBox *unit = this->dataPage->findChild<QComboBox*>("unit", Qt::FindDirectChildrenOnly);
    if(unit->currentText().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("Your unit isn't inserted!"));
        return;
    }
    data->unit = QString::fromLocal8Bit(unit->currentText().toUtf8());
    data->residues = residueVector;
    this->data = data;
//    if(regulator)
//        qDebug()<<"regulator text: " <<regulator->text();
    QMessageBox::about(NULL, QString("Notice"), QString("Your data %1 is inserted!").arg(data->regulator));
}
void MainWindow::onResiduesTextEditTextChanged()
{
    QTextEdit* residues = this->dataPage->findChild<QTextEdit*>("residues", Qt::FindDirectChildrenOnly);


    qDebug() <<residues->toPlainText();

}
void MainWindow::onTabWidgetClosed(int index)
{
    this->tabWidget->removeTab(index);
    qDebug() << QString("tabWidget index:%1 closed!").arg(index);
    return;
}

void MainWindow::onTreeWidgetClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem* parent= item->parent();
    if(parent == NULL)
        return;
    int col = parent->indexOfChild(item);
    QTreeWidget* ptreeWidget= parent->treeWidget();
    if(ptreeWidget == NULL)
        return;
//    int tcount = ptreeWidget->topLevelItemCount();
    int itemIndex = ptreeWidget->indexOfTopLevelItem(parent);
//    QMessageBox::about(NULL, QString("item"), QString().sprintf("%d, index = %d", col, itemIndex));
    qDebug() << QString("col = %1, index = %1").arg(col).arg(itemIndex);
    switch(itemIndex)
    {
    case 0:
        qDebug() << QString("add data page");
        this->addDataPage();
        break;
    case 1:
        if(col == 0)
        {
            qDebug() << QString("select model page");
            this->selectModelPage();
        }
        else if(col == 1)
        {
            qDebug() << QString("recommend model page");
            this->recomModelPage();
        }
        break;
    case 2:
        qDebug() << QString("add result page");

        break;
    default:
        qDebug() << "add error page";
        break;
    }
}

void MainWindow::open()
{
//    QMessageBox::information(this, tr("Information"), tr("Open"));
//    QDialog dialog(this);
//    dialog.setWindowTitle(tr("File Dialog"));
////    dialog.exec();
////    dialog.show();
//    dialog.open();

//    // show and delete on close
//    QDialog *dialog = new QDialog(this);
//    dialog->setAttribute(Qt::WA_DeleteOnClose, true);
//    dialog->show();

    QMessageBox box;
    box.setText(QString::fromLocal8Bit( "确定" ));
    box.setInformativeText(tr("want to saved?"));
    box.setDetailedText(tr("Yes, Saved"));
    box.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard);
    int ret = box.exec();
    switch(ret)
    {
    case QMessageBox::Save :
        qDebug() << "Saved";
        break;
    case QMessageBox::Cancel:
        qDebug() << "Cancel"   ;
        break;
    case QMessageBox::Discard:
        qDebug() << "Discard";
        break;
    default:
        qDebug() << "Detail";
        break;
    }




}

void MainWindow::copyPlot()
{
    //erer
}
