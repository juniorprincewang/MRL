#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datasheet.h"
#include "resultsheet.h"
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#endif
#include "printview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // UI setting
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("食品中农药残留限量制定及风险评估软件"));
    createAction();
    setupMenuBar();
    statusBar();

    QWidget* window = new QWidget(this);
 /*   window->setWindowTitle("Enter your age");

    QSpinBox *spinbox = new QSpinBox(window);
    QSlider *slider = new QSlider(Qt::Horizontal, window);

    spinbox->setRange(0, 130);
    slider->setRange(0, 130);
    void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    QObject::connect(spinbox, spinBoxSignal, slider, &QSlider::setValue);
    void (QSlider:: *sliderSignal)(int) = &QSlider::valueChanged;
    QObject::connect(slider, sliderSignal, spinbox, &QSpinBox::setValue);
    spinbox->setValue(30);
*/
    treeWidget = new QTreeWidget(window);
    QStringList headers;
    headers << "Name" ;
    treeWidget->setHeaderLabels(headers);
    treeWidget->setHeaderHidden(true);

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this,    SLOT(onTreeWidgetClicked(QTreeWidgetItem*, int)));
    QTreeWidgetItem *modelData = new QTreeWidgetItem(treeWidget, QStringList() << QStringLiteral("数据"));
    QTreeWidgetItem *modelSelect = new QTreeWidgetItem(treeWidget, QStringList() << QStringLiteral("模型"));
    QTreeWidgetItem *modelRecom = new QTreeWidgetItem(treeWidget, QStringList() << QStringLiteral("结果"));

    new QTreeWidgetItem(modelData, QStringList() << QStringLiteral("数据录入"));
    new QTreeWidgetItem(modelData, QStringList() << QStringLiteral("查看数据"));
//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(dataInput, QStringList() << "leaf2");
//    leaf2->setCheckState(leaf2->columnCount()-1 , Qt::Checked);
    new QTreeWidgetItem(modelSelect, QStringList() << QStringLiteral("模型选择"));
    new QTreeWidgetItem(modelSelect, QStringList() << QStringLiteral("模型推荐"));
    // MRL模型推荐结果
    new QTreeWidgetItem(modelRecom, QStringList() << QStringLiteral("MRL推荐"));

    QList<QTreeWidgetItem *> topLevel;
    topLevel << modelData << modelSelect << modelRecom;
    treeWidget->insertTopLevelItems(0, topLevel);

    treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
//    treeWidget.setSortingEnabled(true);
//    treeWidget.show();
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
    // data initial
    this->data = NULL;
    this->dataPage = NULL;
    this->modelPage = NULL;
    this->recomPage = NULL;
    // 在当前路径下生成MRL文件夹
    QDir dir(QDir::currentPath());
    if(!dir.mkdir(QString("MRL")))
        qDebug() << "the directory already exists or something wrong!";
    this->currentPath = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
    qDebug() << this->currentPath;
}

void MainWindow::createAction()
{
    aboutMainWindow = new QAction(tr("About MRL"), this);
    connect(aboutMainWindow, &QAction::triggered, this, &MainWindow::showAbout);

    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveDataAction = new QAction(tr("&Save Data"), this);
    saveDataAction->setShortcut(Qt::CTRL | Qt::Key_S);
    connect(saveDataAction, &QAction::triggered, this, &MainWindow::saveData);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    printAction = new QAction(tr("&Print"), this);
    connect(printAction, &QAction::triggered, this, &MainWindow::print);
}

