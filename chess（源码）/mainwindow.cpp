#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(edge*2+grid_number*grid_size,edge*2+grid_number*grid_size);//设置窗口大小
    GameInitialization();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow:: GameInitialization()
{
    my_game=new Game;
    QMessageBox msg;
    QPushButton*Ai=msg.addButton(tr("AI"),QMessageBox::AcceptRole);
    QPushButton*Per=msg.addButton(tr("PERSON"),QMessageBox::AcceptRole);
    msg.exec();
    QPushButton*tmp=(QPushButton*)msg.clickedButton();
    if(tmp==Ai)
 {
        my_game->my_type=AI;
        my_game->GameStart();
 }
    if(tmp==Per)
 {
        my_game->my_type=PERSON;
        my_game->GameStart();
   }
    update();
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter artist(this);
    artist.setRenderHint(QPainter:: Antialiasing, true);  //设置渲染,启动反锯齿
    QPen pen(Qt::black,3,Qt::SolidLine,Qt::SquareCap,Qt::BevelJoin);//设置画棋盘的画笔
    artist.setPen(pen);//设置画笔
    // 画棋盘
    //画竖线
    for(int i=0;i<grid_number+1;i++)
    {
        artist.drawLine(edge+i*grid_size,edge,edge+i*grid_size,edge+grid_number*grid_size);
    }
    //画横线
    for(int i=0;i<grid_number+1;i++)
    {
        artist.drawLine(edge,edge+i*grid_size,edge+grid_size*grid_number,edge+i*grid_size);
    }
    //画鼠标移动时预览棋子
    if(IFclickOK==true&&click_col>0&&click_col<grid_number&&click_row>0&&click_row<grid_number)
    {
        QBrush my_brush;
        my_brush.setColor(Qt::white);
        my_brush.setStyle(Qt::SolidPattern);
        artist.setBrush(my_brush);
        pen.setColor(Qt::black);
        pen.setWidth(1);
        artist.setPen(pen);
        QPoint my_point(edge+click_col*grid_size,edge+click_row*grid_size);
        artist.drawEllipse(my_point,20,20);
    }
    //画选中的棋子
    for(int i=1;i<grid_number;i++)
    {
        for(int j=1;j<grid_number;j++)
        {
            if(my_game->GameMap[i][j]==1)
            {
                QBrush my_brush;
                my_brush.setColor(Qt::white);
                my_brush.setStyle(Qt::SolidPattern);
                artist.setBrush(my_brush);
                pen.setColor(Qt::black);
                pen.setWidth(1);
                artist.setPen(pen);
                QPoint my_point(edge+i*grid_size,edge+j*grid_size);
                artist.drawEllipse(my_point,27,27);
            }
            else if(my_game->GameMap[i][j]==-1)
            {
                QBrush my_brush;
                my_brush.setColor(Qt::black);
                my_brush.setStyle(Qt::SolidPattern);
                artist.setBrush(my_brush);
                pen.setColor(Qt::black);
                pen.setWidth(1);
                artist.setPen(pen);
                QPoint my_point(edge+i*grid_size,edge+j*grid_size);
                artist.drawEllipse(my_point,27,27);
            }
        }
    }
    if(click_col>0&&click_col<15&&click_row>0&&click_row<15)
        {
            if(my_game->isWin(click_col,click_row)==true)
            {
                if(my_game->GameMap[click_col][click_row]==whiteFlag)
                {

                    QMessageBox msg_box;
                    msg_box.setText("white player has won!");
                    msg_box.exec();

                }
                if(my_game->GameMap[click_col][click_row]==blackFlag)
                {

                    QMessageBox msg_box;
                    msg_box.setText("black player has won!");
                    msg_box.exec();

                }
                artist.end();
                my_game->GameStart();
            }
        }
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    //记录当前鼠标位置坐标
    int x=e->x();
    int y=e->y();
    click_col=click_row=-1;
    int col=-1;
    int row=-1;
    int now_dis;
    //下面先简化处理，棋子不能落在最边缘的线上，以便于后续的ai评分算法
    if(x>=edge+grid_size/2&&x<=edge+grid_size*grid_number-grid_size/2&&y>=edge+grid_size/2&&y<=edge+grid_size*grid_number-grid_size/2)
    {
        //获取鼠标所在格子的左上格子行列
        int left_up_grid_col=(x-edge)/grid_size;
        int left_up_grid_row=(y-edge)/grid_size;
        //获取鼠标所在格子的左上格子坐标
        int left_up_posX=edge+left_up_grid_col*grid_size;
        int left_up_posY=edge+left_up_grid_row*grid_size;
        //获取鼠标所在格子的左上格子离鼠标距离
        int left_up_dis=sqrt((x-left_up_posX)*(x-left_up_posX)+(y-left_up_posY)*(y-left_up_posY));


        //获取鼠标所在格子的右上格子行列
        int right_up_grid_col=left_up_grid_col+1;
        int right_up_grid_row=left_up_grid_row;
        //获取鼠标所在格子的右上格子坐标
        int right_up_posX=left_up_posX+grid_size;
        int right_up_posY=left_up_posY;
        //获取鼠标所在格子的右上格子离鼠标距离
        int right_up_dis=sqrt((x-right_up_posX)*(x-right_up_posX)+(y-right_up_posY)*(y-right_up_posY));


        //获取鼠标所在格子的左下格子行和列
        int left_down_grid_col=left_up_grid_col;
        int left_down_grid_row=left_up_grid_row+1;
        //获取鼠标所在格子的左下格子坐标
        int left_down_posX=left_up_posX;
        int left_down_posY=left_up_posY+grid_size;
        //获取鼠标所在格子的左下格子离鼠标距离
        int left_down_dis=sqrt((x-left_down_posX)*(x-left_down_posX)+(y-left_down_posY)*(y-left_down_posY));


        //获取鼠标所在格子右下格子行和列
        int right_down_grid_col=left_up_grid_col+1;
        int right_down_grid_row=left_up_grid_row+1;
        //获取鼠标所在格子的右下格子坐标
        int right_down_posX=left_up_posX+grid_size;
        int right_down_posY=left_up_posY+grid_size;
        //获取鼠标所在格子的右下格子离鼠标距离
        int right_down_dis=sqrt((x-right_down_posX)*(x-right_down_posX)+(y-right_down_posY)*(y-right_down_posY));

        now_dis=left_up_dis;
        col=left_up_grid_col;
        row=left_up_grid_row;
        if(my_game->GameMap[col][row]==0)
        {
         IFclickOK=true;
        }

        if(now_dis>right_up_dis)
        {
            now_dis=right_up_dis;
            col=right_up_grid_col;
            row=right_up_grid_row;
            if(my_game->GameMap[col][row]==0)
            {
             IFclickOK=true;
            }
        }

        if(now_dis>left_down_dis)
        {
            now_dis=left_down_dis;
            col=left_down_grid_col;
            row=left_down_grid_row;
            if(my_game->GameMap[col][row]==0)
            {
             IFclickOK=true;
            }
        }

        if(now_dis>right_down_dis)
        {
            now_dis=right_down_dis;
            col=right_down_grid_col;
            row=right_down_grid_row;
            if(my_game->GameMap[col][row]==0)
            {
             IFclickOK=true;
            }
        }
        if(IFclickOK==true)
        {
            click_col=col;
            click_row=row;
        }
     }
    update();
}
void MainWindow::chessByAI()
{
    my_game->AiAlgorithm(click_col,click_row);
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();
    //若为人人对战模式
    if(my_game->my_type==PERSON)
 {
     //鼠标点击在有效位置并且当轮到己方下棋时，将游戏数据中的下棋位置标记为1
    if(x>=edge+grid_size/2&&x<=edge+grid_size*grid_number-grid_size/2&&y>=edge+grid_size/2&&y<=edge+grid_size*grid_number-grid_size/2&&event->button()==Qt::LeftButton&&IFclickOK==true&&my_game->playFlag==true&&my_game->GameMap[click_col][click_row]==EmptyGrid)
    {
        my_game->GameMap[click_col][click_row]=whiteFlag;
        //下棋后将位置标记为false
         IFclickOK=false;

        //下完后轮到对方下棋
        my_game->playFlag=false;
        update();
    }
      //鼠标点击在有效位置并且当轮到对方下棋时，将游戏数据中的下棋位置标记为1
    if(x>=edge+grid_size/2&&x<=edge+grid_size*grid_number-grid_size/2&&y>=edge+grid_size/2&&y<=edge+grid_size*grid_number-grid_size/2&&event->button()==Qt::LeftButton&&IFclickOK==true&&my_game->playFlag==false&&my_game->GameMap[click_col][click_row]==EmptyGrid)
    {
        my_game->GameMap[click_col][click_row]=blackFlag;
        //下棋后将位置标记为false
         IFclickOK=false;


        //己方下完轮到对方下棋
        my_game->playFlag=true;
        update();
    }
}
    //若为人机对战模式
    if(my_game->my_type==AI)
    {
          //鼠标点击在有效位置并且当轮到己方下棋时，将游戏数据中的下棋位置标记为1
        if(x>=edge+grid_size/2&&x<=edge+grid_size*grid_number-grid_size/2&&y>=edge+grid_size/2&&y<=edge+grid_size*grid_number-grid_size/2&&event->button()==Qt::LeftButton&&IFclickOK==true&&my_game->playFlag==true&&my_game->GameMap[click_col][click_row]==EmptyGrid)
        {
            my_game->GameMap[click_col][click_row]=whiteFlag;
            //下棋后将位置标记为false
             IFclickOK=false;


            //己方下完轮到对方下棋
            my_game->playFlag=false;
            update();
        }
        //延时
        QEventLoop my_loop;
        QTimer::singleShot(1000,&my_loop,SLOT(quit()));
        my_loop.exec();

        if(my_game->playFlag==false)
        {
            chessByAI();
            my_game->GameMap[click_col][click_row]=blackFlag;
            //下棋后将位置标记为false
             IFclickOK=false;


            //对方下完轮到己方下棋
            my_game->playFlag=true;
            update();
        }
    }
}
