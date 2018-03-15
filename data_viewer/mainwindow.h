#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "../package_interface/package_interface.h"
#include "../plot_interface/plot_interface.h"
#include "../QCustomPlot/qcustomplot.h"
#include "com_settingsdialog.h"

#include "../QChart/chartview.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>

#define ARRAY_SIZE 560

namespace Ui {
class MainWindow;
}

class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    PackageInterface package;
    PlotInterface plot;

    QTimer plotTimer;
    bool plotTimerStart;
    int plotPeriod;

    void addNewPlot(int packIndex, int dataIndex);
    void addOutputText(QString str);

    //serial
    SettingsDialog *comSettings;
    QSerialPort *serial;
    QByteArray comBuffer;

    //array
    int arraySize;

    //QChartt
    ChartView *chartView;
    QMainWindow arrayWindow;

private slots:
    /*******************************************/
    void plotUpdate(void);

    void readComBuffer();
    void handleError(QSerialPort::SerialPortError error);
    /*******************************************/

    void on_createConfigFile_clicked();

    void on_readConfigFile_clicked();

    void on_readData_clicked();

    void on_addPlot_clicked();

    void on_addGraph_clicked();

    void on_removePlot_clicked();

    void on_removeGraph_clicked();

    void on_startPlot_clicked();

    void on_packageTable_clicked(const QModelIndex &index);

    void on_dataTable_clicked(const QModelIndex &index);

    void on_plotTable_clicked(const QModelIndex &index);

    void on_configCom_clicked();

    void on_openCom_clicked();

    void on_sendData_clicked();

    void on_clearPlot_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