void MainWindow::setupMenuBar()
{
    QMenu *file = QMainWindow::menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveDataAction);
    file->addAction(printAction);
    file->addSeparator();
    file->addAction(exitAction);
    QMenu *about = QMainWindow::menuBar()->addMenu(tr("&About"));
    about->addAction(this->aboutMainWindow);
    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBar(Qt::TopToolBarArea, toolBar);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::viewData()
{
    if(this->tabWidget->indexOf(this->viewPage) != -1)
    {
        this->tabWidget->setCurrentWidget(this->viewPage);
        return;
    }

    this->viewPage = new QGroupBox(QStringLiteral("所有数据"), this);
    DataSheet* data_sheet =  new DataSheet(this->viewPage);

    Excel *excel = new Excel();
    QString excelPath = QString("%1/mrl_calculator.xls").arg(this->currentPath);
    this->dataVector= excel->loadData(excelPath , "Data Library");
    delete excel;
//    qDebug() << "DataStruct Vector" << dataVector.size() ;
    data_sheet->addColumns(this->dataVector);

    QVBoxLayout *vBox = new QVBoxLayout(this->viewPage);
    QPushButton *selectButton = new QPushButton(this->viewPage);
    QPushButton *reloadButton = new QPushButton(this->viewPage);
    selectButton->setText(QStringLiteral("选择数据列"));
    reloadButton->setText(QStringLiteral("重新载入"));
    QObject::connect(reloadButton, &QPushButton::clicked, this, &MainWindow::onReloadViewPushButtonClicked);
    QObject::connect(selectButton, &QPushButton::clicked, this, &MainWindow::onSelectViewPushButtonClicked);
    data_sheet->setObjectName("dataSheet");
    vBox->addWidget(data_sheet);
    vBox->addWidget(selectButton);
    vBox->addWidget(reloadButton);
    this->viewPage->setLayout(vBox);
    int indexTab = this->tabWidget->addTab(this->viewPage, QStringLiteral("查看数据"));
    this->tabWidget->setCurrentIndex(indexTab);

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
    this->dataPage = new QGroupBox(QStringLiteral("输入数据"), this);
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
    QPushButton *pSavePushButton = new QPushButton(this->dataPage);
    // deal with widgets
    pRegulatorLineEdit->setObjectName("regulator");
    pChemicalLineEdit->setObjectName("chemical");
    pCropLineEdit->setObjectName("crop");
    pPHILineEdit->setObjectName("phi");
    pUnitComboBox->setObjectName("unit");
    pRateLineEdit->setObjectName("rate");
    pResiduesTextEdit->setObjectName("residues");
    pUnitComboBox->setEditable(true);
    pUnitComboBox->addItems(QStringList() << QStringLiteral("mg/kg") << QStringLiteral("μg/kg"));
    pAddPushButton->setText(QStringLiteral("添加"));
    QObject::connect(pAddPushButton, SIGNAL(clicked()), this, SLOT(onAddPushButtonClicked()));
    pPlotPushButton->setText(QStringLiteral("画图"));
    QObject::connect(pPlotPushButton, &QPushButton::clicked, this, &MainWindow::onPlotPushButtonClicked);
    pSavePushButton->setText(QStringLiteral("保存"));
    QObject::connect(pSavePushButton, &QPushButton::clicked, this, &MainWindow::saveData);
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
    pLayout->addRow(pSavePushButton);
    pLayout->setSpacing(10);
    pLayout->setMargin(10);
    this->dataPage->setLayout(pLayout);
//    this->dataPage->setLayout(pLayout);
    int indexTab = this->tabWidget->addTab(this->dataPage, QStringLiteral("添加数据"));
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
    this->modelPage = new QGroupBox(QStringLiteral("选择模型"), this);
    // widgets
    QCheckBox *pChineseCheckBox = new QCheckBox(tr("&Chinese Method"), this->modelPage);
    QCheckBox *pEUICheckBox = new QCheckBox(tr("&EU I"), this->modelPage);
    QCheckBox *pEUIICheckBox = new QCheckBox(tr("EU II"), this->modelPage);
    QCheckBox *pCali1CheckBox = new QCheckBox(tr("California 1"), this->modelPage);
    QCheckBox *pCali2CheckBox = new QCheckBox(tr("California 2"), this->modelPage);
    QCheckBox *pOECDCheckBox = new QCheckBox(tr("OEDC Method"), this->modelPage);
    QCheckBox *pNAFTACheckBox = new QCheckBox(tr("NAFTA Method"), this->modelPage);
    QPushButton *pSelectPushButton = new QPushButton(this->modelPage);
    QCheckBox *pRoundedCheckBox = new QCheckBox(tr("Would you like the values rounded?"), this->modelPage);
//    pChineseCheckBox->setTristate(true);
    //set widgets
    pChineseCheckBox->setObjectName("Chinese");
    pEUICheckBox->setObjectName("EUI");
    pEUIICheckBox->setObjectName("EUII");
    pCali1CheckBox->setObjectName("Cali1");
    pCali2CheckBox->setObjectName("Cali2");
    pOECDCheckBox->setObjectName("OECD");
    pNAFTACheckBox->setObjectName("NAFTA");
    pSelectPushButton->setObjectName("Select");
    pRoundedCheckBox->setObjectName("Rounded");

    pSelectPushButton->setText(QStringLiteral("计算"));
    QObject::connect(pSelectPushButton, &QPushButton::clicked, this, &MainWindow::onCalculatePushButtonClicked);
    QVBoxLayout *tlayout = new QVBoxLayout(this->modelPage);
    // set VBoxLayout
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(pChineseCheckBox);
    vbox->addWidget(pEUICheckBox);
    vbox->addWidget(pEUIICheckBox);
    vbox->addWidget(pCali1CheckBox);
    vbox->addWidget(pCali2CheckBox);
    vbox->addWidget(pOECDCheckBox);
    vbox->addWidget(pNAFTACheckBox);
//    vbox->addStretch(10);
    // set VBoxLayout
    QVBoxLayout *hbox = new QVBoxLayout();
    hbox->addWidget(pRoundedCheckBox);
    hbox->addWidget(pSelectPushButton);
//    hbox->addStretch(1);
    // total layout

    tlayout->addLayout(vbox);
    tlayout->addLayout(hbox);
    // set modelpage
    this->modelPage->setFlat(true);
    this->modelPage->setLayout(tlayout);

    int indexTab = this->tabWidget->addTab(this->modelPage, QStringLiteral("模型选择"));
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
    this->recomPage = new QGroupBox(QStringLiteral("推荐模型"), this);
    // widgets
    QPushButton *pRecomPushButton = new QPushButton();

    // set widgets
    pRecomPushButton->setText(QStringLiteral("推荐"));
    QVBoxLayout *vbox = new QVBoxLayout(this->recomPage);
    vbox->addWidget(pRecomPushButton);
    this->recomPage->setLayout(vbox);
    this->recomPage->setFlat(true);
    //
    int indexTab = this->tabWidget->addTab(this->recomPage, QStringLiteral("推荐模型"));
    this->tabWidget->setCurrentIndex(indexTab);
    qDebug() << QString("Tab index %1").arg(indexTab);
}

