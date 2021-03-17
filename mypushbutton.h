#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton> //修改继承的父类为QPushButton
class MyPushButton : public QPushButton //这里也要修改
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //自定义构造函数,参数1：正常显示的图片路径  参数2：按下后显示的图片路径
    MyPushButton(QString normalImg,QString pressImg=""); //normalImg是必须要传的，pressImg可以传也可以不传，start是没有设计按下按钮的，如果构造函数中有默认值，那么实现中不能再有了


    QString normalImgPath; //成员属性，保存用户传入的默认显示路径
    QString pressImgPath;  //成员属性，保存用户按下后的默认显示路径

    //弹跳特效
    void zoom1(); //向下跳
    void zoom2(); //向上条

    //重写Back按钮的按下和释放事件
    void mousePressEvent(QMouseEvent * e);

    void mouseReleaseEvent(QMouseEvent * e);
signals:

};

#endif // MYPUSHBUTTON_H
