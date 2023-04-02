#include <Windows.h>
#include <algorithm>
#include <iostream>
#include <direct.h>
#include <conio.h>
#include <iomanip>
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
int defC = 9, col = 137, columns, rows, x, y;
bool exitSt = false, change = true, user = true, isLogined = false;

// Prototype

void gotoXy(int x, int y);
void color(int set);
void responsible(int* set, vector<string> selections, int choose, bool ch = change);
int asciiCheck(int ascii, vector<string> selections, int choose);
void quizMenu(int len, vector<string> names, int* set);
void menu();

#include "Accounts.h"
#include "Answers.h"
#include "Questions.h"
#include "Quiz.h"

Quiz* currentQuiz;
#include "Functions.h"


int main() {
	// GUI

	vector<string> selections;
	selections.push_back("Sign Up");
	selections.push_back("Sign In");

	int choose = 0;
	int* set = new int[selections.size()];
	set[0] = col;
	set[1] = defC;

	while (true) {
		responsible(set, selections, choose);
		if (_kbhit()) {
			int ascii = _getch();
			set[choose] = defC;
			choose = asciiCheck(ascii, selections, choose);
			set[choose] = col;

			if (ascii == '\r') {
				system("cls");
				if (choose == 0) {
					signup();
				}else if (choose == 1) {
					signup(true);
				}
				
			}
			quizMenu(selections.size(), selections, set);
			gotoXy(x, y + choose);
		}
	}
	
}