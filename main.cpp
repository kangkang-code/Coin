#include "mainscene.h"

#include <QApplication>
#include<QDebug>
#include"dataconfig.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    w.show();

//    //测试关卡数据
//    dataConfig config; //先声明一个对象
//    for(int i=0;i<4;i++)
//    {
//        for(int j=0;j<4;j++)
//        {
//            qDebug()<<config.mData[1][i][j]; //打印第1关的数据
//        }
//        qDebug()<<"";
//    }
    return a.exec();
}
