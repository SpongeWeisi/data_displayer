#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*********************************************/
    package.setTableFormat(ui->packageTable,"package");
    package.setTableFormat(ui->dataTable,"data");

    ui->output->setReadOnly(true);
    ui->output->document()->setMaximumBlockCount(20);
    ui->output->ensureCursorVisible();
    ui->comPrint->setReadOnly(true);
    ui->comPrint->document()->setMaximumBlockCount(20);
    ui->comPrint->ensureCursorVisible();

    /**********************************************/
    connect(&plotTimer, SIGNAL(timeout()), this, SLOT(plotUpdate()));
    plotTimerStart = false;

    /**********************************************/
    serial = new QSerialPort(this);
    comSettings = new SettingsDialog;
    connect(serial, SIGNAL(readyRead()), this, SLOT(readComBuffer()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewPlot(int packIndex, int dataIndex)
{
    static int plotNameCount = 1;

    QString plotName = QString("Plot %1").arg(plotNameCount);

    QCustomPlot *newPlot = new QCustomPlot();

    bool ok = false;
    addOutputText(plot.addNewPlot(newPlot,plotName,package,packIndex,dataIndex,ok));

    if(ok == true)
    {
        plotNameCount++;
        ui->plotLayout->addWidget(newPlot);
    }
    else
        delete newPlot;
}

void MainWindow::addOutputText(QString str)
{
    QTextCursor cursor = ui->output->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->output->setTextCursor(cursor);
    ui->output->append(str);
}

void MainWindow::plotUpdate(void)
{
    plot.addPlotData(package);
}

void MainWindow::readComBuffer()
{
    comBuffer.append(serial->readAll());

    while(comBuffer.isEmpty() == false)
    {
        unsigned char data = comBuffer[0];
        unsigned char size;

        if(data == 0x55)
        {
            //real package size = header + id + data + checksum = 1 + 1 + size + 1 = size + 3
            size = package.packageList[package.packageIdMap[comBuffer[1]]].packageSize;
            if(size + 3 > comBuffer.size())
            {
                break;
            }
            else// size + 3 <= comBuffer.size()
            {
                unsigned char checksum = 0;

                for(int count = 0;count < size + 3 - 1;count++)
                {
                    checksum += (unsigned char)comBuffer[count];
                }

                if(checksum == (unsigned char)comBuffer[size + 3 - 1])
                {
                    char *p_pack = (char*)comBuffer.constData();
                    package.readPackage(comBuffer[1],(p_pack+2),size);

                    package.updateDataColumn(ui->dataTable,package.packageIdMap[comBuffer[1]]);
                    package.updatePackageCountColumn(ui->packageTable,package.packageIdMap[comBuffer[1]]);
                }

                comBuffer.remove(0,size+3);
            }
        }
        else
        {
            comBuffer.remove(0,1);
        }
    }
}

void MainWindow::on_createConfigFile_clicked()
{
    QSettings settings("./config/config_template.ini",QSettings::IniFormat);
    qDebug()<<package.createConfigFile(settings);
}

void MainWindow::on_readConfigFile_clicked()
{
    QSettings settings("./config/config.ini",QSettings::IniFormat);
    qDebug()<<package.readConfigFile(settings);

    package.setTableFormat(ui->packageTable,"package");
    package.updatePackageTable(ui->packageTable);

    package.setTableFormat(ui->dataTable,"data");
    package.updateDataTable(ui->dataTable,0);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        serial->close();
    }
}

void MainWindow::on_readData_clicked()
{
    char tx[3] = {(char)0x55,(char)0xff,0};

    tx[2] = (char)package.packageList[package.packageFocusedIndex].packageId;
    serial->write(tx,3);
}

void MainWindow::on_addPlot_clicked()
{
    addNewPlot(package.packageFocusedIndex,package.dataFocusedIndex);

    plot.updatePlotTable(ui->plotTable);
}

void MainWindow::on_addGraph_clicked()
{
    addOutputText(plot.addNewGraph(plot.plotFocusedIndex,
                               package,
                               package.packageFocusedIndex,
                               package.dataFocusedIndex));

    plot.updatePlotTable(ui->plotTable);
    plot.updatePlot();
}

void MainWindow::on_removePlot_clicked()
{
    //remove plot
    if(plot.plotList.isEmpty())
        return;

    if(ui->plotLayout->count() - 1 < plot.plotFocusedIndex)
        return;

    bool ok = false;
    QCustomPlot *p_plot = plot.plotList[0].customPlot;

    plot.removePlot(plot.plotFocusedIndex,ok);
    if(ok == true)
    {
        ui->plotLayout->removeItem(ui->plotLayout->itemAt(plot.plotFocusedIndex));
        delete p_plot;
    }

    //update all plot
    plot.updatePlotTable(ui->plotTable);
    plot.updatePlot();
}

void MainWindow::on_removeGraph_clicked()
{
    //remove graph
    plot.removeGraph(plot.plotFocusedIndex,plot.graphFocusedIndex);

    //update plot
    plot.updatePlotTable(ui->plotTable);
    plot.updatePlot();
}


void MainWindow::on_startPlot_clicked()
{
    if(plotTimerStart == false)
    {
        plotTimerStart = true;
        plotTimer.start(50);
        ui->startPlot->setText("stop plot");

        ui->removePlot->setEnabled(false);
        ui->removeGraph->setEnabled(false);
        ui->addPlot->setEnabled(false);
        ui->addGraph->setEnabled(false);
    }
    else
    {
        plotTimerStart = false;
        plotTimer.stop();
        ui->startPlot->setText("start plot");

        ui->removePlot->setEnabled(true);
        ui->removeGraph->setEnabled(true);
        ui->addPlot->setEnabled(true);
        ui->addGraph->setEnabled(true);
    }
}

void MainWindow::on_packageTable_clicked(const QModelIndex &index)
{
    addOutputText(package.updateDataTable(ui->dataTable,index.row()));
}


void MainWindow::on_dataTable_clicked(const QModelIndex &index)
{
    package.dataFocusedIndex = index.row();
    addOutputText(QString("Selected data: <%1> in package <%2>")
                  .arg(package.packageList[package.packageFocusedIndex].dataList[package.dataFocusedIndex].dataName)
                  .arg(package.packageList[package.packageFocusedIndex].packageName));
}

void MainWindow::on_plotTable_clicked(const QModelIndex &index)
{
    qDebug()<<index.row()<<index.column();

    if(index.column() == 0)
    {
        if(index.row() < plot.plotList.size())
        {
            plot.plotFocusedIndex = index.row();
            addOutputText(QString("Selected plot: <%1>")
                          .arg(plot.plotList[plot.plotFocusedIndex].plotName));
        }
    }
    else
    {
        if(index.row() < plot.plotList.size())
        {
            plot.plotFocusedIndex = index.row();
            if(index.column() - 1 < plot.plotList[plot.plotFocusedIndex].graphList.size())
            {
                plot.graphFocusedIndex = index.column() - 1;
                addOutputText(QString("Selected graph: <%1> in <%2>")
                              .arg(plot.plotList[plot.plotFocusedIndex].graphList[plot.graphFocusedIndex].Name)
                              .arg(plot.plotList[plot.plotFocusedIndex].plotName));
            }
        }
    }
}

void MainWindow::on_configCom_clicked()
{
    comSettings->show();
}

void MainWindow::on_openCom_clicked()
{
    if(serial->isOpen() == false)
    {
        SettingsDialog::Settings p = comSettings->settings();
        serial->setPortName(p.name);
        serial->setBaudRate(p.baudRate);
        serial->setDataBits(p.dataBits);
        serial->setParity(p.parity);
        serial->setStopBits(p.stopBits);
        serial->setFlowControl(p.flowControl);
        if (serial->open(QIODevice::ReadWrite)) {
            addOutputText(QString("Connected to %1, baudrate = %2")
                                  .arg(p.name).arg(p.stringBaudRate));
        } else {
            QMessageBox::critical(this, tr("Error"), serial->errorString());
        }

        ui->openCom->setText("close com");
    }
    else
    {
        serial->close();
        ui->openCom->setText("open com");
        addOutputText(QString("Com closed"));
    }
}

void MainWindow::on_sendData_clicked()
{
    //////////////////////////////////////////////
    for(int cnt = 0;cnt < package.packageList[package.packageFocusedIndex].dataList.size();cnt++)
    {
        QString value = ui->dataTable->item(cnt,2)->text();
        package.modifyDataValue(value, cnt);
    }

    //////////////////////////////////////////////
    QByteArray tx;

    qDebug()<<package.generatePackage(tx,package.packageFocusedIndex);
    if(serial->isOpen())
    {
        char tx_header[1];
        char tx_id[1];
        unsigned char checksum[1]= {0};

        tx_header[0] = 0x55;
        tx_id[0] = package.packageList[package.packageFocusedIndex].packageId;

        serial->write(tx_header,1);
        serial->write(tx_id,1);
        serial->write(tx.constData(),package.packageList[package.packageFocusedIndex].packageSize);

        checksum[0] += tx_header[0];
        checksum[0] += tx_id[0];
        for(int count = 0;count < tx.size();count++)
        {
            checksum[0] += (unsigned char)tx.constData()[count];
        }
        serial->write((char*)checksum,1);

        qDebug()<<"comm send";
    }
}

void MainWindow::on_clearPlot_clicked()
{
    plot.clearPlot();
}
