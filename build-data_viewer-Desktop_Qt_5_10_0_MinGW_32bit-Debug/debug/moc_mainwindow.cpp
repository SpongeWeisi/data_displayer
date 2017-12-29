/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../data_viewer/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[416];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "plotUpdate"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "readComBuffer"
QT_MOC_LITERAL(4, 37, 11), // "handleError"
QT_MOC_LITERAL(5, 49, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(6, 78, 5), // "error"
QT_MOC_LITERAL(7, 84, 27), // "on_createConfigFile_clicked"
QT_MOC_LITERAL(8, 112, 25), // "on_readConfigFile_clicked"
QT_MOC_LITERAL(9, 138, 19), // "on_readData_clicked"
QT_MOC_LITERAL(10, 158, 18), // "on_addPlot_clicked"
QT_MOC_LITERAL(11, 177, 19), // "on_addGraph_clicked"
QT_MOC_LITERAL(12, 197, 21), // "on_removePlot_clicked"
QT_MOC_LITERAL(13, 219, 22), // "on_removeGraph_clicked"
QT_MOC_LITERAL(14, 242, 20), // "on_startPlot_clicked"
QT_MOC_LITERAL(15, 263, 23), // "on_packageTable_clicked"
QT_MOC_LITERAL(16, 287, 5), // "index"
QT_MOC_LITERAL(17, 293, 20), // "on_dataTable_clicked"
QT_MOC_LITERAL(18, 314, 20), // "on_plotTable_clicked"
QT_MOC_LITERAL(19, 335, 20), // "on_configCom_clicked"
QT_MOC_LITERAL(20, 356, 18), // "on_openCom_clicked"
QT_MOC_LITERAL(21, 375, 19), // "on_sendData_clicked"
QT_MOC_LITERAL(22, 395, 20) // "on_clearPlot_clicked"

    },
    "MainWindow\0plotUpdate\0\0readComBuffer\0"
    "handleError\0QSerialPort::SerialPortError\0"
    "error\0on_createConfigFile_clicked\0"
    "on_readConfigFile_clicked\0on_readData_clicked\0"
    "on_addPlot_clicked\0on_addGraph_clicked\0"
    "on_removePlot_clicked\0on_removeGraph_clicked\0"
    "on_startPlot_clicked\0on_packageTable_clicked\0"
    "index\0on_dataTable_clicked\0"
    "on_plotTable_clicked\0on_configCom_clicked\0"
    "on_openCom_clicked\0on_sendData_clicked\0"
    "on_clearPlot_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    1,  106,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    0,  113,    2, 0x08 /* Private */,
      12,    0,  114,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    1,  117,    2, 0x08 /* Private */,
      17,    1,  120,    2, 0x08 /* Private */,
      18,    1,  123,    2, 0x08 /* Private */,
      19,    0,  126,    2, 0x08 /* Private */,
      20,    0,  127,    2, 0x08 /* Private */,
      21,    0,  128,    2, 0x08 /* Private */,
      22,    0,  129,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void, QMetaType::QModelIndex,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->plotUpdate(); break;
        case 1: _t->readComBuffer(); break;
        case 2: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 3: _t->on_createConfigFile_clicked(); break;
        case 4: _t->on_readConfigFile_clicked(); break;
        case 5: _t->on_readData_clicked(); break;
        case 6: _t->on_addPlot_clicked(); break;
        case 7: _t->on_addGraph_clicked(); break;
        case 8: _t->on_removePlot_clicked(); break;
        case 9: _t->on_removeGraph_clicked(); break;
        case 10: _t->on_startPlot_clicked(); break;
        case 11: _t->on_packageTable_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 12: _t->on_dataTable_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->on_plotTable_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 14: _t->on_configCom_clicked(); break;
        case 15: _t->on_openCom_clicked(); break;
        case 16: _t->on_sendData_clicked(); break;
        case 17: _t->on_clearPlot_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
