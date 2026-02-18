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

 protected :
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
    class Admin : public Employee {
    public:
        void display() {
            cout << "Admin Data:" << endl;
            cout << "ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Salary: " << salary << endl;
        }

        Admin() = default;
    };

/* ================= Validation Class ================= */

class Validation {
public:

    static bool isValidName(string name) {

        if (name.length() < 3 || name.length() > 20)
            return false;

        for (int i = 0; i < name.length(); i++) {

     
if (!((name[i] >= 'A' && name[i] <= 'Z') ||
                  (name[i] >= 'a' && name[i] <= 'z'))) {
                return false;
            }
        }
        return true;
    }

    static bool isValidPassword(string password) {

        if (password.length() < 8 || password.length() > 20)
            return false;

        for (int i = 0; i < password.length(); i++) {

 if (password[i] == ' ')
                return false;
        }
        return true;
    }

    static bool isValidBalance(double balance) {
        return balance >= 1500;
    }

    static bool isValidSalary(double salary) {
        return salary >= 5000;
    }
};

/* ================= Admin Class ================= */

class Admin {
protected:
    int id;
    string name;
    string password;

public:
    Admin() {
        id = 0;
        name = "";
        password = "";
    }

    Admin(int id, string name, string password) {
        this->id = id;
        setName(name);
        setPassword(password);
    }

    void setId(int id) {
        this->id = id;
    }

    void setName(string name) {
        if (Validation::isValidName(name)) {
            this->name = name;
        }
        else {
            cout << "Invalid Name!\n";
        }
    }

    void setPassword(string password) {
        if (Validation::isValidPassword(password)) {
            this->password = password;
        }
        else {
            cout << "Invalid Password!\n";
        }
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getPassword() {
        return password;
    }
};


/* ================= Test ================= */

int main() {

    Person p1(1, "Nermeen", "password123");

    cout << "ID: " << p1.getId() << endl;
    cout << "Name: " << p1.getName() << endl;
    cout << "Password: " << p1.getPassword() << endl;

    return 0;
}

