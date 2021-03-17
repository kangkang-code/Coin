#include "mycoin.h"
#include<QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg); //如果图片加载失败
    if(!ret)
    {
            QString str= QString("图片 %1 加载失败").arg(btnImg);
            qDebug()<<str;
            return;
    }

    //如果加载成功
    this->setFixedSize(pix.width(),pix.height()); //设置宽高
    this->setStyleSheet("QPushButton{border:0px;}"); //设置边框为0像素
    this->setIcon(pix); //设置图标
    this->setIconSize(QSize(pix.width(),pix.height())); //设置图标大小

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号，并且翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++); //初始化值是1
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height()); //设置宽高
        this->setStyleSheet("QPushButton{border:0px;}"); //设置边框为0像素
        this->setIcon(pix); //设置图标
        this->setIconSize(QSize(pix.width(),pix.height())); //设置图标大小
        //判断如果翻完了，将min重置为1
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation = false; //做完动画了
            timer1->stop(); //停止定时器
        }
    });


    //监听反面翻正面的信号，并且翻转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--); //初始化值是8
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height()); //设置宽高
        this->setStyleSheet("QPushButton{border:0px;}"); //设置边框为0像素
        this->setIcon(pix); //设置图标
        this->setIconSize(QSize(pix.width(),pix.height())); //设置图标大小
        //判断如果翻完了，将min重置为1
        if(this->max<this->min)
        {
            this->max=8;
            isAnimation = false; //做完动画了
            timer2->stop(); //停止定时器
        }
    });

}

//重写鼠标按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)  //如果此时正在做动画，则不执行任何操作，等动画执行完再执行下一个操作,并且如果胜利了，直接return掉，不给做任何操作
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e); //其他的操作交给父类处理
    }
}

//改变正反面标志的方法
void MyCoin::changeFlag()
{
    //如果是正面，翻成反面
    if(this->flag)
    {
        //开启正面翻翻面的定时器
        timer1->start(30); //每隔30毫秒发送信号
        isAnimation = true; //开始做动画
        this->flag=false; //翻面
    }
    else  //反面翻正面
    {
        timer2->start(30);
        isAnimation = true; //开始做动画
        this->flag=true;
    }
}
