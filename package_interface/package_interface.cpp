#include "package_interface.h"

PackageInterface::PackageInterface(QObject *parent) :
    QObject(parent)
{
    dataSizeMap.insert("uint8_t",1);
    dataSizeMap.insert("int8_t",1);
    dataSizeMap.insert("uint16_t",2);
    dataSizeMap.insert("int16_t",2);
    dataSizeMap.insert("uint32_t",4);
    dataSizeMap.insert("int32_t",4);
    dataSizeMap.insert("float",4);

    dataSignMap.insert("uint8_t",QVariant::UInt);
    dataSignMap.insert("int8_t",QVariant::Int);
    dataSignMap.insert("uint16_t",QVariant::UInt);
    dataSignMap.insert("int16_t",QVariant::Int);
    dataSignMap.insert("uint32_t",QVariant::UInt);
    dataSignMap.insert("int32_t",QVariant::Int);
    dataSignMap.insert("float",QVariant::Double);

    packageFocusedIndex = 0;
    dataFocusedIndex = 0;
    packageModifyLock = false;
}


QString PackageInterface::readConfigFile(QSettings &settings)
{
    if(settings.fileName().isNull())
        return "Config file path is NULL";

    QStringList groupList = settings.childGroups();

    if(groupList.size() == 0)
        return "Package number is 0!";

    for(int pack_cnt = 0;pack_cnt < groupList.size();pack_cnt++)
    {
        settings.beginGroup(groupList[pack_cnt]);

        if(settings.childKeys().size() == 0)
            return "Data num is 0!";

        settings.endGroup();
    }

    if(packageModifyLock == true)
        return "Package is locked";
    packageModifyLock = true;

    packageList.clear();
    packageIdMap.clear();

    for(int pack_cnt = 0;pack_cnt < groupList.size();pack_cnt++)
    {
        struct PackageInfo packageInfo;

        packageInfo.packageName = groupList[pack_cnt];
        packageInfo.packageSize = 0;
        packageInfo.packageCount = 0;

        //////////////////////////////////////////////////////////////
        settings.beginGroup(groupList[pack_cnt]);
        QStringList keyList = settings.childKeys();

        packageInfo.packageId = settings.value(keyList[keyList.size()-1]).toInt();

        for(int data_cnt = 0;data_cnt < keyList.size() - 1;data_cnt++)
        {
            struct DataInfo dataInfo;
//            int dataNameMidCount = 0;
//            QChar bottomLine = '_';

//            for(int dataNameMidCount = 0;dataNameMidCount < keyList[data_cnt].size();dataNameMidCount++)
//            {
//                if(keyList[data_cnt].at(dataNameMidCount) == bottomLine)
//                    break;
//            }
            dataInfo.dataName = keyList[data_cnt].mid(3);
            dataInfo.dataTypeName = settings.value(keyList[data_cnt]).toString();

            qDebug()<<dataInfo.dataName<<dataInfo.dataTypeName;

            if(dataSignMap.contains(settings.value(keyList[data_cnt]).toString()))
            {
                dataInfo.data.setValue(0);
                bool ret = dataInfo.data.convert(dataSignMap[settings.value(keyList[data_cnt]).toString()]);

                if(ret == false)
                {
                    packageList.clear();
                    packageModifyLock = false;
                    return QString("Data type convert fail, package ID = %1, data index = %2").arg(packageInfo.packageId).arg(data_cnt);
                }
            }
            else
            {
                packageList.clear();
                packageModifyLock = false;
                return QString("Undefined data type, package ID = %1, data index = %2").arg(packageInfo.packageId).arg(data_cnt);
            }

            if(dataSizeMap.contains(settings.value(keyList[data_cnt]).toString()))
            {
                dataInfo.dataSize = dataSizeMap[settings.value(keyList[data_cnt]).toString()];
            }
            else
            {
                packageList.clear();
                packageModifyLock = false;
                return QString("Undefined data type, package ID = %1, data index = %2").arg(packageInfo.packageId).arg(data_cnt);
            }

            packageInfo.packageSize += dataInfo.dataSize;
            packageInfo.dataList.append(dataInfo);
        }
        settings.endGroup();

        ///////////////////////////////////////////////////////////////
        packageIdMap.insert(packageInfo.packageId,pack_cnt);
        packageList.append(packageInfo);
    }

    // for debug /////////////////////////////////////////////////////////////////////////////////
    for(int pack_cnt = 0;pack_cnt < packageList.size();pack_cnt++)
    {
        qDebug()<<packageList[pack_cnt].packageName<<packageList[pack_cnt].packageId
               <<packageList[pack_cnt].packageSize;


        for(int data_cnt = 0;data_cnt < packageList[pack_cnt].dataList.size();data_cnt++)
        {
            qDebug()<<packageList[pack_cnt].dataList[data_cnt].data.toInt()
                   <<packageList[pack_cnt].dataList[data_cnt].dataName
                  <<packageList[pack_cnt].dataList[data_cnt].dataSize
                 <<packageList[pack_cnt].dataList[data_cnt].data.typeName();
        }
    }

    packageModifyLock = false;
    return "Read congfig file OK";
}

