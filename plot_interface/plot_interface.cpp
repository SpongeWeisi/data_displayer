#include "../plot_interface/plot_interface.h"

PlotInterface::PlotInterface(QObject *parent) :
    QObject(parent)
{
    plotFocusedIndex = 0;
    graphFocusedIndex = 0;
    plotKey = 0;

    colorMap.insert(0,QPen(Qt::blue));
    colorMap.insert(1,QPen(Qt::red));
    colorMap.insert(2,QPen(Qt::darkGreen));
    colorMap.insert(3,QPen(Qt::darkYellow));
    colorMap.insert(4,QPen(Qt::cyan));
    colorMap.insert(5,QPen(Qt::darkGray));
    colorMap.insert(6,QPen(Qt::darkBlue));
    colorMap.insert(7,QPen(Qt::darkRed));
    colorMap.insert(8,QPen(Qt::yellow));
    colorMap.insert(9,QPen(Qt::green));
    colorMap.insert(10,QPen(Qt::darkCyan));
    colorMap.insert(11,QPen(Qt::darkMagenta));
    colorMap.insert(12,QPen(Qt::black));
}


QString PlotInterface::addNewPlot(QCustomPlot *customPlot,
                                  QString plotName,
                                  PackageInterface &packageInterface,
                                  int packIndex,
                                  int dataIndex,
                                  bool &ok)
{
    ok = false;

    if(packIndex + 1 > packageInterface.packageList.size())
        return "Package index overflow";

    if(dataIndex + 1 > packageInterface.packageList[packIndex].dataList.size())
        return "Data index overflow";

    if(customPlot->graphCount() > 0)
        return "Plot is not empty";

    ////////////////////////////////////////////////
    GraphInfo graphInfo;
    graphInfo.packageIndex = packIndex;
    graphInfo.dataIndex = dataIndex;
    graphInfo.Name = packageInterface.packageList[packIndex].dataList[dataIndex].dataName;
    graphInfo.colorIndex = 0;

    PlotInfo plotInfo;
    plotInfo.graphList.append(graphInfo);
    plotInfo.customPlot = customPlot;
    plotInfo.plotName = plotName;
    plotList.append(plotInfo);

    /////plot initial settings///////////////////////
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);

    QFont legendFont = QFont("Helvetica", 9);
    legendFont.setStyleStrategy(QFont::NoAntialias);
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setRowSpacing(-8);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    customPlot->yAxis->setLabel(plotName);

    customPlot->addGraph();
    customPlot->graph(0)->setPen(colorMap[graphInfo.colorIndex]);
    customPlot->graph(0)->setAntialiasedFill(false);
    customPlot->graph(0)->setName(graphInfo.Name);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ok = true;
    return QString("Add new plot OK, added data: <%1> in <%2>")
                    .arg(packageInterface.packageList[packIndex].dataList[dataIndex].dataName)
                    .arg(packageInterface.packageList[packIndex].packageName);
}

QString PlotInterface::addNewGraph(int plotIndex,
                                   PackageInterface &packageInterface,
                                   int packIndex,
                                   int dataIndex)
{
    if(plotIndex + 1> plotList.size())
        return "Plot index overflow";

    if(packIndex + 1 > packageInterface.packageList.size())
        return "Package index overflow";

    if(dataIndex + 1 > packageInterface.packageList[packIndex].dataList.size())
        return "Data index overflow";

    //add new graph
    int graphCount = plotList[plotIndex].customPlot->graphCount();
    if(graphCount >= 13)
        return "Too many graphs in one plot";

    ////////////////////////////////////////////////////
    GraphInfo graphInfo;
    graphInfo.packageIndex = packIndex;
    graphInfo.dataIndex = dataIndex;
    graphInfo.Name = packageInterface.packageList[packIndex].dataList[dataIndex].dataName;

    for(int cnt_color = 0;cnt_color < 13;cnt_color++)
    {
        bool unusedMinColorFinded = true;

        graphInfo.colorIndex = cnt_color;
        for(int cnt_graph = 0;cnt_graph < plotList[plotIndex].graphList.size();cnt_graph++)
        {
            if(graphInfo.colorIndex == plotList[plotIndex].graphList[cnt_graph].colorIndex)
            {
                unusedMinColorFinded = false;
                break;
            }
        }
        if(unusedMinColorFinded == true)
            break;
    }

    plotList[plotIndex].graphList.append(graphInfo);

    qDebug()<<"graph index"<<graphInfo.colorIndex;

    for(int cnt = 0;cnt < plotList[plotIndex].graphList.size();cnt++)
        qDebug()<<"list index"<<plotList[plotIndex].graphList[cnt].colorIndex;

    ////////////////////////////////////////////////////
    plotList[plotIndex].customPlot->addGraph();
    plotList[plotIndex].customPlot->graph(graphCount)->setPen(colorMap[graphInfo.colorIndex]);
    plotList[plotIndex].customPlot->graph(graphCount)->setAntialiasedFill(false);
    plotList[plotIndex].customPlot->graph(graphCount)->setName(graphInfo.Name);

    qDebug()<<"graph count"<<graphCount;

    return QString("Add new graph OK, added data: <%1> in <%2>")
            .arg(packageInterface.packageList[packIndex].dataList[dataIndex].dataName)
            .arg(packageInterface.packageList[packIndex].packageName);
}

