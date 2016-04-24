#ifndef PLOT_INTERFACE_H
#define PLOT_INTERFACE_H

#include <QtCore>
#include <qnamespace.h>
#include <QTableWidget>
#include <QHeaderView>

#include "../QCustomPlot/qcustomplot.h"
#include "../package_interface/package_interface.h"


struct GraphInfo
{
    QString Name;
    int packageIndex;
    int dataIndex;
    int colorIndex;
};

struct PlotInfo
{
    QList<GraphInfo> graphList;
    QCustomPlot *customPlot;
    QString plotName;

};

class PlotInterface : public QObject
{
    //Q_OBJECT
public:
    explicit PlotInterface(QObject *parent = 0);

    int plotFocusedIndex;
    int graphFocusedIndex;
    QList<PlotInfo> plotList;

    QMap<int,QPen> colorMap;

    float plotKey;

    //////////////////////////////////////////////
    QString addNewPlot(QCustomPlot *customPlot,
                       QString plotName,
                       PackageInterface &packageInterface,
                       int packIndex,
                       int dataIndex,
                       bool &ok);
    QString addNewGraph(int plotIndex,
                        PackageInterface &packageInterface,
                        int packIndex,
                        int dataIndex);
    QString removePlot(int plotIndex, bool &ok);
    QString removeGraph(int plotIndex, int dataIndex);
    QString updatePlot(void);
    QString clearPlot(void);
    QString addPlotData(PackageInterface &packageInterface);
    QString updatePlotTable(QTableWidget *table);
};

#endif // PLOT_INTERFACE_H
