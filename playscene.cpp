#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include"mycoin.h"
#include<QPropertyAnimation>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex = levelNum;

    //初始化游戏场景

    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png"); //第二个参数默认为空，就是之前第二个成员属性，pressImg，现在传入一个参数，使得按下后切换为另一张图片
    backBtn->setParent(this);  //将当前按钮放到窗口中
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height()); //设置位置,当前高宽减去按钮的高宽

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
       qDebug()<<"翻金币场景中，点击了返回按钮";

        QTimer::singleShot(500,this,[=](){
             emit this->chooseSceneBack(); //发送自定义信号
        });

    });

    //点击第几关后，显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏"); //设置字体
    font.setPointSize(20); //设置字号
    QString str1 = QString("level: %1").arg(this->levelIndex); //设置显示内容

    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1); //显示关卡数
    label->setGeometry(30,this->height()-50,120,50); //设置宽高和大小



    dataConfig config;
    //初始化每个关卡的二维数组
    for (int i=0;i<4 ;i++ ) {
        for (int j=0;j<4 ;j++ ) {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }


    //胜利图片显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height()); //-tmpPix.height(),-表示负方向，表现在屏幕上就是上面


    //显示金币背景图案
    for (int i=0;i<4 ;i++ ) {
        for (int j=0;j<4 ;j++ ) {
            //绘制背景图片
            QPixmap pix = QPixmap(":/res/BoardNode(1).png"); //加载背景图
            QLabel * label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height()); //设置大小为背景图的宽和高
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50); //背景图移动

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                //等于1就等于显示金币
                str=":/res/Coin0001.png";
            }

            else
            {
                //要不就显示银币
                 str=":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str); //加载金币图片
            coin->setParent(this);
            coin->move(59+i*50,204+j*50); //设置金币位置

            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag = this->gameArray[i][j]; //1是正面，0是反面

            //将金币放入到金币的二维数组里，以便后期维护(把金币的上下左右拿到手，之前的数组每个金币之间都是独立的）
            coinBtn[i][j]=coin;

            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                for (int i=0;i<4 ;i++ ) {
                    for (int j=0;j<4 ;j++ ) {
                        this->coinBtn[i][j]->isWin=true;  //在点击按钮时，其他按钮都设为胜利的状态，即在点击当前按钮时，其他按钮都失效，无法点击
                    }
                }

                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0; //更新数组状态，如果是银币，翻转后变成金币，反之是银币

                //翻转周围的硬币

                //翻转右侧的硬币,延时翻转
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX<=3) //周围的右侧金币翻转的条件
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag(); //[coin->posX+1]x坐标加1，[coin->posY]->changeFlag()那么翻转y坐标，即右侧坐标的金币
                         this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0; //维护代码中01的数据，即更新数组
                    }

                    //翻转左侧的硬币
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                         this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }

                    //翻转上侧的硬币
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                         this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }

                    //翻转下侧的硬币
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                         this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }

                    for (int i=0;i<4 ;i++ ) {
                        for (int j=0;j<4 ;j++ ) {
                            this->coinBtn[i][j]->isWin=false; //翻完周围金币后，将所有金币解开禁用
                        }
                    }


                    //判断是否胜利
                    this->isWin = true;
                    for (int i=0;i<4 ;i++ ) {
                        for (int j=0;j<4 ;j++ ) {
                            if(coinBtn[i][j]->flag==false) //只要有一个反面，就失败
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true)  //如果isWin依然等于true
                    {
                        qDebug()<<"胜利了";
                        //将所有按钮的胜利的标志改为true;如果再次调集按钮，直接return，不做响应
                        for (int i=0;i<4 ;i++ ) {
                            for (int j=0;j<4 ;j++ ) {
                              coinBtn[i][j]->isWin=true; //如果胜利了就把按钮全部改为true
                            }
                        }

                        //将胜利的图片移动下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });

            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix; //生成pix对象
    pix.load(":/res/PlayLevelSceneBg.png"); //加载背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix); //加载完画出背景图,两个this表示拉伸成屏幕的宽度和高度

    //画出背景上的图标
    pix.load(":/res/Title.png"); //加载图标图
    pix =  pix.scaled(pix.width()*0.5,pix.height()*0.5); //缩放图标，原来的宽高乘上0.5
    painter.drawPixmap(10,30,pix); //画出背景上的图标

}
