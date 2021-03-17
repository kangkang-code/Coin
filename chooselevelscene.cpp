#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include"playscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588); //设置大小

    //设置图标
    this->setWindowIcon(QPixmap(":/res:/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
   QMenuBar * bar =  menuBar();
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
      //qDebug()<<"点击了返回按钮";
       //告诉主场景，返回了。即主场景监听ChooseLevelScene按钮
       //做一个延时返回，即点击back后延时0.5秒后返回主场景
       QTimer::singleShot(500,this,[=](){
            emit this->ChooseSceneBack(); //发送自定义信号
       });

   });

   // 创建选择关卡的按钮
   for(int i=0;i<20;i++)
   {
       MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png"); //设置1-20关的图片按钮
       menuBtn->setParent(this); //放置到当前窗口中
       menuBtn->move(25+i%4*70,130+i/4*70); //25和130分别是x和y的起始位置，70和70分别是x和y的间距

       //监听每个按钮的点击事件
       connect(menuBtn,&MyPushButton::clicked,[=](){
           QString str=QString("您选择的是第%1关").arg(i+1);
           qDebug()<<str;



           //进入到游戏场景

           play = new PlayScene(i+1); //创建游戏场景

           //设置游戏场景的初始位置
           play->setGeometry(this->geometry());
           play->show(); //显示游戏场景


           connect(play,&PlayScene::chooseSceneBack,[=](){
               this->setGeometry(play->geometry());
               this->show();
               delete play; // 每个关卡都不一样，不用了就delete掉，有可能进入一个20关，返回不玩，这时候就delete掉，如果再进入新的关卡，就再创建一个新的
               play = NULL;
           });
       });

       //新创建一个控件来显示关卡中的数字
       QLabel * label = new QLabel;
       label->setParent(this);
       label->setFixedSize(menuBtn->width(),menuBtn->height()); //label默认是没有固定大小的，这里设置成menubtn的大小
       label->setText(QString::number(i+1)); //设置1-20的数字
       label->move(25+i%4*70,130+i/4*70); //移动数字到按钮中

       //光移动数字到按钮中是不够的，因为label本质是一个矩形框，这样移动是无法完全移动到中间去的，所以需要设置对齐方式
       label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

       //设置让鼠标进行穿透，不然qlabel会吃掉所有的点击事件，无法传给下层
       label->setAttribute(Qt::WA_TransparentForMouseEvents); //51号属性
   }
}

//重写点击start按钮后跳转的场景的背景图
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png"); //加载背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //设置背景图的小标题
    pix.load(":/res/Title.png"); //加载背景图小标题图片
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix); //当前的宽度减去pix的宽度就是中间，30是高度，后面是pix本身图的宽和高，前面调的是位置
}