void MainWindow::showResultPage()
{
    if( this->tabWidget->indexOf(this->resultPage) != -1)
    {
        this->tabWidget->setCurrentWidget(this->resultPage);
        return;
    }
    this->resultPage = new QGroupBox(QStringLiteral("推荐结果"), this);
    // widgets
    ResultSheet* resultSheet = new ResultSheet(this->resultPage);
//    resultSheet->reloadColumns();

    QPushButton *pResultReflushPushButton = new QPushButton(this->resultPage);

    // set widgets
    pResultReflushPushButton->setText(QStringLiteral("刷新结果"));
    QVBoxLayout *vbox = new QVBoxLayout(this->resultPage);
    vbox->addWidget(pResultReflushPushButton);
    this->resultPage->setLayout(vbox);
    this->resultPage->setFlat(true);
    //
    int indexTab = this->tabWidget->addTab(this->resultPage, QStringLiteral("推荐结果"));
    this->tabWidget->setCurrentIndex(indexTab);
    qDebug() << QString("Tab index %1").arg(indexTab);
}

void MainWindow::onResultReflushPushButtionClicked()
{

}

void MainWindow::onPlotPushButtonClicked()
{
    if(this->data == NULL)
    {
        QMessageBox::critical(NULL, "Generating Plot Error!", QString("No Data Yet!"));
        return;
    }
    QString trendLineName = QString("%1_%2_%3_%4").arg(this->data->regulator.trimmed()).arg(this->data->chemical.trimmed()).arg(
                this->data->crop.trimmed()).arg(this->data->phi.trimmed());

    QString picturePath = QString("%1/%2.jpg").arg(this->currentPath).arg(trendLineName);
    MainWindow::makePlot(picturePath);

    ImageViewer* imageViewer = new ImageViewer(this);
    imageViewer->loadFile(picturePath);
    imageViewer->show();
}

