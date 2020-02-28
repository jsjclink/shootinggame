//Header file
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h> //gotoxy
#include<conio.h>
//Define constant 

//Global Variables Declaration
char selection = 0; //menu select
int map[26][62];
int x = 32, y = 24, a=0;
int bullet_x[10];
int bullet_y[10];
int bullet_count = 0;
int checkcollision = 0;

// Functions Declaration
void Gotoxy(int x, int y);
void HideCursor();
void StartScreen();
void HelpScreen();
void GamePlay();
void PressAnyKey();
void PrintBoundary();
void PrintPlayer();
void MovePlayer();
void PrintStatus();
void CreateBullet();
void PrintBullet();
int CountBullet();
int CheckBulletCollision_wall();

int main() {
	HideCursor();
	system("cls");
	system("mode con cols=80 lines=30");
	while (1) {
		StartScreen();
		PressAnyKey();
		selection = _getch();
		system("cls");
		switch (selection) {
		case '1': GamePlay(); return 0;
		case '2': HelpScreen(); break;
		}
	} //while
	return 0;
}

//Functions
void Gotoxy(int x, int y) {
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void StartScreen() {
	printf("####################\n");
	Sleep(100);
	printf("#    * G A M E *   #\n");
	printf("#    * T E S T *   #\n");
	Sleep(100);
	printf("#                  #\n");
	printf("#                  #\n");
	Sleep(100);
	printf("#   * 1 : start *  #\n");
	printf("#                  #\n");
	Sleep(100);
	printf("#                  #\n");
	printf("#                  #\n");
	Sleep(100);
	printf("#   * 2 : help  *  #\n");
	printf("#                  #\n");
	Sleep(100);
	printf("#                  #\n");
	printf("#                  #\n");
	Sleep(100);
	printf("####################");
}
void HelpScreen() {
	printf("help me!");
}
void PressAnyKey() {
	while (1) {
		if (_kbhit()) {
			return ;
		}
	}
}

void GamePlay() {
	memset(bullet_x, -1, sizeof(bullet_x));
	memset(bullet_y, -1, sizeof(bullet_y));
	while (1) {
		PrintBoundary();
		MovePlayer();
		checkcollision = CheckBulletCollision_wall();
		PrintBullet();
		PrintPlayer();
		CountBullet();
		PrintStatus();
		PressAnyKey();
	}
}

void PrintBoundary() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 62; j++) {
			if (map[i][j] == 1) {
				Gotoxy(j, i);
				printf("#");
			}
		}
	}
}

void PrintPlayer() {
	Gotoxy(x, y);
	printf("*");
}
void MovePlayer() {
	char move_c = _getch();
	switch (move_c) {
	case 'w': {
		if (y - 1 == 0) { break; }
		Gotoxy(x, y); printf("%c", 0); y--; break;
	}
	case 'a': {
		if (x - 1 == 0) { break; }
		Gotoxy(x, y); printf("%c", 0); x--; break;
	}
	case 's': {
		if (y + 1 == 25) { break; }
		Gotoxy(x, y); printf("%c", 0); y++; break;
	}
	case 'd': {
		if (x + 1 == 61) { break; }
		Gotoxy(x, y); printf("%c", 0); x++; break;
	}
	case 'l': {
		if (y == 1) { break; }
		CreateBullet(); break;
	}
	}
}
void PrintStatus() {
	Gotoxy(63, 1);
	printf("x : %3d", x);

	Gotoxy(63, 2);
	printf("y : %3d", y);
	
	Gotoxy(63, 3);
	printf("bullet : %3d", bullet_count);
	
	Gotoxy(63, 4);
	printf("check : %3d", checkcollision);
}

void CreateBullet() {
	int i = 0;
	while (bullet_x[i] != -1) { //find empty space
		i++;
	}
	bullet_x[i] = x;
	bullet_y[i] = y;
}
void PrintBullet() {
	
	for (int i = 0; i < 10; i++) {
		if (bullet_x[i] == -1) { continue; }
		bullet_y[i]--;
		Gotoxy(bullet_x[i], bullet_y[i]);
		printf("+");
		
		Gotoxy(bullet_x[i], bullet_y[i]+1);
		printf("%c", 0);
	}
}
int CountBullet() {
	bullet_count = 0;
	for (int i = 0; i < 10; i++) {
		if (bullet_x[i] != -1) { bullet_count++; }
	}
}

int CheckBulletCollision_wall(){ //collision ->1 
	for (int i = 0; i < 10; i++) {
		if (bullet_x[i] == -1) { continue; }
		if (map[bullet_y[i]-1][bullet_x[i]] == 1) {
			//remove bullet from screen
			Gotoxy(bullet_x[i], bullet_y[i]);
			Sleep(1000);
			printf("%c", 0);
			//remove bullet from bullet_array
			bullet_x[i] = -1;
			bullet_y[i] = -1;
			//return
			return 1;
		}
	}
	return 0;
}


//Arrays
int map[26][62] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};