QString PackageInterface::createConfigFile(QSettings &settings)
{
    if(settings.fileName().isEmpty())
        return "Config file path is empty";

    settings.setValue("p1/ID", 1);
    settings.setValue("p1/1_d7", QString("uint8_t"));
    settings.setValue("p1/2_d2", QString("int8_t"));
    settings.setValue("p1/3_d3", QString("uint16_t"));
    settings.setValue("p1/4_d4", QString("int16_t"));
    settings.setValue("p1/5_d5", QString("uint32_t"));
    settings.setValue("p1/6_d6", QString("int32_t"));
    settings.setValue("p1/7_d1", QString("float"));

    settings.setValue("p2/ID", 2);
    settings.setValue("p2/1_d3", QString("float"));
    settings.setValue("p2/2_d2", QString("float"));
    settings.setValue("p2/3_d1", QString("float"));
    settings.setValue("p2/4_d4", QString("float"));
    settings.setValue("p2/5_d5", QString("float"));
    settings.setValue("p2/6_d6", QString("float"));


    return "Create congfig file OK";
}

QString PackageInterface::readPackage(int packId, char *p_pack, int size)
{
    if(packageList.isEmpty())
        return "There is no package info";

    if(packageIdMap.isEmpty())
        return "Package ID map is empty";

    if(packageIdMap.contains(packId) == false)
        return QString("Cannot find package ID = %1").arg(packId);

    if(packageList[packageIdMap[packId]].packageSize != size)
        return QString("Package size if not match, package ID = %1\n").arg(packId);

    if(packageModifyLock == true)
        return "Package is locked";
    packageModifyLock = true;

    struct PackageInfo &packageInfo = packageList[packageIdMap[packId]];

    packageInfo.packageCount++;

    int dataNum = packageInfo.dataList.size();
    int dataOffset = 0;

    /////for debug//////////////////////////////////////////////////////////////////
//    for(int cnt = 0;cnt < dataNum;cnt++)
//    {
//        qDebug()<<packageList[packageIdMap[packId]].dataList[cnt].dataName
//                <<packageList[packageIdMap[packId]].dataList[cnt].data.toString()
//                <<packageList[packageIdMap[packId]].dataList[cnt].data.typeName();
//    }

    for(int cnt = 0;cnt < dataNum;cnt++)
    {
        struct DataInfo &dataInfo = packageInfo.dataList[cnt];

        if(dataInfo.data.type() == QVariant::UInt)
        {
            if(dataInfo.dataSize == sizeof(unsigned char))
            {
                unsigned char value = *(unsigned char*)(p_pack + dataOffset);
                dataInfo.data.setValue((unsigned int)value);
            }
            else if(dataInfo.dataSize == sizeof(unsigned short))
            {
                unsigned short value = *(unsigned short*)(p_pack + dataOffset);
                dataInfo.data.setValue((unsigned int)value);
            }
            else if(dataInfo.dataSize == sizeof(unsigned int))
            {
                unsigned int value = *(unsigned int*)(p_pack + dataOffset);
                dataInfo.data.setValue((unsigned int)value);
            }
        }
        else if(dataInfo.data.type() == QVariant::Int)
        {
            if(dataInfo.dataSize == sizeof(char))
            {
                char value = *(char*)(p_pack + dataOffset);
                dataInfo.data.setValue((int)value);
            }
            else if(dataInfo.dataSize == sizeof(short))
            {
                short value = *(short*)(p_pack + dataOffset);
                dataInfo.data.setValue((int)value);
            }
            else if(dataInfo.dataSize == sizeof(int))
            {
                int value = *(int*)(p_pack + dataOffset);
                dataInfo.data.setValue((int)value);
            }
        }
        else if(dataInfo.data.type() == QVariant::Double)
        {
            float value = *(float*)(p_pack + dataOffset);
            dataInfo.data.setValue((double)value);
        }

        dataOffset += dataInfo.dataSize;
    }

    /////for debug//////////////////////////////////////////////////////////////////
//    for(int cnt = 0;cnt < dataNum;cnt++)
//    {
//        qDebug()<<packageList[packageIdMap[packId]].dataList[cnt].dataName
//                <<packageList[packageIdMap[packId]].dataList[cnt].data.toString()
//                <<packageList[packageIdMap[packId]].dataList[cnt].data.typeName();
//    }

    packageModifyLock = false;
    return QString("Read package OK, package ID = %1").arg(packId);
}