void MainWindow::makePlot(QString &fileSavePath)
{
    if(this->data == NULL)
    {
        QMessageBox::critical(NULL, "Generating Plot Error!", QString("No Data Yet!"));
        return;
    }
//    QVector<double> residues = this->data->residues;

    Excel * excel = new Excel();
    excel->residues = this->data->residues;
    QString trendLineName = QString("%1_%2_%3_%4").arg(this->data->regulator.trimmed()).arg(this->data->chemical.trimmed()).arg(
                this->data->crop.trimmed()).arg(this->data->phi.trimmed());
    excel->trendLinesName = trendLineName;

    QDir dir(fileSavePath);
    if(dir.exists())
    {
//        QMessageBox::question(NULL, QString("Warning"), QStringLiteral("文件已存在，是否覆盖"));
        QMessageBox box;
        box.setText(QStringLiteral("确定"));
        box.setInformativeText(QStringLiteral("文件已存在，是否覆盖?"));
        box.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel );
        int ret = box.exec();
        if(QMessageBox::Save != ret)
        {
            qDebug() << "Not Saved";
            return;
        }
    }
    excel->pictureSavePath = fileSavePath;
    this->rSquared= excel->savePlot();
    delete excel;
    qDebug() << "Plot is saved! and rSquaredValue is "<<this->rSquared;
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
    data->regulator = QString::fromLocal8Bit(regulator->text().trimmed().toUtf8());
    QLineEdit *chemical = this->dataPage->findChild<QLineEdit*>("chemical", Qt::FindDirectChildrenOnly);
    if(chemical->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("Your chemical isn't inserted!"));
        return;
    }
    data->chemical = QString::fromLocal8Bit(chemical->text().trimmed().toUtf8());
    QLineEdit *crop = this->dataPage->findChild<QLineEdit*>("crop", Qt::FindDirectChildrenOnly);
    if(crop->text().isEmpty())
    {
        QMessageBox::critical(NULL, QString("Critical"), QString("Your crop isn't inserted!"));
        return;
    }
    data->crop = QString::fromLocal8Bit(crop->text().trimmed().toUtf8());
    QLineEdit *phi = this->dataPage->findChild<QLineEdit*>("phi", Qt::FindDirectChildrenOnly);
    data->phi = QString::fromLocal8Bit(phi->text().trimmed().toUtf8());
    QLineEdit *rate = this->dataPage->findChild<QLineEdit*>("rate", Qt::FindDirectChildrenOnly);
    data->rate = QString::fromLocal8Bit(rate->text().trimmed().toUtf8());
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


    QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("数据成功插入!"));
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