QString PlotInterface::removePlot(int plotIndex, bool &ok)
{
    ok = false;
    if(plotIndex + 1> plotList.size())
        return "Plot index overflow";

    plotList[plotIndex].customPlot->hide();
    plotList.removeAt(plotIndex);

    ok = true;
    return "Remove plot OK";
}

QString PlotInterface::removeGraph(int plotIndex, int dataIndex)
{
    if(plotIndex + 1 > plotList.size())
        return "Plot index overflow";

    if(dataIndex + 1 > plotList[plotIndex].graphList.size())
        return "Graph index overflow";

    plotList[plotIndex].graphList.removeAt(dataIndex);
    plotList[plotIndex].customPlot->removeGraph(dataIndex);

    return "Remove graph OK";
}

QString PlotInterface::addPlotData(PackageInterface &packageInterface, int plotPeriod)
{
    if(plotList.isEmpty())
        return "Plot list is empty";


    plotKey += ((float)plotPeriod)/1000;//50ms
    for(int cnt = 0;cnt < plotList.size();cnt++)
    {
        for(int graph_cnt = 0;graph_cnt < plotList[cnt].graphList.size();graph_cnt++)
        {
            int packIndex = plotList[cnt].graphList[graph_cnt].packageIndex;
            int dataIndex = plotList[cnt].graphList[graph_cnt].dataIndex;
            double value = packageInterface.packageList[packIndex].dataList[dataIndex].data.toDouble();
            plotList[cnt].customPlot->graph(graph_cnt)->addData(plotKey, value);

            plotList[cnt].customPlot->graph(graph_cnt)->rescaleValueAxis(true);
        }
        plotList[cnt].customPlot->rescaleAxes(true);
        plotList[cnt].customPlot->xAxis->setRange(plotKey, 10, Qt::AlignRight);
        plotList[cnt].customPlot->replot();
    }

    return "Add plot data OK";
}

QString PlotInterface::updatePlot(void)
{
    for(int cnt = 0;cnt < plotList.size();cnt++)
    {
        plotList[cnt].customPlot->replot();
    }

    return "Update plot OK";
}

QString PlotInterface::updatePlotTable(QTableWidget *table)
{
    table->clearContents();
    table->setRowCount(plotList.size());
    table->setColumnCount(1);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    for(int row_cnt = 0;row_cnt < plotList.size();row_cnt++)
    {
        table->setItem(row_cnt,0,new QTableWidgetItem(plotList[row_cnt].plotName));
        for(int cnt = 0;cnt < plotList[row_cnt].graphList.size();cnt++)
        {
            //qDebug()<<"graph list size"<<plotList[row_cnt].graphList.size();
            if(table->columnCount() < plotList[row_cnt].graphList.size()+1)
            {
                table->setColumnCount(plotList[row_cnt].graphList.size()+1);
            }

            table->setItem(row_cnt,cnt+1,new QTableWidgetItem(plotList[row_cnt].graphList[cnt].Name));
        }
    }

    table->resizeRowsToContents();
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    return "Update plot table OK";
}

QString PlotInterface::clearPlot(void)
{
    for(int cnt = 0;cnt < plotList.size();cnt++)
    {
        for(int graphCnt = 0;graphCnt < plotList[cnt].graphList.size();graphCnt++)
        {
            plotList[cnt].customPlot->graph(graphCnt)->clearData();
        }
        plotList[cnt].customPlot->replot();
    }
    plotKey = 0;

    return "Clear plot OK";
}
