#include "excel.h"
#include <QFile>
#include <QTextStream>
#include <QAxObject>
#include <QDir>
#include <QFileInfo>



Excel::Excel()
{
    this->excel = new QAxObject("Excel.Application");
    //xlMaximized =-4137 xlMinimized =-4140 •xlNormal =-4143
    this->excel->setProperty("WindowState", -4137);
    this->excel->setProperty("Visible", DEBUG);
}

Excel::~Excel()
{
    this->excel->dynamicCall("Quit()");
    free(this->excel);
}

void Excel::createDoc(const QString& fileName, QAxObject* qObject)
{
    QFile file1(fileName);
    if(file1.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file1);
        out << qObject->generateDocumentation();
        file1.close();
    }
}

void Excel::read(const QString &sheetName)
{
    QAxObject *work_book = this->excel->querySubObject("ActiveWorkBook");
//    this->createDoc(QString("D:\\Qt\\workBookAPI.html"), work_book);
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
    qDebug()<<QString("sheet count : ")<<sheet_count;
//    for(int i=1; i<=sheet_count; i++)
//    {
//        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", i);  //Sheets(int)也可换用Worksheets(int)
//        QString work_sheet_name = work_sheet->property("Name").toString();  //获取工作表名称
//        QString message = QString("sheet ")+QString::number(i, 10)+ QString(" name");
//        qDebug()<<message<<work_sheet_name;
//    }

    if(sheet_count > 0)
    {
//        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
        QAxObject *work_sheet = work_book->querySubObject("Sheets(const String&)", sheetName);
//        this->createDoc(QString("D:\\Qt\\workSheetAPI.html"), work_sheet);
        QAxObject *used_range = work_sheet->querySubObject("UsedRange");
//        this->createDoc(QString("D:\\Qt\\workSheetAPI.html"), used_range);
        QAxObject *columns = used_range->querySubObject("Columns");
        QAxObject *column2ed = columns->querySubObject("item(int)", 2);
//        this->createDoc(QString("D:\\Qt\\column2edAPI.html"), column2ed);
        int column_start = column2ed->property("Column").toInt();  //获取起始列
        int column_count = column2ed->property("Count").toInt();  //获取列数
        qDebug() << QString("column start") << column_start << QString("column count: ")<<column_count << endl;

        QAxObject *row = column2ed->querySubObject("Rows");
        int row_start = column2ed->property("Row").toInt();  //获取起始行
        int row_count = row->property("Count").toInt();  //获取行数
        qDebug() << QString("row start") << row_start << QString("row count: ")<<row_count << endl;

        QMap<QString, QString> indexMap;
        QVector<QString> otherStuff(5);
        otherStuff.push_back(QString("Regulator"));
        otherStuff.push_back(QString("Chemical"));
        otherStuff.push_back(QString("Crop"));
        otherStuff.push_back(QString("PHI"));
        otherStuff.push_back(QString("App. Rate"));
        QVector<double> residues;
        for(int i=1; i<=5; i++)
        {
            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, column_start);
            QVariant cell_value = cell->property("Value");  //获取单元格内容
            if(!cell_value.isNull() && !cell_value.isValid())
                indexMap.insert(otherStuff[i], cell_value.toString());
            else
                indexMap.insert(otherStuff[i], NULL);
        }
        this->indexMap = indexMap;
        for(int i=8; i <= row_count; i++)
        {
            QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, column_start);
//        this->createDoc(QString("D:\\Qt\\cellsAPI.html"), cell);
            QVariant cell_value = cell->property("Value");  //获取单元格内容
            if(!cell_value.isValid())
                break;
            residues.push_back(cell_value.toDouble());
            QString message = QString("row-")+QString::number(i, 10)+QString("-column-")+QString::number(column_start, 10)+QString(":");
            qDebug()<<message<<cell_value;
        }
        this->residues = residues;
    }
    work_book->dynamicCall("Close(Boolean)", false);
