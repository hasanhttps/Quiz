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

int asciiCheck(int ascii, vector<string> selections, int choose) {
	if (ascii == 72 || ascii == 119 || ascii == 89) {
		if (choose) choose--;
		else choose = selections.size() - 1;
	}else if (ascii == 80 || ascii == 115 || ascii == 83) {
		if (choose < selections.size() - 1) choose++;
		else choose = 0;
	}else return choose;
	return choose;
}

void responsible(int* set, vector<string> selections, int choose, bool ch) {
	getCurrentSizeT(); // Get Current Size of Terminal wit row and column
	if (ch) {
		quizMenu(selections.size(), selections, set);
		gotoXy(x, y + choose);
	}
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
	responsible(set, names, choose, true);

	while (true) {
		responsible(set, names, choose);
		if (_kbhit()) {
			int ascii = _getch();
			for (int i = 0; i < len; i++) set[i] = defC;
			choose = asciiCheck(ascii, names, choose);

			if (ascii == '\r') return names[choose];
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
	if (user)selections.push_back("Help");
	selections.push_back("Exit");
	int choose = 0;
	int* set = new int[selections.size()];
	for (int i = 0; i < selections.size(); i++) set[i] = defC; set[0] = col;
	responsible(set, selections, choose, true);

	while (true) {
		responsible(set, selections, choose);
		if (_kbhit()) {
			set[choose] = defC;
			int ascii = _getch();
			choose = asciiCheck(ascii, selections, choose);
			set[choose] = col;

			if (ascii == '\r') {
				if (choose == 0) {
					system("cls");
					currentQuiz = new Quiz;
					if (user) {
						currentQuiz->setQuizName(newQuiz());
						currentQuiz->setFromFile();
						currentQuiz->start();
					}
					else {
						currentQuiz = createQuiz();;
						currentQuiz->save();
					}
				}else if (choose == 1) {
					if (user) {
						try {
							system("cls");
							string folder = location + "\\" + "statistic.txt", username, quizname;
							int True, False, emp, total, point;
							ifstream file(folder, ios::out);
							map<string, vector<int>> statistics;

							if (!file) throw exception("File couldnt be opened\n");
							if (!file.is_open()) throw exception("File couldnt be opened\n");
							cout << left << setw(28) << "| Name | " << setw(15) << "| Quiz Name |" << setw(10) << "| True |" << setw(10) << "| False |" << setw(10) << "| Empty |" << setw(10) << "| Total |" << setw(10) << "| Point |" << setw(10) << "| Percent |" <<  endl;

							while (!file.eof()) {
								file >> username;
								file >> quizname;
								file >> True;
								file >> False;
								file >> emp;
								file >> total;
								file >> point;

								vector<int> results;
								results.push_back(True);
								results.push_back(False);
								results.push_back(emp);
								results.push_back(total);
								results.push_back(point);
								statistics[username + '-' + quizname] = results;
								
							}

							list <vector<int>> numbers;
							for (auto& i : statistics) {
								numbers.push_back(i.second);
							}

							numbers.sort([](vector<int> v1, vector<int> v2)->auto {
								float percent1 = (float(v1[4]) / float(v1[3])) * 100.0f;
								float percent2 = (float(v2[4]) / float(v2[3])) * 100.0f;
								return (percent1 > percent2);
							});

							auto j = numbers.begin();
							for (auto& i : statistics){
								username = i.first.substr(0, i.first.find('-'));
								quizname = i.first.substr(i.first.find('-') + 1, i.first.size() - 1);
								True = (*j)[0];
								False = (*j)[1];
								emp = (*j)[2];
								total = (*j)[3];
								point = (*j)[4];

								j++;
								cout << left << setw(20) << username << " :\t\t" << setw(15) << quizname << setw(10) << True
									 << setw(10) << False << setw(10) << emp << setw(10) << total << setw(10) << point 
									 << setw(10) << (float(point) / float(total)) * 100.0f << endl;
							}
							system("pause");

							file.close();
						}catch (exception& ex) { cout << ex.what(); }

					}
				}else if (choose == 3) break;
			}
			quizMenu(selections.size(), selections, set);
			gotoXy(x, y + choose);
		}
	}
}