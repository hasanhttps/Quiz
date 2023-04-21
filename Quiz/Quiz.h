#pragma once 

class Quiz {
	string _quizname;
	Questions _questions;
	int totalPoint;

	string typecast_int(int data) {
		int clonedata = data;
		int len = 0;
		while (clonedata != 0) {
			len++;
			clonedata /= 10;
		} string int_str;
		int_str.resize(len);
		for (int i = len - 1; i >= 0; i--) {
			int_str[i] = (data % 10) + 48;
			data /= 10;
		} return int_str;
	}

	int typecast_str(string data) {
		int str_int = 0;
		for (int i = 0; i < data.size(); i++) str_int = str_int * 10 + data[i] - 48;
		return str_int;
	}

public:

	Quiz() = default;
	Quiz(string quizname) { 
		if (quizname[quizname.size() - 4] != '.') quizname.append(".txt"); 
		_quizname = quizname;
		ofstream file(location + "\\" + "Quiz Names.txt", ios::app);
		if (!file) throw exception("File couldnt be opened\n");
		if (!file.is_open()) throw exception("File couldnt be opened\n");
		file << _quizname << endl;
		file.close();
	}

	// Acsessors

	// Setters

	inline void setQuizName(string quizname) { 
		if (quizname[quizname.size() - 4] != '.') quizname.append(".txt");
		_quizname = quizname;
	}
	inline void setQuestions(Questions questions) { 
		_questions = questions; 
		totalPoint += _questions.totalPoint();
	}

	// Getters

	inline string getQuizName() { return _quizname; }
	inline Questions getQuestion() { return _questions; }

	// Functions

	void save() {
		try {
			string folder = location + "\\" + "Quizs";
			_mkdir(folder.c_str());

			ofstream file(folder + "\\" + _quizname, ios::out);

			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");

			for (auto& i : _questions.getQuestions()) {
				file << i.first->getQuestion() << endl;
				file << typecast_int(i.first->getPoint()) << endl;
				file << (i.second->getAnswers()[0]).getAnswer() << endl;
				for (int j = 1; j < 4; j++) file << (i.second->getAnswers()[j]).getAnswer() << "-";
				file << endl;
			}file.close();
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	void setFromFile() {
		ifstream file(location + "\\" + "Quizs\\" + _quizname, ios::in);
		if (!file) throw exception("File couldnt be found\n");
		if (!file.is_open()) throw exception("File couldnt be opened\n");

		string squestion;
		string spoint;
		ushort point;
		string scorans;
		string sanswer;
		string st = "";

		while (!file.eof()) {
			getline(file, squestion);
			Question* question = new Question;
			question->setQuestion(st + squestion);
			getline(file, spoint);
			point = typecast_str(spoint);
			question->setPoint(point);
			getline(file, scorans);
			Answer corans(scorans, true);
			Answers* answers = new Answers;
			answers->setAnswer(corans);
			for (int i = 0; i < 3; i++) {
				getline(file, sanswer,  '-');
				Answer answer(sanswer);
				answers->setAnswer(answer);
			}file >> st;
			_questions.setQuestion(question, answers);
			totalPoint += question->getPoint();
		} file.close();
	}

	void start() {

		system("cls");
		int* answers = new int[_questions.size()];
		for (int i = 0; i < _questions.size(); i++) answers[i] = -1;
		bool back = false, next = false, save = false;
		auto& m = _questions.getQuestions();
		auto it = m.cbegin();
		int random = rand() % m.size(), count = 0, True = 0, False = 0, Empty = 0;
		advance(it, random);

		// Randomize Answers

		for (auto& i : _questions.getQuestions()) {
			auto& v = (i.second)->getAnswers();
			unsigned seed = chrono::system_clock::now()
				.time_since_epoch()
				.count();
			shuffle(begin(v), end(v), default_random_engine(seed));
		}

		// Questions

		for (auto j = _questions.getQuestions().begin(); j != _questions.getQuestions().end(); count++) {
			if (back && count > 0) {
				j--;
				count--;
			}auto& i = *j;
			system("cls");
			cout << _quizname << endl;
			cout << count + 1 << "." << *i.first << endl;

			auto& v = (i.second)->getAnswers();
			int* set = new int[v.size() + 2] {defC};
			int choose = 0;

			while (true) {
				for (int j = 0; j < v.size() + 3; j++) set[j] = defC;
				set[choose] = col;
				for (int j = 0; j < v.size(); j++) {
					gotoXy(0, 4 + j);
					color(set[j]);
					cout << char(97 + j) << ") " << v[j];
				}gotoXy(0, 9);
				color(set[4]);
				cout << "Previous";
				gotoXy(0, 10);
				color(set[5]);
				cout << "Next";
				gotoXy(0, 11);
				color(set[6]);
				cout << "Save";
				color(defC);
				if (choose > v.size() - 1) gotoXy(0, 5 + choose);
				else gotoXy(0, 4 + choose);
				
				int ascii = _getch();
				for (int j = 0; j < v.size() + 3; j++) set[j] = defC;
				if (ascii == 72 || ascii == 119 || ascii == 89) {
					if (choose) choose--;
					else choose = v.size() + 2;
				}
				else if (ascii == 80 || ascii == 115 || ascii == 83) {
					if (choose < v.size() + 2) choose++;
					else choose = 0;
				}else if (ascii == '\r') {
					back = false;
					if (choose == v.size() && count > 0) {
						count -= 1;
						j--;
						back = true;
						break;
					}else if (choose == v.size() + 1 && count < v.size()) next = true;
					else if (choose == v.size() + 2) save = true;
					else if (choose >= 0 && choose < v.size()) {
						answers[count] = choose;
						next = true;
					}if (!(count == 0 && choose == v.size()) && !(count == _questions.getQuestions().size() - 1 && choose == v.size() + 1)) break;
				}
			}
			if (save) break;
			if (next) j++;
		}
		// Check Answers

		int index = 0, point = 0;
		for (auto& i : _questions.getQuestions()) {
			auto& v = (i.second)->getAnswers();
			auto& trueanswers = i.second;
			string answer = trueanswers->getTrueAnswer();

			if (answers[index] < v.size()) {
				if (v[answers[index]].getAnswer() == answer) {
					True++;
					point += i.first->getPoint();
				}
			}else Empty++;

			index++;
		}False = (_questions.getQuestions().size()) - (True + Empty);

		// Print Result

		system("cls");
		cout << "True : " << True << endl;
		cout << "False : " << False << endl;
		cout << "Empty : " << Empty << endl << endl;
		cout << "Exam Score : " << 100 << '/' << float(float(float(point) / _questions.totalPoint())) * 100.0f << endl;
		string folder = location + "\\" + "statistic.txt";
		ofstream file(folder, ios::app);

		if (!file) throw exception("File couldnt be opened\n");
		if (!file.is_open()) throw exception("File couldnt be opened\n");

		file << currentUser->getUsername() << _quizname << ' ' << True << ' ' << False << ' ' << Empty << ' ' << _questions.totalPoint() << ' ' << point << endl;

		system("pause");
	}

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const Quiz& other) {
		cout << other._quizname << endl;
		cout << other.totalPoint << endl;
		cout << other._questions;

		return print;
	}
};