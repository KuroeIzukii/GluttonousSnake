#include "functions.h"
using namespace std;

/*蛇的坐标*/
entity snake[1000] = {};
entity snakeTemp[1000] = {};
entity food;
entity mapEmpty[1000] = {};

/*游戏难度*/
int gameLevel;

/*游戏结束*/
bool gameover = false;

/*地图长宽*/
int mapWidth, mapLength;

/*蛇的长度*/
int snakeLength;

/*蛇头方向*/
int snakeDir;
int snakeDirTemp;

/*蛇头转向*/
int snakeTurns[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

/*速度*/
double speed;

/*获取按键*/
char ch;

/*时间*/
clock_t clockStart, clockEnd;

/*定位并移动光标*/
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;
void locateCursor(int x, int y) {
	coord.X = x*2;
	coord.Y = y;
	SetConsoleCursorPosition(hOutput, coord);
}

/*隐藏光标*/
void hideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hOutput, &cursor_info);
}

/*游戏是否开始*/
bool canGameStart() {
	if (_kbhit()) {
		ch = _getch();
		if (ch == ' ')
			return true;
	}
	return false;
}

/*改变方向*/
void switchDir() {
	//while (1) {
		//if (!gameover/*_kbhit()*/) {
			if (_kbhit()) {
				ch = _getch();
				if (ch == -32) {
					ch = _getch();
					switch (ch) {
					case 72:
						if (snakeDir == 0 || snakeDir == 1)
							snakeDir = 2;
						break;
					case 80:
						if (snakeDir == 0 || snakeDir == 1)
							snakeDir = 3;
						break;
					case 75:
						if (snakeDir == 2 || snakeDir == 3) 
							snakeDir = 0;
						break;
					case 77:
						if (snakeDir == 2 || snakeDir == 3) 
							snakeDir = 1;
						break;
					}
				}
			}
		//}
		//else
			//break;
	//}
}

/*移动蛇*/
void move() {
	/*正常移动*/
	for (int i = 0; i <= snakeLength - 2; i++)
		snakeTemp[i + 1] = snake[i];
	snakeTemp[0].x = snake[0].x + snakeTurns[snakeDir][0];
	snakeTemp[0].y = snake[0].y + snakeTurns[snakeDir][1];
	/*吃到食物*/
	if (snakeTemp[0].x == food.x && snakeTemp[0].y == food.y) {
		snakeTemp[snakeLength] = snake[snakeLength - 1];
		snakeLength++;
		food.x = -1;
		food.y = -1;
		locateCursor(mapWidth + 2, (int)(mapLength / 2) + 1);
		cout << snakeLength - 5;
		locateCursor(mapWidth + 2, mapLength + 2);
		cout << endl;
	}
	else {
		locateCursor(snake[snakeLength - 1].x, snake[snakeLength - 1].y);
		cout << "　";
	}
	/*是否撞墙*/
	if (isCollide()) {
		locateCursor(mapWidth / 2 - 2, mapLength + 2);
		//cout << snakeTemp[0].x << snakeTemp[0].y << snake[0].x << snake[0].y;
		cout << "游戏结束" << endl;
		gameover = true;
	}
	else {
		for (int i = 0; i <= snakeLength - 1; i++) {
			snake[i] = snakeTemp[i];
		}
		locateCursor(snake[1].x, snake[1].y);
		cout << "Ｘ";
		locateCursor(snake[0].x, snake[0].y);
		cout << "Ｏ";
		locateCursor(mapWidth + 2, mapLength + 2);
		cout << endl;
	}

}

/*生产随机数*/
int randomX() {
	return rand() % mapWidth + 1;
}
int randomY() {
	return rand() % mapLength + 1;
}
int random() {
	return rand() % (mapWidth * mapLength - snakeLength);
}

/*打印地图*/
void printMap() {
	locateCursor(0, 0);
	cout << "·";
	for (int i = 1; i <= mapWidth; i++)
		cout << "—";
	cout << "·" << endl;
	for (int j = 1; j <= mapLength; j++) {
		cout << "｜";
		for (int i = 1; i <= mapWidth; i++)
			cout << "　";
		cout << "｜" << endl;
	}
	cout << "·";
	for (int i = 1; i <= mapWidth; i++)
		cout << "—";
	cout << "·";
}

/*首次打印蛇*/
void printSnake() {
	locateCursor(snake[0].x, snake[0].y);
	cout << "Ｏ";
	for (int i = 1; i <= snakeLength - 1; i++) {
		locateCursor(snake[i].x, snake[i].y);
		cout << "Ｘ";
	}
	locateCursor(mapWidth + 2, mapLength + 2);
	cout << endl;
}

/*判断是否撞墙或自撞*/
bool isCollide() {
	if (snakeTemp[0].x == 0 || snakeTemp[0].y == 0 || snakeTemp[0].x == mapWidth + 1 || snakeTemp[0].y == mapLength + 1)
		return true;
	else {
		for (int i = 1; i <= snakeLength - 1; i++) {
			if (snakeTemp[0].x == snakeTemp[i].x && snakeTemp[0].y == snakeTemp[i].y) {
				return true;
				break;
			}
		}
	}
	return false;
}