QString PackageInterface::updateDataTable(QTableWidget *table, int packIndex)
{
    if(packageList.isEmpty())
        return "There is no package info";

    if(packIndex > packageList.size()-1)
        return "Package index overflow";

    if(packageModifyLock == true)
        return "Package is locked";
    packageModifyLock = true;

    packageFocusedIndex = packIndex;

    struct PackageInfo &packageInfo = packageList[packIndex];

    table->clearContents();
    table->setColumnCount(3);
    table->setRowCount(packageInfo.dataList.size());

    for(int row = 0;row < packageInfo.dataList.size();row++)
    {
       QTableWidgetItem *item0 = new QTableWidgetItem(packageInfo.dataList[row].dataName);
       item0->setFlags(item0->flags() & (~Qt::ItemIsEditable));

       QTableWidgetItem *item1 = new QTableWidgetItem(packageInfo.dataList[row].dataTypeName);
       item1->setFlags(item0->flags() & (~Qt::ItemIsEditable));

       table->setItem(row,0,item0);
       table->setItem(row,1,item1);

       if(packageInfo.dataList[row].data.type() == QVariant::Double)
       {
           QString str;
           table->setItem(row,DATA_COLUMN_INDEX-1,new QTableWidgetItem(str.setNum((float)packageInfo.dataList[row].data.toDouble())));
       }
       else
       {
           table->setItem(row,DATA_COLUMN_INDEX-1,new QTableWidgetItem(packageInfo.dataList[row].data.toString()));
       }
    }

    table->resizeRowsToContents();
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    packageModifyLock = false;
    return QString("Selected package: <%1> ID = %2")
            .arg(packageList[packageFocusedIndex].packageName)
            .arg(packageList[packageFocusedIndex].packageId);
}

void PackageInterface::updateDataColumn(QTableWidget *table, int packIndex)
{
    if(packageFocusedIndex != packIndex)
        return;

    if(table->columnCount() < DATA_COLUMN_INDEX)
        return;

    if(packageList[packIndex].dataList.size() > table->rowCount())
        return;

    if(packageModifyLock == true)
        return;
    packageModifyLock = true;

    struct PackageInfo &packageInfo = packageList[packIndex];

    for(int row = 0;row < packageInfo.dataList.size();row++)
    {
       if(packageInfo.dataList[row].data.type() == QVariant::Double)
       {
           QString str;
           table->item(row,DATA_COLUMN_INDEX-1)->setText(str.setNum((float)packageInfo.dataList[row].data.toDouble()));
       }
       else
       {
           table->item(row,DATA_COLUMN_INDEX-1)->setText(packageInfo.dataList[row].data.toString());
       }
    }

    packageModifyLock = false;
}

