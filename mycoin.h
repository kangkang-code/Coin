#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>  //修改继承的类为QPushButton
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    MyCoin(QString btnImg); //自定义构造函数，参数代表传入的是金币路径还是银币路径


    //金币的属性
    int posX; //x坐标位置
    int posY; //y左标位置
    bool flag; //正反标示

    //改变标志的方法
    void changeFlag();
    QTimer *timer1; //正面翻反面的定时器
    QTimer *timer2; //反面翻正面的定时器
    int min=1; //最小值，即资源图片中的0001图片
    int max=8; //最大值，即资源图片中的0008图片

    //执行动画的标志，让一个动画做完再做下一个动画
    bool isAnimation = false; //默认为false

    //重写 按下
    void mousePressEvent(QMouseEvent * e);

    //是否胜利的标志
    bool isWin;
signals:

};

#endif // MYCOIN_H