//    this->excel->dynamicCall("Quit()");
}

void Excel::import(const QString& fileName)
{
    QAxObject *work_books = this->excel->querySubObject("WorkBooks");
//    this->createDoc(QString("D:\\Qt\\workBooksAPI.html"), work_books);
    work_books->dynamicCall("Open(const QString&)", fileName);
//    QVariant title = excel.property("Caption");
//    qDebug() << QString("Title: ") << title;

    /*
    work_books->dynamicCall("Add(void)");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取当前工作簿
    QAxObject *worksheets = workbook->querySubObject("Sheets");//获取工作表集合
    QAxObject *worksheet = worksheets->querySubObject("Item(int)", 1);//获取工作表集合的工作表1，即sheet1

    for (int i = 0; i < 12; i++)
    {
        int count = QINDEX[i].size();
        for (int j = 0; j < QINDEX[i].size(); j++)
        {
            QAxObject *cellnum;
            QString num = (QChar)('A' + i) + QString::number(j + 1);
            cellnum = worksheet->querySubObject("Range(QVariant, QVariant)", num);//获取单元格
            cellnum->dynamicCall("SetValue(const QVariant&)", QVariant(QINDEX[i][j]));
        }
    }

    workbook->dynamicCall("SaveAs(const QString&)", QString("./test.xlsx"));
    workbook->dynamicCall("Close()");//关闭工作簿
    excel.dynamicCall("Quit()");//关闭excel
    */
}

