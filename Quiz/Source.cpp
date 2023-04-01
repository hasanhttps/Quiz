#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <direct.h>
#include <conio.h>
#include <fstream>
#include <random>
#include <string>
#include <chrono>
#include <vector>
#include <map>

using namespace std;
typedef unsigned short ushort;

// Global Variables

string location = "C:\\Users\\Public\\Downloads";
int defC = 9, col = 137, columns, rows;
bool exitSt = false, change = true;

#include "Answers.h"
#include "Questions.h"
#include "Quiz.h"
#include "Functions.h"


int main() {
	// GUI

	Quiz* currentQuiz;
	int choose = 0;
	int set[4] = { col, defC, defC, defC };

	while (true) {
		getCurrentSizeT();// Get Current Size of Terminal wit row and column
		if (change) {
			menu(set, columns / 2 - 8, rows / 2 - 1);
			gotoXy(columns / 2 - 8, rows / 2 - 1 + choose);
		}if (_kbhit()) {
			int ascii = _getch();
			set[0] = defC;
			set[1] = defC;
			set[2] = defC;
			set[3] = defC;

			if (ascii == 72 || ascii == 119 || ascii == 89) {
				if (choose) choose--;
				else choose = 3;
			}else if (ascii == 80 || ascii == 115 || ascii == 83) {
				if (choose < 3) choose++;
				else choose = 0;
			} if (ascii == '\r') {
				if (choose == 0){
					system("cls");
					Quiz* newquiz = createQuiz();
					newquiz->save();
				}
				else if (choose == 1) {
					system("cls");
					currentQuiz = new Quiz;
					currentQuiz->setQuizName(newQuiz());
					currentQuiz->setFromFile();
					currentQuiz->start();
				}
				else if (choose == 3) break;
			}set[choose] = col;
			menu(set, columns / 2 - 8, rows / 2 - 1);
			gotoXy(columns / 2 - 8, rows / 2 - 1 + choose);
		}
	}
}