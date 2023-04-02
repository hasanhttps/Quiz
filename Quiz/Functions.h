#pragma once

inline void color(int col) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
}

void gotoXy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void getCurrentSizeT() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	if (columns != csbi.srWindow.Right - csbi.srWindow.Left + 1) {
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		change = true;
	}else if (rows != csbi.srWindow.Bottom - csbi.srWindow.Top + 1) {
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		change = true;
	}else change = false;
}

int x, y;

void quizMenu(int len, vector<string> names, int* set) {
	system("cls");
	x = columns / 2 - 5;
	for (int i = 0; i < len; i++) {
		y = rows / 2 - len + 1;
		gotoXy(x, y + i);
		color(set[i]);
		cout << names[i];
	}color(defC);
}

string newQuiz() {
	ifstream file(location + "\\" + "Quiz Names.txt", ios::in);
	if (!file) throw exception("File couldnt be found\n");
	if (!file.is_open()) throw exception("File couldnt be opened\n");

	vector<string> names;
	string name;
	while (!file.eof()) {
		getline(file, name);
		if (name != "") names.push_back(name);
	}
	int choose = 0, len = names.size();
	int* set = new int[len] { defC }; set[0] = col;
	for (int i = 1; i < len; i++) set[i] = defC;
	quizMenu(len, names, set);
	file.close();

	while (true) {
		getCurrentSizeT();// Get Current Size of Terminal wit row and column
		if (change) {
			quizMenu(len, names, set);
			gotoXy(x, y + choose);
		}if (_kbhit()) {
			int ascii = _getch();
			for (int i = 0; i < len; i++) set[i] = defC;
			if (ascii == 72 || ascii == 119 || ascii == 89) {
				if (choose) choose--;
				else choose = len - 1;
			}else if (ascii == 80 || ascii == 115 || ascii == 83) {
				if (choose < len - 1) choose++;
				else choose = 0;
			}else if (ascii == '\r') return names[choose];
			set[choose] = col;
			quizMenu(len, names, set);
			gotoXy(x, y + choose);
		}
	}
}


Quiz* createQuiz() {
	string quizName, quest, ans;
	int questionCount;
	cout << "Enter Quiz name : ";
	getline(cin, quizName);
	cout << "Please enter the question count : ";
	cin >> questionCount;
	Questions questions;
	cin.ignore(1);

	while (questionCount--) {
		system("cls");
		Question* question = new Question;
		Answers* answers = new Answers;
		ushort point;

		cout << "Please enter the question : ";
		getline(cin, quest);
		question->setQuestion(quest);
		cout << "Please enter the point of question : ";
		cin >> point;
		question->setPoint(point);
		cin.ignore(1);
		cout << "Please enter the correct answer : ";
		getline(cin, ans);
		Answer corans(ans, true);
		answers->setAnswer(corans);

		for (int i = 0; i < 3; i++) {
			cout << "Please enter the wrong answer : ";
			getline(cin, ans);
			Answer answer(ans);
			answers->setAnswer(answer);
		}questions.setQuestion(question, answers);
	}
	Quiz* quiz = new Quiz(quizName);
	quiz->setQuestions(questions);
	
	return quiz;
}

void menu() {
	vector<string> selections;
	if (!user) selections.push_back("Create Quiz");
	selections.push_back("New Quiz");
	selections.push_back("Leader Top (10)");
	if (user )selections.push_back("Help");
	selections.push_back("Exit");
	int choose = 0;
	int* set = new int[selections.size()];
	for (int i = 0; i < selections.size(); i++) set[i] = defC; set[0] = col;

	while (true) {
		getCurrentSizeT();// Get Current Size of Terminal wit row and column
		if (change) {
			quizMenu(selections.size(), selections, set);
			gotoXy(x, y + choose);
		}if (_kbhit()) {
			int ascii = _getch();
			set[choose] = defC;

			if (ascii == 72 || ascii == 119 || ascii == 89) {
				if (choose) choose--;
				else choose = selections.size() - 1;
			}else if (ascii == 80 || ascii == 115 || ascii == 83) {
				if (choose < selections.size() - 1) choose++;
				else choose = 0;
			} if (ascii == '\r') {
				if (choose == 0) {
					system("cls");
					currentQuiz = new Quiz;
					if (user) {
						currentQuiz->setQuizName(newQuiz());
						currentQuiz->setFromFile();
						currentQuiz->start();
					}
				}else if (choose == 1) {

				}else if (choose == 3) break;
			}set[choose] = col;
			quizMenu(selections.size(), selections, set);
			gotoXy(x, y + choose);
		}
	}
}