/*是否吃掉食物*/
bool isFoodEaten() {
	if (food.x == -1 && food.y == -1) {
		return true;
	}
	return false;
}

/*打印食物*/
void printFood() {
	//bool canPrint = false;
	int p = 0;
	int rand;
	if (isFoodEaten()) {
		srand((unsigned)time(NULL)*random());
		for (int i = 1; i <= mapWidth; i++) {
			for (int j = 1; j <= mapLength; j++) {
				if ((snake[0].x == i + 1 && snake[0].y == j) || (snake[0].x == i - 1 && snake[0].y == j) || (snake[0].x == i && snake[0].y == j + 1) || (snake[0].x == i && snake[0].y == j - 1)) {
					continue;
				}
				mapEmpty[p].x = i;
				mapEmpty[p].y = j;
				p++;
				for (int k = 0; k <= snakeLength - 1; k++) {
					if (snake[k].x == i && snake[k].y == j) {
						p--;
						//mapEmpty[p].x = 0;
						//mapEmpty[p].y = 0;
						
					}
				}
			}
		}
		rand = random();
		food.x = mapEmpty[rand].x;
		food.y = mapEmpty[rand].y;
		locateCursor(food.x, food.y);
		cout << "ｏ";
		locateCursor(mapWidth + 2, mapLength + 2);
		cout << endl;
	}
	/*
	while (1) {
		if (isFoodEaten()) {
			srand((unsigned)time(NULL));
			food.x = randomX();
			food.y = randomY();
			for (int i = 0; i <= snakeLength - 1; i++) {
				if (food.x == snake[i].x && food.y == snake[i].y) {
					canPrint = false;
					food.x = -1;
					food.y = -1;
					break;
				}
				canPrint = true;
			}
			if (canPrint) {
				locateCursor(food.x, food.y);
				cout << "ｏ";
				locateCursor(mapWidth + 2, mapLength + 2);
				cout << endl;
				break;
			}
			//else
				//break;
		}
		else
			break;
	}
	*/
}

/*退出游戏*/
bool exitGame() {
	if (_kbhit()) {
		ch = _getch();
		if (ch == 27)
			return true;
	}
	return false;
}

/*游戏本体*/
void GluttonousSnake() {
	/*重置*/
	gameLevel = 0;
	mapWidth = 0;
	mapLength = 0;
	hideCursor();
	while (gameLevel > 10 || gameLevel < 1 || mapWidth < 10 || mapWidth > 40 || mapLength < 10 || mapLength > 25) {
		cin.clear();
		cout << "输入游戏难度(1-10）：";
		cin >> gameLevel;
		cout << "输入地图宽度(10-40)：";
		cin >> mapWidth;
		cout << "输入地图长度(10-25)：";
		cin >> mapLength;
		if (gameLevel > 10 || gameLevel < 1 || mapWidth < 10 || mapWidth > 40 || mapLength < 10 || mapLength > 25) {
			system("cls");
			cout << "输入有误，请重新输入" << endl;
		}
	}
	//gameover = false;
	snakeLength = 5;
	for (int i = 0; i <= 4; i++) {
		snake[i].x = 5 - i;
		snake[i].y = mapLength / 2;
	}
	snakeDir = 1;
	//snakeDirTemp = 1;
	food.x = -1;
	food.y = -1;
	system("cls");
	printMap();
	printSnake();
	printFood();
	locateCursor(mapWidth / 2 - 3, mapLength + 2);
	cout << "按空格开始游戏";
	while (1) {
		if (canGameStart()) {
			//thread foodPrinter(printFoods);
			//foodPrinter.detach();
			gameover = false;
			locateCursor(mapWidth / 2 - 3, mapLength + 2);
			cout << "　　　　　　　";
			locateCursor(mapWidth + 2, mapLength / 2);
			cout << "score:";
			locateCursor(mapWidth + 2, (int)(mapLength / 2) + 1);
			cout << snakeLength - 5;
			locateCursor(mapWidth + 2, mapLength + 2);
			cout << endl;
			//thread kbMonitor(switchDir);
			//kbMonitor.detach();
			break;
		}
	}
	while (!gameover) {
		/*速度随蛇长度变化*/
		speed = (double)snakeLength / (double)((double)mapWidth * (double)mapLength);
		clockStart = clock();
		while (1) {
			clockEnd = clock();
			if ((double)clockEnd - (double)clockStart >= (double)(400 - (double)gameLevel * 25) * (1 - sqrt(speed)))
				break;
		}
		//snakeDir = snakeDirTemp;
		switchDir();
		move();
		printFood();
		//thread foodPrinter(printFood);
		//foodPrinter.detach();
	}
}

/*失败的东西*/
void printFoods() {
	while (1) {
		printFood();
	}
}


//srand((unsigned)time(NULL));