void Excel::savePlot()
{
    QAxObject *work_books = this->excel->querySubObject("WorkBooks");
//    QFileInfo fileInfo(this->pictureSavePath);
//    QString tmpFile = QString("%1/%2.xls").arg(fileInfo.path()).arg(fileInfo.baseName());
//    work_books->dynamicCall("Open(const QString&)",  tmpFile);
    work_books->dynamicCall("Add");
    QAxObject *workbook = this->excel->querySubObject("ActiveWorkBook");
//    QAxObject *work_sheets = workbook->querySubObject("Sheets");  //Sheets也可换用WorkSheets
//    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
//    QAxObject *worksheet = workbook->querySubObject("Worksheets(String&)", sheetName);

//        QAxObject *work_sheet = work_book->querySubObject("Sheets(const String&)", "Probability Plot");
//        work_sheet->dynamicCall("Select(void");
//        QAxObject *chart = work_book->querySubObject("ActiveChart");
//        chart->dynamicCall("Export(Filename, FilterName)", "D:\\Qt\\PPPPPPPPPPPPPPPP.jpg", "jpg");

//        worksheet->dynamicCall("Select(void)"); // very important
//        QAxObject *range = worksheet->querySubObject("Range(A1:B7)");
//        range->dynamicCall("Select (void)");
    QAxObject *chart = workbook->querySubObject("Charts")->querySubObject("Add");
//    this->createDoc(QString("D:\\Qt\\chartAPI.html"), chart);
    QAxObject * series = chart->querySubObject("SeriesCollection");
    // qDebug() << series->property("Count");   // 3 !
    series->dynamicCall("NewSeries(void)");

    QAxObject * serie   = series->querySubObject("Item (int)", 1);
    serie->setProperty("Name", "(Z-score, Ln(residue))");
    // from worksheet
//        QAxObject * xvalues = worksheet->querySubObject("Range(D8:D21)");
//        QAxObject * yvalues = worksheet->querySubObject("Range(C8:C21)");
//        serie->setProperty("XValues", xvalues->asVariant());
//        serie->setProperty("Values",  yvalues->asVariant());
    // from vector
    QList<QVariant> listXValues, listValues;
    std::vector<double> ln_residues = Model::getLnVector(this->residues.toStdVector());
    std::vector<double> zScore = Model::getZScoreVector(this->residues.toStdVector());
//        listXValues =  zScore.toList();
//        listValues = ln_residues.toList();
    for(int i=0; i<ln_residues.size(); i++)
    {
        listXValues.push_back(zScore[i]);
        listValues.push_back(ln_residues[i]);
    }
    serie->setProperty("XValues",listXValues);
    serie->setProperty("Values",listValues);
    serie->dynamicCall("Select(void)");
    /* set chart property*/
    chart->setProperty("Name", "Probability Chart");
//    xlXYScatter    -4169    Scatter.
    chart->setProperty("ChartType", -4169);
    chart->setProperty("HasTitle", true);
    QAxObject* chartTitle = chart->querySubObject("ChartTitle");
    chartTitle->setProperty("Text", "Lognormal Probability Plot"); // read-only or does not exist
    // XlCategoryLabelLevelCustom -2 (&HFFFFFFFE) Indicates literal data in the category labels.
//    chart->setProperty("CategoryLabelLevel", -2);   // !Exception
    chart->setProperty("BarShape", 0); // xlBox
    chart->setProperty("ChartColor", 2);
    chart->setProperty("DepthPercent", 100);
    chart->setProperty("DisplayBlanksAs", 0);// lxBox !
//    chart->setProperty("Elevation", 15);    // Exception
    chart->setProperty("GapDepth", 150);
    chart->setProperty("HasDataTable", false);
    chart->setProperty("HasLegend", true);
//    chart->setProperty("HeightPercent", 100);   // Exception
//    chart->setProperty("Perspective", 30);  // Exception
    chart->setProperty("Rotation", 20);
//    chart->dynamicCall("SetSeriesNameLevel(int)", -2);
//    int val = chart->property("SeriesNameLevel").toInt();
//    qDebug() << QString("SeriesNameLevel = %1").arg(val);
//    chart->setProperty("SeriesNameLevel", -2);// !xlSeriesNameLevelCustom
//    val = chart->property("SeriesNameLevel").toInt();
//    qDebug() << QString("SeriesNameLevel = %1").arg(val);
    chart->setProperty("Visible", -1);
    /* set x, y axis property */
    QAxObject* x_axis = chart->querySubObject("Axes(int)", 1);
    QAxObject* y_axis = chart->querySubObject("Axes(int)", 2);
    x_axis->setProperty("HasTitle", true);
    QAxObject* x_axisTitle = x_axis->querySubObject("AxisTitle");
    x_axisTitle->setProperty("Text", "Percentiles");
    x_axis->setProperty("HasMajorGridlines", false);
    x_axis->setProperty("HasMinorGridlines", false);
    y_axis->setProperty("HasTitle", true);
    QAxObject* y_axisTitle = y_axis->querySubObject("AxisTitle");
    y_axisTitle->setProperty("Text", "Concentrate");
    y_axis->setProperty("HasMajorGridlines", false);
    y_axis->setProperty("HasMinorGridlines", false);

//    serie = series->querySubObject("Item (int)", 2);
//    yvalues = worksheet->querySubObject("Range(C2:C9)");
//    serie->setProperty("XValues", xvalues->asVariant());
//    serie->setProperty("Values",  yvalues->asVariant());
    // 添加趋势线
    QAxObject *trendLines = serie->querySubObject("Trendlines()");
    if (trendLines) {
        trendLines->dynamicCall("Add()");
        int nbTrendLines = trendLines->property("Count").toInt();
        QAxObject *trendLine = serie->querySubObject("Trendlines(int)",nbTrendLines);
        // 设定图标格式为 “散点图”，数字-4132来自 枚举变量 XlTrendlineType  : xlLinear
        trendLine->setProperty("Type",-4132);       // XlTrendlineType  : xlLinear
        trendLine->setProperty("Name", this->trendLinesName);
        trendLine->setProperty("DisplayEquation",true);
        trendLine->setProperty("DisplayRSquared",true);

        QAxObject *dataLabel = trendLine->querySubObject("DataLabel");
        QString strFormula = dataLabel->property("Formula").toString();
        qDebug() << strFormula;         // "y = -9.113ln(x) + 78.016"
    }
    // 拷贝图片，参考 https://msdn.microsoft.com/en-us/library/office/ff841052.aspx
    // xlScreen = 1, xlPicture =-4147
//        chart->dynamicCall("CopyPicture(Appearance, Format)", 1, -4147); //
//        workbook->dynamicCall("SaveAs (const QString&)", "D:\\Qt\\a");
    chart->dynamicCall("Export(Filename, FilterName)", this->pictureSavePath, "jpg");


    workbook->dynamicCall("Close (Boolean)", false);
    this->excel->dynamicCall("Quit (void)");
}

