#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation> //设置动画特效需要包含的头文件
//下面代码块可要可不要，这里选择注释掉
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent) //这里也要修改成QPushButton
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg) //如果构造函数中有默认值，那么实现中不能再有了
{
    //先维护住两个路径
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImg); //先加载用户传进来的这张图
    if(!ret) //加载用户图片失败
    {
        qDebug()<<"图片加载失败";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height()); //设置图片固定大小为pix里面的宽和高

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}"); //设置边框为0像素

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //动画起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //动画起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="") //如果传入的按下图片不等于空，表示用户想切图
    {
        QPixmap pix;
        bool ret = pix.load(pressImgPath); //先加载用户传进来的这张图
        if(!ret) //加载用户图片失败
        {
            qDebug()<<"图片加载失败";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height()); //设置图片固定大小为pix里面的宽和高

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}"); //设置边框为0像素

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //上面的表示一层拦截，其他内容还要交给父类处理，不然点击效果就没了
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="") //如果传入的按下图片不等于空，表示用户想切换成初始图片
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath); //先加载用户传进来的这张图
        if(!ret) //加载用户图片失败
        {
            qDebug()<<"图片加载失败";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height()); //设置图片固定大小为pix里面的宽和高

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}"); //设置边框为0像素

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //上面的表示一层拦截，其他内容还要交给父类处理，不然点击效果就没了
    return QPushButton::mouseReleaseEvent(e);
}

