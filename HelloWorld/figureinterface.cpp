#include "figureinterface.h"

FigureInterface::FigureInterface(QWidget *parent)
    :QWidget(parent)
{
    tableLabel = new QLabel("间隔期和残留量（标题栏为间隔期，每一列为对应的残留量，请若修改请回来数据定义项。）", this);
    tableWidget = new QTableWidget(this);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);  //整列选中的方式
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //选择单行模式
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setEnabled(false);
    selectButton = new QPushButton("生成QQ图", this);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableLabel);
    mainLayout->addWidget(tableWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(selectButton);
    mainLayout->addLayout(buttonLayout);
    // 设置滚动轴
    QWidget *client = new QWidget();
    client->setLayout(mainLayout);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(client);
    this->setLayout(new QVBoxLayout);
    this->layout()->addWidget(scrollArea);

    // 当前路径下的MRL文件夹
    this->currentDir = QString("%1/%2").arg(QDir::currentPath()).arg("MRL");
    this->pesticide = NULL;
}
void FigureInterface::preset()
{
    pesticide = new PesticideData;
    pesticide->chineseName = QString("甲氨基阿维菌素苯甲酸盐");
    pesticide->englishName = QString("Emamectin Benzoate");
    pesticide->chemicalName = QString("4'-表-甲胺基-4'-脱氧阿维菌素苯甲酸盐");
    pesticide->molecular = "1008.24";
    pesticide->dosage = "略略";
    pesticide->edible = "稻谷";
    pesticide->nonedible = "水稻秸秆";
    pesticide->method= "喷施";

    QMap<int, QVector<double>> m;
    std::vector<double> e = {0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.010, 0.070, 0.120, 0.190, 0.220, 0.230, 0.260, 0.270, 0.280, 0.330, 0.490, 1.100, 1.200, 1.300, 1.400, 1.600, 1.600,1.600};

    m[5] = QVector<double>::fromStdVector(e);
    pesticide->residues = m;

    key = 5;
//    residues = QVector<double>::fromStdVector(e);
    std::vector<int> days={10, 14, 21, 30, 45, 60};
    std::vector<double> residues = {27.5, 24.8, 21.6, 20.3, 13.7, 12.2};
}



void FigureInterface::fillTableWidget()
{
    QMap<int, QVector<double>> map = this->pesticide->residues;
    QVector<double> residues = map[key];
    // 必须设置行和列，否则setItem无法显示。
    this->tableWidget->setRowCount(1<<16);
    this->tableWidget->setColumnCount(1);
    int col = 0;
    QStringList header;

    header << QString::number(key);
    for(int r_row=0; r_row<residues.size(); r_row++)
    {
        QString r_value = QString::number(residues[r_row]);
        this->tableWidget->setItem(r_row, col, new QTableWidgetItem(r_value));
    }

    this->tableWidget->setHorizontalHeaderLabels(header);
}
