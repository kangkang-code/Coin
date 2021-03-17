#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QObject>
#include <QMap>
#include <QVector>

class dataConfig : public QObject
{
    Q_OBJECT
public:
    explicit dataConfig(QObject *parent = 0); //自定义构造函数

public:

    //mData为所有数据，都放在map容器中，map容器是一个键值对，一个key，一个value，QVector< QVector<int> 为二维数组，key是int类型，相当于第一至二十关的二维数组是什么
    QMap<int, QVector< QVector<int> > >mData;



signals:

public slots:
};

#endif // DATACONFIG_H
