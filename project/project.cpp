#include <iostream>
#include <string>
using namespace std;

class Client {
//attributes
	string name, password;
	int id;
	double balance;

public:
//settter and getter
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
// Deposit function
void deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}
// Withdraw function
bool withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}
// Transfer money to another client
bool transferTo(double amount, Client& otherClient) {
    if (withdraw(amount)) {
        otherClient.deposit(amount);
        return true;
    }
    return false;
}
// Check balance
double checkBalance() {
    return balance;
}
// Display client data
void display() {
    cout << "Client ID: " << id << endl;
    cout << "Client Name: " << name << endl;
    cout << "Balance: " << balance << endl;
}
};
class Employee {

private:
    int id;
    string name;
    string password;
    double salary;

public:

    void setId(int id) {
        this->id = id;
    }

    int getId() {
        return id;
    }

    void setName(string name) {

        if (name.size() >= 5 && name.size() <= 20) {

            bool valid = true;

            for (int i = 0; i < name.size(); i++) {
                if (!isalpha(name[i])) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                this->name = name;
            }
        }
    }

    string getName() {
        return name;
    }

    void setPassword(string password) {

        if (password.size() >= 8 && password.size() <= 20) {
            this->password = password;
        }
    }

    string getPassword() {
        return password;
    }

    void setSalary(double salary) {

        if (salary >= 5000) {
            this->salary = salary;
        }
    }

    double getSalary() {
        return salary;
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};
