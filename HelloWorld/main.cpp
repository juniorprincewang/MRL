#include "mainwindow.h"
#include "newspaper.h"
#include "reader.h"
#include "eventlabel.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QTranslator>
#include <QDebug>

#include <QLayout>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSplashScreen>
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include <QCoreApplication>
#include "imageviewer/imageviewer.h"
#include <QCommandLineParser>

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<QApplication *>(QCoreApplication::instance()))



class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();

    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QTreeWidget treeWidget;
//    treeWidget.setColumnCount(1);

//    QTreeWidgetItem *root = new QTreeWidgetItem(&treeWidget,
//                                                QStringList(QString("Root")));
//    new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
//    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2")));
//    leaf2->setCheckState(0, Qt::Checked);

//    QList<QTreeWidgetItem *> rootList;
//    rootList << root;
//    treeWidget.insertTopLevelItems(0, rootList);

//    treeWidget.show();




    // QSpinBox & QSlider
//    QTranslator qt;
//    qt.load("qt_zh_CN");
//    a.installTranslator( &qt );
/*
    EventLabel *label = new EventLabel;
    label->setWindowTitle("MouseEvent Demo");
    label->resize(300, 200);
    label->setMouseTracking(true);
    label->show();
*/

//    qDebug() <<  ppf( double(0.95));
//    qDebug() <<  cdf( double(1));

    //  test Excel
/*
    Excel * excel = new Excel();
    excel->import(QString("E:\\学习资料\\农科院程序\\mrl-calculator.xls"));
//    excel->read("Data Library");
//    print(excel->ZScore());
//    excel->formula("Data");
    excel->addChart("Data");
    excel->~Excel();
    excel=NULL;
    free(excel);
*/
    /*
    QVector<double> av;
    av.push_back(0.5);
    av.push_back(0.6);
    av.push_back(0.5);
    qDebug() << countIf(av, 0.5);
    */


    //信号槽
//    Newspaper newspaper("my paper", "123");
//    Reader reader;
//    void (Newspaper:: *signalNewspaper)(const QString&, const QString&) = &Newspaper::newPaper;
//    QObject::connect(&newspaper, &Newspaper::newspaper, &reader, &Reader::receiveNewspaper);
//    QObject::connect(&newspaper, signalNewspaper, &reader, &Reader::receiveNewspaper);
//    newspaper.sendAll();


//    QLabel label("Hello World");
//    label.show();

//    QPushButton pushButton("QUIT");
//    QObject::connect(&pushButton, &QPushButton::clicked, &QApplication::quit);
//    pushButton.show();

    /*
    // sheet test
//    Q_INIT_RESOURCE(spreadsheet);
    SpreadSheet sheet(10, 6);
//    sheet.setWindowIcon(QPixmap(":/images/interview.png"));
    sheet.show();
    sheet.layout()->setSizeConstraint(QLayout::SetFixedSize);
*/

//    QFile file(":/qss/treeview");
//    if(file.open(QFile::ReadOnly))
//        {
//            a.setStyleSheet(file.readAll());
//            file.close();
//            qDebug() << "Open File Successfully!!!";
//        }
//        else
//            QMessageBox::about(NULL, "Test", "Open File Failed");

    CommonHelper::setStyle(":/qss/style");
    QPixmap pixmap(":/images/doc-open");
    QSplashScreen* splash = new QSplashScreen(pixmap);

    splash->show();
    a.processEvents();

    MainWindow w;
    splash->showMessage(QObject::tr("Loading modules..."), Qt::AlignRight | Qt::AlignTop);
    Sleeper::sleep(1);
    w.show();
    splash->finish(&w);
    delete splash;

//    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));
//    QCommandLineParser commandLineParser;
//    commandLineParser.addHelpOption();
//    commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"), ImageViewer::tr("Image file to open."));
//    commandLineParser.process(QCoreApplication::arguments());
//    ImageViewer imageViewer;
//    if (!commandLineParser.positionalArguments().isEmpty()
//            && !imageViewer.loadFile(commandLineParser.positionalArguments().front()))
//    {
//        return 1;
//    }
//    imageViewer.show();

    return a.exec();
}