void Excel::exportPicture()
{
    QAxObject *work_book = this->excel->querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
//    qDebug()<<QString("sheet count : ")<<sheet_count;

    if(sheet_count > 0)
    {
        QAxObject *work_sheet = work_book->querySubObject("Sheets(const String&)", "Data");
        work_sheet->dynamicCall("Select(void");
        QAxObject *chart = work_book->querySubObject("ActiveChart");
//        chart->dynamicCall("CopyPicture()");
        chart->dynamicCall("Export(Filename, FilterName)", "D:\\Qt\\PPPPPPPPPPPPPPPP.jpg", "jpg");
    }
    work_book->dynamicCall("Close(Boolean)", false);
}

void Excel::formula(const QString &sheetName )
{
    QAxObject *work_book = this->excel->querySubObject("ActiveWorkBook");
    QAxObject *work_sheet = work_book->querySubObject("Sheets(const String&)", sheetName);
    QAxObject *shapes = work_sheet->querySubObject("Shapes");

    QAxObject *emptyCell = work_sheet->querySubObject("Cells(int,int)", 21, 1 );
    // 先选中一个空白的地方，不然后面的SeriesCollection会先将所有行都做个散点图。。。
    emptyCell->dynamicCall("Select(void)");
    shapes->dynamicCall("AddChart(int)",-4169,100,100,500,800); // height width
    // 再将视野拖回到左上角区域
    QAxObject *range = work_sheet->querySubObject("Range(QVariant)","$B$1:$D$1");
    range->dynamicCall("Select(void)");

    int nbChart = shapes->property("Count").toInt();
    qDebug() << "chart size :" <<nbChart;
    QAxObject *shape = shapes->querySubObject("Range(int)",nbChart);
    qDebug() << "Name" <<shape->property("Name").toString();        // 获取Name属性
    qDebug() << "Title" <<shape->property("Title").toString();      // 获取Title属性
    //shape->dynamicCall("ScaleWidth(QVariant,QVariant)",2,0);
    shape->dynamicCall("Select(void)");

    QAxObject *chart = work_book->querySubObject("ActiveChart");
    QAxObject *seriesCollection = chart->querySubObject("SeriesCollection()");
    seriesCollection->dynamicCall("NewSeries (void)");
    int nb = seriesCollection->property("Count").toInt();
    QAxObject *series = chart->querySubObject("SeriesCollection(int)",nb);
    series->setProperty("Name","SeriesNo1");

    // 选中部分单元格
//    QAxObject *range = work_sheet->querySubObject("Range(QVariant,QVariant)",coordInt2String(1,2),coordInt2String(1,9));
    range = work_sheet->querySubObject("Range(QVariant)","$B$1:$Q$1");
    range->dynamicCall("Select(void)");
    QAxObject * xvalues = work_sheet->querySubObject("Range(D8:D21)");
    QAxObject * yvalues = work_sheet->querySubObject("Range(C8:C21)");
    series->setProperty("XValues", xvalues->asVariant());
    series->setProperty("Values", yvalues->asVariant());

    // 给该系列添加源数据
    // 这里我的数据来自其他部分，非Excel文件，
    // 想使用Excel文件数据可采用上面的方法，先选中数据单元格，然后传递过去
    /*
    QList<QVariant> listXValues, listValues;
    for (int i=1; i<_colFenwei.size(); i++)
    {
        listXValues.push_back(i+1);
        listValues.push_back(_colFenwei.at(i));
    }
    series->setProperty("XValues",listXValues);
    series->setProperty("Values",listValues);
    series->dynamicCall("Select(void)");
    */
/*
    // 添加趋势线
    QAxObject *trendLines = series->querySubObject("Trendlines()");
    if (trendLines) {
        trendLines->dynamicCall("Add()");
        int nbTrendLines = trendLines->property("Count").toInt();
        QAxObject *trendLine = series->querySubObject("Trendlines(int)",nbTrendLines);
        // 设定图标格式为 “散点图”，数字-4133来自 枚举变量 XlTrendlineType  : xlLogarithmic
        trendLine->setProperty("Type",-4133);       // XlTrendlineType  : xlLogarithmic
        trendLine->setProperty("Name","TrendLineName");
        trendLine->setProperty("DisplayEquation",true);
        //trendLine->setProperty("DisplayRSquared",true);

        QAxObject *dataLabel = trendLine->querySubObject("DataLabel");
        QString strFormula = dataLabel->property("Formula").toString();
        qDebug() << strFormula;         // "y = -9.113ln(x) + 78.016"

        getFormulaCoeffcient(strFormula,_cofA, _cofB);
        qDebug() << _cofA;
        qDebug() << _cofB;
    }
    */

    // 保存文件
    /*
    QString qstrFileName = QCoreApplication::applicationDirPath().append("/FCQ_");
    qstrFileName.append(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));
    qstrFileName.replace("/", "\\");
    //qDebug() << qstrFileName;
    //保存文件并退出
    //_curWorkbook->dynamicCall("SaveCopyAs(QString)",qstrFileName);
    _curWorkbook->dynamicCall("SaveAs(QString)",qstrFileName);
    */
}