void MainWindow::onCalculatePushButtonClicked()
{
    if(NULL == this->data)
    {
        QMessageBox::critical(NULL, QStringLiteral("错误"), QStringLiteral("未添加或选择数据"));
        return;
    }
    QCheckBox* Chinese = this->modelPage->findChild<QCheckBox*>("Chinese", Qt::FindDirectChildrenOnly);
    QCheckBox* EUI = this->modelPage->findChild<QCheckBox*>("EUI", Qt::FindDirectChildrenOnly);
    QCheckBox* EUII = this->modelPage->findChild<QCheckBox*>("EUII", Qt::FindDirectChildrenOnly);
    QCheckBox* Cali1 = this->modelPage->findChild<QCheckBox*>("Cali1", Qt::FindDirectChildrenOnly);
    QCheckBox* Cali2 = this->modelPage->findChild<QCheckBox*>("Cali2", Qt::FindDirectChildrenOnly);
    QCheckBox* OECD = this->modelPage->findChild<QCheckBox*>("OECD", Qt::FindDirectChildrenOnly);
    QCheckBox* NAFTA = this->modelPage->findChild<QCheckBox*>("NAFTA", Qt::FindDirectChildrenOnly);
    bool NoneChecked = true;
    QList<QCheckBox*> childCheckBoxes= this->modelPage->findChildren<QCheckBox*>(QString(), Qt::FindDirectChildrenOnly);
    foreach(QCheckBox* tmp, childCheckBoxes)
    {
        if(tmp->isChecked())
        {
            NoneChecked = false;
            break;
        }
    }
    if(NoneChecked)
    {
        QMessageBox::critical(NULL, QStringLiteral("警告"), QStringLiteral("至少选择一个模型."));
        return;
    }
    QCheckBox* bRoundedCheckBox = this->modelPage->findChild<QCheckBox*>("Rounded", Qt::FindDirectChildrenOnly);
    bool bRounded = bRoundedCheckBox->isChecked();

    QString trendLineName = QString("%1_%2_%3_%4").arg(this->data->regulator.trimmed()).arg(this->data->chemical.trimmed()).arg(
                this->data->crop.trimmed()).arg(this->data->phi.trimmed());

    QString picturePath = QString("%1/%2.jpg").arg(this->currentPath).arg(trendLineName);
    MainWindow::makePlot(picturePath);

    // 对数验证
    Model model(this->data->residues.toStdVector());

    int normality = model.ShapiroFranciaNormalityTest(this->rSquared);
    if(0 ==normality)
        QMessageBox::information(NULL, QStringLiteral("Shapiro-Francia Normality"), QStringLiteral("Error"));
    else if(1 == normality)
        QMessageBox::information(NULL, QStringLiteral("Shapiro-Francia Normality"), QStringLiteral("p-value <= 0.01: Reject lognormality assumption"));
    else if(2 == normality)
        QMessageBox::information(NULL, QStringLiteral("Shapiro-Francia Normality"), QStringLiteral("0.05 >= p-value > 0.01 : Reject lognormality assumption"));
    else if(3 == normality)
        QMessageBox::information(NULL, QStringLiteral("Shapiro-Francia Normality"), QStringLiteral("p-value > 0.05 : Do not reject lognormality assumption"));

    if(Chinese->isChecked())
    {

    }
    if(EUI->isChecked())
    {
        std::vector<QString> results = model.EUMethodI(bRounded);
//        for(auto p: results)
//        {
//            qDebug() << p;
//        }
        QString s;
        QString display("5 results of EUI is as follows:\r\n");
        display+="95th Percentile           : "+results[0] +"\r\n";
//        display+=s.sprintf("%-30s : %10s\r\n","95th Percentile",results[0]);
        display+="LN 95th Percentile        : "+results[1]+"\r\n";
//        display+=s.sprintf("%-30s : %10s\r\n","LN 95th Percentile",results[1]);
        display+="99th Percentile           : "+results[2]+"\r\n";
        display+="LN 99th Percentile        : "+results[3]+"\r\n";
        display+="99.9th Percentile         : "+results[4]+"\r\n";
        QMessageBox::information(NULL, QStringLiteral("结果"), display);
    }
    if(EUII->isChecked())
    {
//        std::vector<std::pair<double, int> > results = model.EUMethodII();
//        for(auto p: results)
//        {
//            qDebug() << QString::number(p.first, 'f', p.second);
//        }
        std::vector<QString> results = model.EUMethodII(bRounded);

        QString display("The result of EUII is : ");
        display+="99th Percentile       : "+results[0]+"\r\n";
        QMessageBox::information(NULL, QStringLiteral("结果"), display);

//        for(auto p: results)
//        {
//            qDebug() << p;
//        }
    }
    if(Cali1->isChecked())
    {
        std::vector<QString> results = model.CaliMethodI(bRounded);

        QString display("The result of Cali Method I is : ");
        display+="99th Percentile       : "+results[0]+"\r\n";
        QMessageBox::information(NULL, QStringLiteral("结果"), display);
    }
    if(Cali2->isChecked())
    {
        /*
         *
         * 暂时将UPLMedian95th放入Cali2中。
        */
        std::vector<QString> results = model.UPLMedian95th(bRounded);

        QString display("The result of UCLMedian95th Method is : ");
        display+="95th Percentile       : "+results[0]+"\r\n";
        QMessageBox::information(NULL, QStringLiteral("结果"), display);
    }
    if(OECD->isChecked())
    {
    }
    if(NAFTA->isChecked())
    {
//        std::vector<std::pair<double, int> > results = model.NAFTA();
        std::vector<QString > results = model.NAFTA(bRounded);
        QString display("5 results of NAFTA is as follows:\r\n");
        display+="95th Percentile       : "+results[0]+"\r\n";
        display+="LN 95th Percentile    : "+results[1]+"\r\n";
        display+="99th Percentile       : "+results[2]+"\r\n";
        display+="LN 99th Percentile    : "+results[3]+"\r\n";
        display+="99.9th Percentile     : "+results[4]+"\r\n";
        QMessageBox::information(NULL, QStringLiteral("结果"), display);
//        for(auto p: results)
//        {
//            qDebug() << p;
//        }
    }

}

