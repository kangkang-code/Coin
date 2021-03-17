#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum); //记录关卡号

    int levelIndex; //内部成员属性，记录所选关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    int gameArray[4][4]; //二维数组，维护每关的具体数据，map容器中是每次都是第几关，但是第几关在第12行代码中已经记录在lavelNum中，所以我们去除掉第几关，只保存关卡数据，即去掉外壳

    MyCoin * coinBtn[4][4]; //再做一个数组，维护实现翻转周围金币的数组，上一个二维数组每一个金币之间都是独立的

    //是否胜利的标志
    bool isWin;
signals:
     void chooseSceneBack(); //自定义信号，可以一样
};

#endif // PLAYSCENE_H
