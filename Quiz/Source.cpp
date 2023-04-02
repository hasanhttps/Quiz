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
bool exitSt = false, change = true, user = true;

#include "Accounts.h"
#include "Answers.h"
#include "Questions.h"
#include "Quiz.h"

Quiz* currentQuiz;

#include "Functions.h"


int main() {
	// GUI

	menu();
	
}