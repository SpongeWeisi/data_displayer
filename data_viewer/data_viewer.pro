#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T16:39:29
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = data_viewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../QCustomPlot/qcustomplot.cpp \
    ../plot_interface/plot_interface.cpp \
    ../package_interface/package_interface.cpp \
    com_settingsdialog.cpp \
    ../QChart/chartview.cpp

HEADERS  += mainwindow.h \
    ../QCustomPlot/qcustomplot.h \
    ../plot_interface/plot_interface.h \
    ../package_interface/package_interface.h \
    com_settingsdialog.h \
    ../QChart/chartview.h

FORMS    += mainwindow.ui \
    settingsdialog.ui
