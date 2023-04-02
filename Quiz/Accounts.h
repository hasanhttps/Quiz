#pragma once

class Person {
protected:
	string _name;
	string _surname;
public:

	Person() = default;
	Person(string name, string surname) {
		_name = name;
		_surname;
	}


	// Acsessors

	// Setters

	void setName(string name) { _name = name; }
	void setSurname(string surname) { _surname = surname; }

	// Getters

	string getName() { return _name; }
	string getSurname() { return _surname; }

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const Person& other) {
		cout << other._name << endl
			 << other._surname << endl;

		return print;
	}
};


class User : protected Person {
	string _username;
	string _password;
public:

	User() = default;
	User(string username, string password) {
		_username = username;
		_password = password;
	}


	// Acsessors

	// Setters

	void setUsername(string username) { _username = username; }
	void setPassword(string password) { _password = password; }

	// Getters

	string getUsername() { return _username; }
	string getPassword() { return _password; }

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const User& other) {
		cout << Person(other);
		cout << other._username << endl
			 << other._password << endl;

		return print;
	}
};

class Admin : protected Person{
	string _adminname;
	string _password;
public:

	Admin() = default;
	Admin(string adminname, string password) {
		_adminname = adminname;
		_password = password;
	}


	// Acsessors

	// Setters

	void setAdminName(string adminame) { _adminname = adminame; }
	void setPassword(string password) { _password = password; }

	// Getters

	string getAdminName() { return _adminname; }
	string getPassword() { return _password; }

	friend ostream& operator<<(ostream& print, const Admin& other) {
		cout << Person(other);
		cout << other._adminname << endl
			 << other._password << endl;

		return print;
	}
};