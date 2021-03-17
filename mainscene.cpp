#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h" //这里要写自己写的类的头文件名
#include<QDebug>
#include<QTimer> //延时进入方法要包含的头文件
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);


    /////////////设置主场景///////////////

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("康康带你翻金币");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });



    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this); //将按钮放到当前窗口中
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);//取屏幕的宽度的一半减去按钮宽度的一半就在中心位置了

    chooseScene = new ChooseLevelScene; //实例化选择关卡场景


    //监听选择关卡的返回按钮的信号 （代码要写到这，只要一次监听就可以了）
    connect(chooseScene,&ChooseLevelScene::ChooseSceneBack,this,[=](){

        this->setGeometry(chooseScene->geometry());
        chooseScene->hide(); //将选择关卡场景隐藏
        this->show(); //重新显示主场景
    });


    connect(startBtn,&MyPushButton::clicked,[=](){

        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入到选择关卡中

        //进入到选择关卡场景中
        QTimer::singleShot(500,this,[=](){  //延时0.5秒进入场景

            //设置chooseScene场景的位置，让它不要随意移动
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示关卡场景
            chooseScene->show();


        });

    });
}

//实现背景图重写
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //生成画家对象
    QPixmap pix; //生成pix对象
    pix.load(":/res/PlayLevelSceneBg.png"); //加载背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix); //加载完画出背景图,两个this表示拉伸成屏幕的宽度和高度

    //画出背景上的图标
    pix.load(":/res/Title.png"); //加载图标图
    pix =  pix.scaled(pix.width()*0.5,pix.height()*0.5); //缩放图标，原来的宽高乘上0.5
    painter.drawPixmap(10,30,pix); //画出背景上的图标
}
MainScene::~MainScene()
{
    delete ui;
}

