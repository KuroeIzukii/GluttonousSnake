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

/*�ߵ�����*/
extern entity snake[1000];
extern entity snakeTemp[1000];
extern entity food;
extern entity mapEmpty[1000];

/*��Ϸ�Ѷ�*/
extern int gameLevel;

/*��Ϸ����*/
extern bool gameover;

/*��ͼ����*/
extern int mapWidth, mapLength;

/*�ߵĳ���*/
extern int snakeLength;

/*��ͷ����*/
extern int snakeDir;
extern int snakeDirTemp;

/*��ͷת��*/
extern int snakeTurns[4][2];

/*�ٶ�*/
extern double speed;

/*��ȡ����*/
extern char ch;

/*ʱ��*/
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