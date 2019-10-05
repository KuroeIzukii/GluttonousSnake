#pragma
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <Windows.h>

struct entity {
	int x, y;
};

/*蛇的坐标*/
extern entity snake[1000];
extern entity snakeTemp[1000];
extern entity food;
extern entity mapEmpty[1000];

/*游戏难度*/
extern int gameLevel;

/*游戏结束*/
extern bool gameover;

/*地图长宽*/
extern int mapWidth, mapLength;

/*蛇的长度*/
extern int snakeLength;

/*蛇头方向*/
extern int snakeDir;
extern int snakeDirTemp;

/*蛇头转向*/
extern int snakeTurns[4][2];

/*速度*/
extern double speed;

/*获取按键*/
extern char ch;

/*时间*/
extern clock_t clockStart, clockEnd;

void locateCursor(int x, int y);

void hideCursor();

bool canGameStart();

void switchDir();

void move();

int randomX();

int randomY();

int random();

void printMap();

void printSnake();

bool isCollide();

bool isFoodEaten();

void printFood();

bool exitGame();

void printFoods();

void GluttonousSnake();