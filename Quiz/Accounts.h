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

class User;

vector<User*> users;

class User : protected Person {
	string _username;
	string _password;
public:

	User() = default;
	User(string name, string surname, string username, string password) {
		_name = name;
		_surname = surname;
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

	// Functions

	void writeFile() {
		try {
			string folder = location + "\\" + "users.txt";
			ofstream file(folder, ios::app);
			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");

			file << _username << '-' << _password << '-' << _name << '-' << _surname << '-' << endl;
		}catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	void readFile() {
		try {
			string folder = location + "\\" + "users.txt";
			ifstream file(folder, ios::in);
			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");

			string name, surname, username, password, s;

			while (!file.eof()) {
				getline(file, username, '-');
				getline(file, password, '-');
				getline(file, name, '-');
				getline(file, surname, '-');
				getline(file, s, '\n');
				User* newuser = new User(name, surname, username, password);
				users.push_back(newuser);
			}
		}catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const User& other) {
		cout << Person(other);
		cout << other._username << endl
			 << other._password << endl;

		return print;
	}

	bool operator==(const User& u1) {
		return (_username == u1._username && _password == u1._password);
	}
};

class Admin;

vector<Admin> admins;

class Admin : protected Person{
	string _adminname;
	string _password;
public:

	Admin() = default;
	Admin(string name, string surname, string adminname, string password) {
		_name = name;
		_surname = surname;
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

	// Functions

	void writeFile() {
		try {
			string folder = location + "\\" + "admins.txt";
			ofstream file(folder, ios::app);
			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");

			file << _adminname << '-' << _password << '-' << _name << '-' << _surname << '-' << endl;
		}catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	void readFile() {
		try {
			string folder = location + "\\" + "admins.txt";
			ifstream file(folder, ios::in);
			if (!file) throw exception("File couldnt be opened\n");
			if (!file.is_open()) throw exception("File couldnt be opened\n");

			string name, surname, username, password, s;

			while (!file.eof()) {
				getline(cin, username, '-');
				getline(cin, password, '-');
				getline(cin, name, '-');
				getline(cin, surname, '-');
				file >> s;
				Admin newadmin(name, surname, username, password);
				admins.push_back(newadmin);
			}
		}
		catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}

	// Operator Overloading

	friend ostream& operator<<(ostream& print, const Admin& other) {
		cout << Person(other);
		cout << other._adminname << endl
			 << other._password << endl;

		return print;
	}

	bool operator==(const Admin& u1) {
		return (_adminname == u1._name && _password == u1._password);
	}
};

User* currentUser;
Admin* currentAdmin;


void signup(bool isIn = false) {
	vector<string> selections;
	selections.push_back("User");
	selections.push_back("Admin");

	int choose = 0;
	int* set = new int[selections.size()];
	for (int i = 0; i < selections.size(); i++) set[i] = defC; set[0] = col;
	responsible(set, selections, choose, true);

	while (true) {
		responsible(set, selections, choose);
		if (_kbhit()) {
			int ascii = _getch();
			set[choose] = defC;
			choose = asciiCheck(ascii, selections, choose);
			set[choose] = col;

			if (ascii == '\r') {
				system("cls");
				string name, surname, username, password;
				if (!isIn){
					cout << "Please enter the name : ";
					getline(cin, name);
					cout << "Please enter the surname : ";
					getline(cin, surname);
				}
				cout << "Please enter username : ";
				getline(cin, username);
				cout << "Please enter password : ";
				getline(cin, password);

				if (choose == 0) {
					if (!isIn) {
						currentUser = new User(name, surname, username, password);
						currentUser->writeFile();
						user = true;
					}else {
						currentUser = new User();
						currentUser->setPassword(password);
						currentUser->setUsername(username);
						currentUser->readFile();
						for (auto& i : users) {
							if (*i == *currentUser) isLogined = true;
						}if (isLogined) menu();
					}
				}else if (choose == 1) {
					if (!isIn) {
						currentAdmin = new Admin(name, surname, username, password);
						currentAdmin->writeFile();
						user = false;
					}
					else {
						currentAdmin = new Admin();
						currentAdmin->setPassword(password);
						currentAdmin->setAdminName(username);
						currentAdmin->readFile();
						for_each(admins.begin(), admins.end(), [](Admin& u)->void {
							if (u == *currentAdmin) {
								isLogined = true;
								return;
							}
						});if (isLogined) menu();
					}
				}
			}quizMenu(selections.size(), selections, set);
			gotoXy(x, y + choose);
		}
	}
}