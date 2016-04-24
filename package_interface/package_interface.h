#ifndef PACKAGE_INTERFACE_H
#define PACKAGE_INTERFACE_H

#include <QtCore>

#include <QTableWidget>
#include <QHeaderView>

#define DATA_COLUMN_INDEX 3

struct DataInfo
{
    QVariant data;
    QString dataName;
    QString dataTypeName;
    int dataSize;
};

struct PackageInfo
{
    QString packageName;
    int packageId;
    int packageSize;
    int packageCount;

    QList<struct DataInfo> dataList;
};


class PackageInterface : public QObject
{
    //Q_OBJECT
public:
    explicit PackageInterface(QObject *parent = 0);

    QList<struct PackageInfo> packageList;

    QMap<QString, int> dataSignMap;
    QMap<QString, int> dataSizeMap;
    QMap<int, int> packageIdMap;

    /////////////////////////////////////////////////////////
    QString readConfigFile(QSettings &settings);
    QString createConfigFile(QSettings &settings);
    QString readPackage(int packId, char *p_pack, int size);

    //////////////////////////////////////////////////////////
    QString setTableFormat(QTableWidget *table, QString table_type);

    QString updatePackageTable(QTableWidget *table);
    void updatePackageCountColumn(QTableWidget *table, int packIndex);
    QString updateDataTable(QTableWidget *table, int packIndx);
    void updateDataColumn(QTableWidget *table, int packIndex);

    int packageFocusedIndex;
    int dataFocusedIndex;
    bool packageModifyLock;
    QString modifyDataValue(QString &value, int data_index);

    //////////////////////////////////////////////////////////
    QString generatePackage(QByteArray &dataArray, int package_id);
};

#endif // PACKAGE_INTERFACE_H
