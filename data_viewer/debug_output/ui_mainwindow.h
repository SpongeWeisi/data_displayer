/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *output;
    QTextEdit *comPrint;
    QVBoxLayout *plotLayout;
    QVBoxLayout *leftLayout;
    QGridLayout *fileLayout;
    QPushButton *readConfigFile;
    QPushButton *createConfigFile;
    QPushButton *openCom;
    QPushButton *configCom;
    QTableWidget *packageTable;
    QTableWidget *dataTable;
    QGridLayout *dataLayout;
    QPushButton *sendData;
    QPushButton *readData;
    QTableWidget *plotTable;
    QGridLayout *plotButtonLayout;
    QPushButton *addPlot;
    QPushButton *addGraph;
    QPushButton *removeGraph;
    QPushButton *removePlot;
    QPushButton *startPlot;
    QPushButton *clearPlot;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(920, 679);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        output = new QTextEdit(centralWidget);
        output->setObjectName(QStringLiteral("output"));

        horizontalLayout->addWidget(output);

        comPrint = new QTextEdit(centralWidget);
        comPrint->setObjectName(QStringLiteral("comPrint"));

        horizontalLayout->addWidget(comPrint);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 1);

        plotLayout = new QVBoxLayout();
        plotLayout->setSpacing(6);
        plotLayout->setObjectName(QStringLiteral("plotLayout"));

        gridLayout_2->addLayout(plotLayout, 0, 1, 1, 1);

        leftLayout = new QVBoxLayout();
        leftLayout->setSpacing(3);
        leftLayout->setObjectName(QStringLiteral("leftLayout"));
        leftLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        leftLayout->setContentsMargins(-1, -1, 0, -1);
        fileLayout = new QGridLayout();
        fileLayout->setSpacing(6);
        fileLayout->setObjectName(QStringLiteral("fileLayout"));
        fileLayout->setVerticalSpacing(3);
        readConfigFile = new QPushButton(centralWidget);
        readConfigFile->setObjectName(QStringLiteral("readConfigFile"));

        fileLayout->addWidget(readConfigFile, 0, 0, 1, 1);

        createConfigFile = new QPushButton(centralWidget);
        createConfigFile->setObjectName(QStringLiteral("createConfigFile"));

        fileLayout->addWidget(createConfigFile, 0, 1, 1, 1);

        openCom = new QPushButton(centralWidget);
        openCom->setObjectName(QStringLiteral("openCom"));

        fileLayout->addWidget(openCom, 1, 0, 1, 1);

        configCom = new QPushButton(centralWidget);
        configCom->setObjectName(QStringLiteral("configCom"));

        fileLayout->addWidget(configCom, 1, 1, 1, 1);


        leftLayout->addLayout(fileLayout);

        packageTable = new QTableWidget(centralWidget);
        packageTable->setObjectName(QStringLiteral("packageTable"));

        leftLayout->addWidget(packageTable);

        dataTable = new QTableWidget(centralWidget);
        dataTable->setObjectName(QStringLiteral("dataTable"));

        leftLayout->addWidget(dataTable);

        dataLayout = new QGridLayout();
        dataLayout->setSpacing(6);
        dataLayout->setObjectName(QStringLiteral("dataLayout"));
        dataLayout->setVerticalSpacing(3);
        sendData = new QPushButton(centralWidget);
        sendData->setObjectName(QStringLiteral("sendData"));

        dataLayout->addWidget(sendData, 0, 1, 1, 1);

        readData = new QPushButton(centralWidget);
        readData->setObjectName(QStringLiteral("readData"));

        dataLayout->addWidget(readData, 0, 0, 1, 1);


        leftLayout->addLayout(dataLayout);

        plotTable = new QTableWidget(centralWidget);
        plotTable->setObjectName(QStringLiteral("plotTable"));

        leftLayout->addWidget(plotTable);

        plotButtonLayout = new QGridLayout();
        plotButtonLayout->setSpacing(6);
        plotButtonLayout->setObjectName(QStringLiteral("plotButtonLayout"));
        plotButtonLayout->setVerticalSpacing(3);
        addPlot = new QPushButton(centralWidget);
        addPlot->setObjectName(QStringLiteral("addPlot"));

        plotButtonLayout->addWidget(addPlot, 0, 0, 1, 1);

        addGraph = new QPushButton(centralWidget);
        addGraph->setObjectName(QStringLiteral("addGraph"));

        plotButtonLayout->addWidget(addGraph, 1, 0, 1, 1);

        removeGraph = new QPushButton(centralWidget);
        removeGraph->setObjectName(QStringLiteral("removeGraph"));

        plotButtonLayout->addWidget(removeGraph, 1, 1, 1, 1);

        removePlot = new QPushButton(centralWidget);
        removePlot->setObjectName(QStringLiteral("removePlot"));

        plotButtonLayout->addWidget(removePlot, 0, 1, 1, 1);

        startPlot = new QPushButton(centralWidget);
        startPlot->setObjectName(QStringLiteral("startPlot"));

        plotButtonLayout->addWidget(startPlot, 1, 2, 1, 1);

        clearPlot = new QPushButton(centralWidget);
        clearPlot->setObjectName(QStringLiteral("clearPlot"));

        plotButtonLayout->addWidget(clearPlot, 0, 2, 1, 1);


        leftLayout->addLayout(plotButtonLayout);

        leftLayout->setStretch(0, 1);
        leftLayout->setStretch(1, 2);
        leftLayout->setStretch(2, 5);
        leftLayout->setStretch(3, 1);
        leftLayout->setStretch(4, 2);
        leftLayout->setStretch(5, 1);

        gridLayout_2->addLayout(leftLayout, 0, 0, 2, 1);

        gridLayout_2->setRowStretch(0, 4);
        gridLayout_2->setRowStretch(1, 1);
        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 4);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        readConfigFile->setText(QApplication::translate("MainWindow", "read file", 0));
        createConfigFile->setText(QApplication::translate("MainWindow", "create file", 0));
        openCom->setText(QApplication::translate("MainWindow", "open com", 0));
        configCom->setText(QApplication::translate("MainWindow", "config com", 0));
        sendData->setText(QApplication::translate("MainWindow", "send data", 0));
        readData->setText(QApplication::translate("MainWindow", "read data", 0));
        addPlot->setText(QApplication::translate("MainWindow", "new plot", 0));
        addGraph->setText(QApplication::translate("MainWindow", "new graph", 0));
        removeGraph->setText(QApplication::translate("MainWindow", "remove graph", 0));
        removePlot->setText(QApplication::translate("MainWindow", "remove plot", 0));
        startPlot->setText(QApplication::translate("MainWindow", "start plot", 0));
        clearPlot->setText(QApplication::translate("MainWindow", "clear plot", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