template<typename T>
void print(QVector<T> source)
{
    for(auto num : source)
        qDebug() << num;
}
int Excel::addChart(const QString& sheetName)
{
//    QAxObject *excel = new QAxObject("Excel.Application");
    QAxObject *workbook  = this->excel->querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = workbook->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
    qDebug()<<QString("sheet count : ")<<sheet_count;
    QAxObject *worksheet = workbook->querySubObject("Worksheets(String&)", sheetName);
    qDebug() << worksheet->property("Name").toString();

//    worksheet->setProperty("Name", "Dati applicazione");
//    worksheet->querySubObject("Cells(1,1)")->dynamicCall("SetValue", "Serie");
//    worksheet->querySubObject("Cells(1,2)")->dynamicCall("SetValue", "Dati");

    // Selecting 3 columns will force charts.add to create 3 series !
    worksheet->dynamicCall("Select(void)"); // very important
    QAxObject *range = worksheet->querySubObject("Range(A1:B7)");
    range->dynamicCall("Select (void)");
    QAxObject *chart = workbook->querySubObject("Charts")->querySubObject("Add");
//    this->createDoc(QString("D:\\Qt\\chartAPI.html"), chart);
    QAxObject * series = chart->querySubObject("SeriesCollection");
    // qDebug() << series->property("Count");   // 3 !

    QAxObject * serie   = series->querySubObject("Item (int)", 1);
//    this->createDoc(QString("D:\\Qt\\serieAPI.html"), serie);
    QAxObject * xvalues = worksheet->querySubObject("Range(D8:D21)");
    QAxObject * yvalues = worksheet->querySubObject("Range(C8:C21)");
    serie->setProperty("XValues", xvalues->asVariant());
    serie->setProperty("Values",  yvalues->asVariant());


    chart->setProperty("Name", "Probability Chart");
//    xlXYScatter    -4169    Scatter.
    chart->setProperty("ChartType", -4169);
    chart->setProperty("HasTitle", true);
    QAxObject* chartTitle = chart->querySubObject("ChartTitle");
    chartTitle->setProperty("Text", "Lognormal Probability Plot"); // read-only or does not exist
    // XlCategoryLabelLevelCustom -2 (&HFFFFFFFE) Indicates literal data in the category labels.
//    chart->setProperty("CategoryLabelLevel", -2);   // !Exception
    chart->setProperty("BarShape", 0); // xlBox
    chart->setProperty("ChartColor", 2);
    chart->setProperty("DepthPercent", 100);
    chart->setProperty("DisplayBlanksAs", 0);// lxBox !
//    chart->setProperty("Elevation", 15);    // Exception
    chart->setProperty("GapDepth", 150);
    chart->setProperty("HasDataTable", false);
    chart->setProperty("HasLegend", true);
//    chart->setProperty("HeightPercent", 100);   // Exception
//    chart->setProperty("Perspective", 30);  // Exception
    chart->setProperty("Rotation", 20);
//    chart->dynamicCall("SetSeriesNameLevel(int)", -2);
//    int val = chart->property("SeriesNameLevel").toInt();
//    qDebug() << QString("SeriesNameLevel = %1").arg(val);
//    chart->setProperty("SeriesNameLevel", -2);// !xlSeriesNameLevelCustom
//    val = chart->property("SeriesNameLevel").toInt();
//    qDebug() << QString("SeriesNameLevel = %1").arg(val);
    chart->setProperty("Visible", -1);

    QAxObject* x_axis = chart->querySubObject("Axes(int)", 1);
    QAxObject* y_axis = chart->querySubObject("Axes(int)", 2);
    x_axis->setProperty("HasTitle", true);
    QAxObject* x_axisTitle = x_axis->querySubObject("AxisTitle");
    x_axisTitle->setProperty("Text", "Percentiles");
    x_axis->setProperty("HasMajorGridlines", false);
    x_axis->setProperty("HasMinorGridlines", false);
    y_axis->setProperty("HasTitle", true);
    QAxObject* y_axisTitle = y_axis->querySubObject("AxisTitle");
    y_axisTitle->setProperty("Text", "Concentrate");
    y_axis->setProperty("HasMajorGridlines", false);
    y_axis->setProperty("HasMinorGridlines", false);

//    serie = series->querySubObject("Item (int)", 2);
//    yvalues = worksheet->querySubObject("Range(C2:C9)");
//    serie->setProperty("XValues", xvalues->asVariant());
//    serie->setProperty("Values",  yvalues->asVariant());
    // 添加趋势线
    QAxObject *trendLines = serie->querySubObject("Trendlines()");
    if (trendLines) {
        trendLines->dynamicCall("Add()");
        int nbTrendLines = trendLines->property("Count").toInt();
        QAxObject *trendLine = serie->querySubObject("Trendlines(int)",nbTrendLines);
        // 设定图标格式为 “散点图”，数字-4132来自 枚举变量 XlTrendlineType  : xlLinear
        trendLine->setProperty("Type",-4132);       // XlTrendlineType  : xlLinear
        trendLine->setProperty("Name","TrendLineName");
        trendLine->setProperty("DisplayEquation",true);
        trendLine->setProperty("DisplayRSquared",true);

        QAxObject *dataLabel = trendLine->querySubObject("DataLabel");
        QString strFormula = dataLabel->property("Formula").toString();
        qDebug() << strFormula;         // "y = -9.113ln(x) + 78.016"

//        getFormulaCoeffcient(strFormula,_cofA, _cofB);
//        qDebug() << _cofA;
//        qDebug() << _cofB;
    }
    // 拷贝图片，参考 https://msdn.microsoft.com/en-us/library/office/ff841052.aspx
    // xlScreen = 1, xlPicture =-4147
    chart->dynamicCall("CopyPicture(Appearance, Format)", 1, -4147); //
    workbook->dynamicCall("SaveAs (const QString&)", "D:\\Qt\\a");
    workbook->dynamicCall("Close (Boolean)", false);
    excel->dynamicCall("Quit (void)");

    return 0;
}
