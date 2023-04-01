#pragma once


class Answer {
	bool _isCorrect = false;
	string _answer;
public:

	Answer() = default;
	Answer(string answer) { this->_answer = answer; }
	Answer(string answer, bool isCorrect) {
		this->_answer = answer;
		this->_isCorrect = isCorrect;
	}

	// Acsessors

	// Setters

	void setAnswer(string answer) { _answer = answer; }

	// Getters

	string getAnswer() { 
		return _answer; 
	}
	bool ifTrue() { return _isCorrect; }

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const Answer& other) {
		cout << other._answer << endl;

		return print;
	}
};

class Answers {
	vector<Answer> answers;
public:

	Answers() = default;
	Answers(vector<Answer> answers) { this->answers = answers; }

	// Acsessors

	// Setters

	inline void setAnswers(vector<Answer> answers) { this->answers = answers; }
	inline void setAnswer(Answer answer) { answers.push_back(answer); }

	// Getters

	inline vector<Answer>& getAnswers() { return answers; }

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const Answers& other) {
		cout << "a) " << other.answers[0];
		cout << "b) " << other.answers[1];
		cout << "c) " << other.answers[2];
		cout << "d) " << other.answers[3];

		return print;
	}
};