QString PackageInterface::updatePackageTable(QTableWidget *table)
{
    if(packageList.isEmpty())
        return "There is no package info";

    if(packageModifyLock == true)
        return "Package is locked";
    packageModifyLock = true;

    table->clearContents();
    table->setColumnCount(4);
    table->setRowCount(packageList.size());

    for(int row = 0;row < packageList.size();row++)
    {
       table->setItem(row,0,new QTableWidgetItem(packageList[row].packageName));
       table->setItem(row,1,new QTableWidgetItem(QString::number(packageList[row].packageId,10)));
       table->setItem(row,2,new QTableWidgetItem(QString::number(packageList[row].packageSize,10)));
       table->setItem(row,3,new QTableWidgetItem(QString::number(packageList[row].packageCount,10)));
    }

    table->resizeRowsToContents();
    table->resizeColumnsToContents();
    table->horizontalHeader()->setStretchLastSection(true);

    packageModifyLock = false;
    return "Update package table OK";
}

void PackageInterface::updatePackageCountColumn(QTableWidget *table, int packIndex)
{
    if(table->colorCount() < 4)
        return;

    if(packIndex > table->rowCount() - 1)
        return;

    if(packageList.size() > table->rowCount())
        return;

    if(packageModifyLock == true)
        return;
    packageModifyLock = true;

    QString str;
    table->item(packIndex,3)->setText(str.setNum(packageList[packIndex].packageCount));

    packageModifyLock = false;
}

QString PackageInterface::setTableFormat(QTableWidget *table, QString table_type)
{
    QStringList header;

    if(table_type == "package")
    {
        header<<"Name"<<"ID"<<"Size"<<"count";
        table->setColumnCount(4);
        table->setHorizontalHeaderLabels(header);
        table->horizontalHeader()->setStretchLastSection(true);

        table->verticalHeader()->setVisible(false);

        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);

        table->resizeRowsToContents();
        table->resizeColumnsToContents();
    }
    else if(table_type == "data")
    {
        table->setColumnCount(DATA_COLUMN_INDEX);

        header<<"Name"<<"Type"<<"Value";
        table->setColumnCount(3);
        table->setHorizontalHeaderLabels(header);
        table->horizontalHeader()->setStretchLastSection(true);

        table->verticalHeader()->setVisible(false);

        table->setSelectionMode(QAbstractItemView::SingleSelection);

        table->resizeRowsToContents();
        table->resizeColumnsToContents();
    }
    else
    {
        return "Undefined table type";
    }

    return "set table format OK";
}

QString PackageInterface::modifyDataValue(QString &value_str, int data_index)
{
    if(data_index > packageList[packageFocusedIndex].dataList.size())
    {
        return "Data index overflow";
    }

    qDebug()<<"lock "<<packageModifyLock;

    if(packageModifyLock == true)
        return "Package is locked";
    packageModifyLock = true;

    struct DataInfo &dataInfo = packageList[packageFocusedIndex].dataList[data_index];

    if(dataInfo.data.type() == QVariant::UInt)
    {
        if(dataInfo.dataSize == sizeof(unsigned char))
        {
            unsigned char value = (unsigned char)value_str.toUInt();
            dataInfo.data.setValue((unsigned int)value);
        }
        else if(dataInfo.dataSize == sizeof(unsigned short))
        {
            unsigned short value = (unsigned short)value_str.toUInt();
            dataInfo.data.setValue((unsigned int)value);
        }
        else if(dataInfo.dataSize == sizeof(unsigned int))
        {
            unsigned int value = (unsigned int)value_str.toUInt();
            dataInfo.data.setValue((unsigned int)value);
        }
    }
    else if(dataInfo.data.type() == QVariant::Int)
    {
        if(dataInfo.dataSize == sizeof(char))
        {
            char value = (char)value_str.toInt();
            dataInfo.data.setValue((int)value);
        }
        else if(dataInfo.dataSize == sizeof(short))
        {
            short value = (short)value_str.toInt();
            dataInfo.data.setValue((int)value);
        }
        else if(dataInfo.dataSize == sizeof(int))
        {
            int value = (int)value_str.toInt();
            dataInfo.data.setValue((int)value);
        }
    }
    else if(dataInfo.data.type() == QVariant::Double)
    {
        float value = (float)value_str.toFloat();
        dataInfo.data.setValue((double)value);
    }


    /////for debug//////////////////////////////////////////////////////////////////
    for(int cnt = 0;cnt < packageList[packageFocusedIndex].dataList.size();cnt++)
    {
        qDebug()<<packageList[packageIdMap[packageFocusedIndex]].dataList[cnt].dataName
                <<packageList[packageIdMap[packageFocusedIndex]].dataList[cnt].data.toString()
                <<packageList[packageIdMap[packageFocusedIndex]].dataList[cnt].data.typeName();
    }
    packageModifyLock = false;
    return "Modify data value OK";
}

