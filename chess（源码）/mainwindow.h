#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QPainter>
#include"game.h"
#include<QMouseEvent>
#include<math.h>
#include<QPoint>
#include<QTimer>
#include<QMessageBox>
#include<QtMultimedia/QSound>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    int click_col;
    int click_row;
    bool IFclickOK=false;
    //游戏指针
    Game *my_game;
    //游戏初始化
    void GameInitialization();
    //绘制函数
    void paintEvent(QPaintEvent*);//会被系统自动调用
    // 在Qt中要捕捉鼠标移动事件需要重写MouseMoveEvent，
    //但是MouseMoveEvent为了不太耗资源在默认状态下是要鼠标按下才能捕捉到。要想鼠标不按下时的移动也能捕捉到，需要setMouseTracking(true)
    //鼠标监听 mainwindow ui->centralwidget mouseTacking
    //无论按下的是哪个键，只要有按键按下并移动就会触发mouseMoveEvent
    void mouseMoveEvent(QMouseEvent*event);
    //void mouseReleaseEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
    void chessByAI();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