void MainWindow::onSelectViewPushButtonClicked()
{
    QTableWidget* table = this->viewPage->findChild<QTableWidget*>("viewTable");
    int column = table->currentColumn();
//    qDebug() << "select column : "<< column;
    if(column > 0)
    {
        this->data = this->dataVector.at(column-1);
        QMessageBox::information(NULL, QStringLiteral("选择数据列!"), QStringLiteral("成功选择数据列"));
        return;
    }
    QMessageBox::warning(NULL, QStringLiteral("选择数据列!"), QStringLiteral("选择数据列无效!"));
}
void MainWindow::onReloadViewPushButtonClicked()
{
    DataSheet* sheet = this->viewPage->findChild<DataSheet*>("dataSheet");
    Excel *excel = new Excel();
    QString excelPath = QString("%1/mrl_calculator.xls").arg(this->currentPath);
    this->dataVector= excel->loadData(excelPath , "Data Library");
    delete excel;
    sheet->reloadColumns(this->dataVector);
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
    qDebug() << QString("col = %1, index = %2").arg(col).arg(itemIndex);
    switch(itemIndex)
    {
    case 0:
        if(col ==0 )
        {
            qDebug() << QString("add data page");
            this->addDataPage();
        }
        else if(col == 1)
        {
            qDebug() << QString("view data");
            this->viewData();
        }
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

        qDebug() << QString("result page");
//        this->showResultPage();
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

    /*
    QMessageBox box;
    box.setText(QStringLiteral( "确定" ));
    box.setInformativeText(QStringLiteral("要保存吗?"));
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
    */



}

void MainWindow::showAbout()
{
    const char *aboutText =
            "<HTML>"
            "<p><b>This demo shows use of <c>QTableWidget</c> with custom handling for"
            " individual cells.</b></p>"
            "<p>Using a customized table item we make it possible to have dynamic"
            " output in different cells. The content that is implemented for this"
            " particular demo is:"
            "<ul>"
            "<li>Adding two cells.</li>"
            "<li>Subtracting one cell from another.</li>"
            "<li>Multiplying two cells.</li>"
            "<li>Dividing one cell with another.</li>"
            "<li>Summing the contents of an arbitrary number of cells.</li>"
            "</HTML>";
    QMessageBox::about(this, "About MRL", aboutText);
}

void MainWindow::print()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintPreviewDialog dlg(&printer);
    PrintView view;
//    view.setModel(table->model());
    connect(&dlg, &QPrintPreviewDialog::paintRequested, &view, &PrintView::print);
    dlg.exec();
#endif
}

void MainWindow::saveData()
{
    if(NULL == this->data)
    {
        QMessageBox::critical(NULL, QStringLiteral("提示"), QStringLiteral("未有添加数据!"));
        return;
    }
    QString excelPath = QString("%1/mrl_calculator.xls").arg(this->currentPath);
    Excel * excel = new Excel();
//    qDebug() << excelPath;
//    QDir dir(this->currentPath);
//    if(dir.exists(excelPath))
//    {
//        QMessageBox::question(NULL, QString("Warning"), QString::fromLocal8Bit("The File exits, overwrite?"));
//        QMessageBox box;
//        box.setText(QString::fromLocal8Bit( "Are you sure?" ));
//        box.setInformativeText(QString::fromLocal8Bit("File exists, overwrite?"));
//        box.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel );
//        int ret = box.exec();
//        if(QMessageBox::Save != ret)
//        {
//            qDebug() << "Not Saved";
//            return;
//        }
//    }
//    else
//    {
//        QString filename = QFileDialog::getSaveFileName(NULL, "Save File", ".", "Excel File(*.xls)");
//        excel->createFile(excelPath);
//    }

//    excel->fileSavePath = excelPath;
    excel->saveData(this->data, excelPath, "Data Library");
    delete excel;
//    qDebug() << "Saved";
    QMessageBox::information(NULL, QStringLiteral("提示"), QString("%1 saved!").arg(this->data->regulator));
}

