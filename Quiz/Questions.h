#pragma once

class Question {
	string _question;
	ushort _point;
public:

	Question() = default;
	Question(ushort point, string newquestion) {
		_question = newquestion;
		_point = point;
	}

	// Acsessors

	// Setters

	inline void setQuestion(string question) { _question = question; }
	inline void setPoint(ushort point) { _point = point; }

	// Getters

	inline string getQuestion() { return _question; }
	inline int getPoint() const { return _point; }

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const Question& other) {
		cout << other._question << "\n(" << other._point << ")" << endl;

		return print;
	}

};

class Questions {
	map<Question*, Answers*> questions;

public:

	Questions() = default;
	Questions(map<Question*, Answers*> questions) {
		this->questions = questions; 
	}

	// Acsessors

	// Setters

	inline void setQuestions(map<Question*, Answers*> questions) { this->questions = questions; }
	inline void setQuestion(Question* question, Answers* answers) { this->questions[question] = answers; }

	// Getters

	inline map<Question*, Answers*>& getQuestions() { return questions; }
	inline vector<Answer>& getAnswer() { return questions[0]->getAnswers(); }
	inline const int size() { return questions.size(); }

	// Functions

	int totalPoint() {
		int sum = 0;
		for (auto& i : questions) sum += (*i.first).getPoint();
		return sum;
	}

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const Questions& other) {
		for (auto& i : other.questions) {
			cout << *i.first << endl;
			cout << *i.second << endl;
		}

		return print;
	}
};