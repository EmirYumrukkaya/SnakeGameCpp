#include <iostream>
#include<string>
#include<Windows.h>
#include"Header.h"
#include <conio.h> 
#include<vector>
#include<fstream>
using namespace std;

void ScoreRanking(int a[], string b[]);
void ReadToTxt();
void ScoreToArray();

int ForScore[10];
string ForName[10];

extern bool GameOver;
extern int Point;
int Score=0;
int menu;
string name;

fstream ScoreFile;

int main()
{
    
    bool again = true;
    
    
    cout << "1.PLAY \n2.SCORE BOARD"<<endl;
    cin >> menu;
    switch (menu) {
    case 1:
        cout << "ENTER YOURN NICKNAME"<<endl;
        cin >> name;
        
        while (again) {
            Initialization();
            while (!GameOver) {
                RenderSettings();
                GetInput();
                UpdateGame();
                Sleep(100);
                if (GameOver) {
                    GameOverScreen();
                    cout << endl << "SCORE: " << Point;
                    if (Point > Score) Score = Point;
                    cout<< endl << "YourBestScore: " << Score;
                    ScoreToArray();
                    ScoreRanking(ForScore, ForName);
                    if (Score > ForScore[9]) {
                        ForScore[9] = Score;
                        ForName[9] = name;
                    }
                    ReadToTxt();
                    cout << endl << "1.PlayAgain 0.Exit";
                    cin >> again;
                }
            }
        }

        break;
    
    case 2:
        system("cls");
        ScoreFile.open("Score.txt", ios::in);
        string line;
        while (getline(ScoreFile,line)){
            cout << line << endl;
        }
        ScoreFile.close();
        cout << "ENTER 1 TO EXIT"<<endl;
        int hold;
        cin >> hold;
        
        break;
    }
    
    
    return 0;
}


void ScoreRanking(int a[], string b[]) {

    for (int i = 0; i < 10; i++) {

        for (int k = i; k < 10; k++) {
            int temp;
            string tempN;
            if (a[k] > a[i]) {
                temp = a[k];
                a[k] = a[i];
                a[i] = temp;

                tempN = b[k];
                b[k] = b[i];
                b[i] = tempN;
            }
        }
    }

}

void ReadToTxt() {

    ScoreFile.open("Score.txt", ios::out);
    ScoreRanking(ForScore, ForName);
    for (int i = 0; i < 10; i++) ScoreFile << ForName[i] << " " << ForScore[i] << endl;
    ScoreFile.close();
}

void ScoreToArray() {
    
    int i = 0;
    ScoreFile.open("Score.txt", ios::in);
    while (ScoreFile>>ForName[i] >>ForScore[i]) {
        i++;
    }
    
    ScoreFile.close();
}



//cpp how to creat object again and again with input