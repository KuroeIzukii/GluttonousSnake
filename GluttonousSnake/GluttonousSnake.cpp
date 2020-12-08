#include "functions.h"
using namespace std;

int main(){
	hideCursor();
	cout << "·－－－－－－－－－－－－－－－－－－·" << endl;
	cout << "｜　　　　　　　　　　　　　　　　　　｜" << endl;
	cout << "｜　　　　　　贪吃蛇 1.3a 　　　　　　｜" << endl;
	cout << "｜　　　　　 By KuroeIzukii 　　　　　｜" << endl;
	cout << "｜　　　　　　　　　　　　　　　　　　｜" << endl;
	cout << "·－－－－－－－－－－－－－－－－－－·" << endl;
	cout << "　　　　　　 长按空格键继续" << endl;
	cout << "　　　　　　　按esc键退出";
	while (!canGameStart()){
		if (exitGame())
			return 0;
	}
	while (1) {
		system("cls");
		GluttonousSnake();
		locateCursor(mapWidth / 2 - 2, mapLength + 2);
		cout << "　　　　" << endl;
		locateCursor(mapWidth / 2 - 4, mapLength + 2);
		cout << "长按空格键重新开始";
		locateCursor(mapWidth / 2 - 2, mapLength + 3);
		cout << "按esc键退出";
		while (!canGameStart()) {
			if (exitGame())
				return 0;
		}
	}
	return 0;
}