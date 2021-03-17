#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写绘图事件，实现背景
    void paintEvent(QPaintEvent*);

    //游戏场景对象指针
    PlayScene * play = NULL; //默认置为空

signals:
    //写一个自定义信号，告诉主场景点击了返回
    void ChooseSceneBack(); //可以有参，也可以无参，自定义信号只需要声明，不需要实现
};

#endif // CHOOSELEVELSCENE_H
