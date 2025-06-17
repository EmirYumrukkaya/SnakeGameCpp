#include<iostream>
#include<Windows.h>
#include"Header.h"
#include <conio.h> 
#include<vector>

HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

int SnakeX, SnakeY;
int BaitX, BaitY;
bool GameOver = false;
int Point;

int Right, Left, Up, Down;
char input;
char GoingOn;

const int width = 75;
const int height = 25;

int TailRotX, TailRotY;
int Tail[1000][2];
bool TailOrSpace;
int TailSize;
int TCounter;

void Initialization() {
	SnakeX = width / 2;
	SnakeY = height / 2;
	BaitX = rand() % width+1;
	BaitY = rand() % height;
	if (BaitX == 0) BaitX = rand() % width + 1;
	GameOver = false;
	Right=Left=Up=Down = 0;
	char GoingOn='S';
	TailOrSpace = false;
	TailSize = 0;
	TCounter = 0;
	Point = 0;
}



void RenderSettings() {

	system("cls");
	SetConsoleTextAttribute(color, FOREGROUND_RED | FOREGROUND_BLUE);
	for (int i = 0; i < width+2; i++) {
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width + 2; j++) {
			SetConsoleTextAttribute(color, FOREGROUND_RED | FOREGROUND_BLUE);
			if (j == 0 || j == width + 1) cout << "|";
			else if (SnakeX == j && SnakeY == i) { SetConsoleTextAttribute(color, FOREGROUND_RED); cout << "O"; }
			else if (BaitX == j && BaitY == i) { SetConsoleTextAttribute(color, 3); cout << "*"; }

				else {
					TailOrSpace = false;
					for (int k = 1; k <= TailSize; k++) {
						SetConsoleTextAttribute(color, FOREGROUND_GREEN);
						if (Tail[k][0] == j && Tail[k][1] == i) {
							cout << "o";
							TailOrSpace = true;
						}

					}
					if (! TailOrSpace) cout << " ";
				}
				
				
				
									
			}
			cout << endl;
			if (i + 1 == height) for (int a = 0; a < width+2; a++) cout << "-";
		
	}
	SetConsoleTextAttribute(color,12|14);
	cout << endl << "Point: " << Point;
}

void GetInput() {
	if (_kbhit()) {

		switch (_getch()) {
		case 'w':
			if (!Down) {
				Up = 1;
				Left = Right = Down = 0;
				GoingOn = 'U';
			}
			break;
		case 'd':
			if (!Left) {
				Right = 1;
				Left = Up = Down = 0;
				GoingOn = 'R';
			}
			break;
		case 'a':
			if (!Right) {
				Left = 1;
				Up = Right = Down = 0;
				GoingOn = 'L';
			}
			break;
		case 's':
			if (!Up) {
				Down = 1;
				Left = Right = Up = 0;
				GoingOn = 'D';
			};
			break;
		case 'x':
			GameOver = true;
			break;
		}


	}
}

void UpdateGame() {
	
	Tail[0][0] = SnakeX;
	Tail[0][1] = SnakeY;

	for (int i = TailSize; i >= 1; i--) {

		Tail[i][0] = Tail[i - 1][0];
		Tail[i][1] = Tail[i - 1][1];


		
	}
	

	switch(GoingOn)
	{
	case 'U':
		SnakeY--;
		break;
	case 'D':
		SnakeY++;
		break;
	case 'R':
		SnakeX++;
		break;
	case 'L':
		SnakeX--;
		break;
	}
	
	if (SnakeX == 0 || SnakeX == width + 1) GameOver = true;
	if (SnakeY == -1 || SnakeY == height) GameOver = true;
	if (SnakeX == BaitX && SnakeY == BaitY) {
		BaitX = rand() % width + 1;
		BaitY = rand() % height;
		Point += 10;
		TailSize++;
	}
	
	for (int i = 1; i <= TailSize; i++) {
		if (Tail[i][0] == SnakeX && Tail[i][1] == SnakeY) GameOver = true;
	}

}




void GameOverScreen() {

	system("cls");




	cout <<R"(
				  _____          __  __ ______    ______      ________ _____    
				 / ____|   /\   | \/   |  ____|  / __ \ \    / /  ____ | __ \ 
			        | |  __   /  \  |    / | |__    | |  | \ \  / /| |__  | |__) | 
				| | |_ | / /\ \ | |\/| |  __|   | |  | |\ \/ / |  __| |  _  /  
				| |__| |/ ____ \| |  | | |____  | |__| | \  /  | |____| | \ \  
				 \_____| /    \_\_|  |_| ____ |  \____ /  \/   |______|_|  \_\ 
		)"<<"\n";



}

