#include <iostream>
#include <string>
using namespace std;

class Client {

	string name, password;
	int id;
	double balance;

public:

	void setName(string name) {
		(name >= "a" && name <= "z") || (name >= "A" && name <= "Z") ? cout << "valid name\n" : cout << "invalid name\n";
		(name.size() >= 3 && name.size() <= 20) ? cout << "valid name\n" : cout << "invalid name\n";

		this->name = name;
	}
	string getName() {
		return name;
	}
	void setPassword(string password) {
		(password.size() >= 8 && password.size() <= 20) || (password.find(" "))? cout << "valid password\n" : cout << "invalid password\n";
		this->password = password;
	}
	string getPassword() {
		return password;
	}
	void setBalance(double balance) {
		balance >= 1500 ? cout<<"valid balance\n" : cout << "invalid balance\n";
		this->balance = balance;
	}
	double getBalance() {
		return balance;
	}
	void setId(int id) {
		this->id = id;
	}
	int getId() {
		return id;
	}
