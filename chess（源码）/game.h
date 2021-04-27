#pragma once
#ifndef GAME_H
#define GAME_H
#define edge 30 //棋盘边缘尺寸
#define grid_size 60  //棋盘格子尺寸
#define grid_number 15 //一行（列）格子数
#define off_set 30
#define EmptyGrid 0
#define whiteFlag 1
#define blackFlag -1
#include<vector>
#include<QDebug>
enum GameType
{
    AI,
    PERSON
};
class Game{
public:
    std::vector<std::vector<int>> GameMap;
    std::vector<std::vector<int>> ScoreMapP;
    std::vector<std::vector<int>> ScoreMapAI;
    GameType my_type;
    //默认让己方先下，己方下为true,对方为false
    bool playFlag=true;
    void GameStart();
    bool isWin(int col,int row);
    void AiAlgorithm(int&col,int&row);
};
#endif // GAME_H