QString PackageInterface::generatePackage(QByteArray &dataArray, int pack_index)
{
    if(packageList.isEmpty())
        return "There is no package info";

    struct PackageInfo &packageInfo = packageList[pack_index];
    const char *p_data = 0;

    for(int data_index = 0;data_index < packageInfo.dataList.size();data_index++)
    {
        struct DataInfo &dataInfo = packageInfo.dataList[data_index];

        if(dataInfo.data.type() == QVariant::UInt)
        {
            if(dataInfo.dataSize == sizeof(unsigned char))
            {
                unsigned char value = (unsigned char)dataInfo.data.toUInt();
                p_data = (const char*)&value;
                dataArray.append(p_data,dataInfo.dataSize);
            }
            else if(dataInfo.dataSize == sizeof(unsigned short))
            {
                unsigned short value = (unsigned short)dataInfo.data.toUInt();
                p_data = (const char*)&value;
                dataArray.append(p_data,dataInfo.dataSize);
            }
            else if(dataInfo.dataSize == sizeof(unsigned int))
            {
                unsigned int value = (unsigned int)dataInfo.data.toUInt();
                p_data = (const char*)&value;
                dataArray.append(p_data,dataInfo.dataSize);
            }
        }
        else if(dataInfo.data.type() == QVariant::Int)
        {
            if(dataInfo.dataSize == sizeof(char))
            {
                char value = (char)dataInfo.data.toInt();
                p_data = (const char*)&value;
                dataArray.append(p_data,dataInfo.dataSize);
            }
            else if(dataInfo.dataSize == sizeof(short))
            {
                short value = (short)dataInfo.data.toInt();
                p_data = (const char*)&value;
                dataArray.append(p_data,dataInfo.dataSize);
            }
            else if(dataInfo.dataSize == sizeof(int))
            {
                int value = (int)dataInfo.data.toInt();
                p_data = (const char*)&value;
                dataArray.append(p_data,dataInfo.dataSize);
            }
        }
        else if(dataInfo.data.type() == QVariant::Double)
        {
            float value = (float)dataInfo.data.toDouble();
            p_data = (const char*)&value;
            dataArray.append(p_data,dataInfo.dataSize);
        }
    }

    /////for debug//////////////////////////////////////////////////////////////////
    char fake_data[]={(char)100,
                      (char)-100,
                      (char)0x40,(char)0x9c,
                      (char)0xe0,(char)0xb1,
                      (char)0x40,(char)0x42,(char)0x0f,(char)0x00,
                      (char)0xc0,(char)0xbd,(char)0xf0,(char)0xff,
                      (char)0xcb,(char)0xa1,(char)0x53,(char)0xc1};
    for(int cnt = 0;cnt < dataArray.size();cnt++)
    {
        qDebug()<<(unsigned char)dataArray[cnt]<<(unsigned char)fake_data[cnt];
    }
    return QString("Generate package OK, package ID = %1").arg(packageList[pack_index].packageId);
}
