#include <iostream>
#include <string>
#include <cctype>
#include <fstream>   
#include <sstream>   
#include <vector>

using namespace std;

class Validation {
public:
    static bool isValidName(string name) {
        if (name.length() < 5 || name.length() > 20) return false;
        for (char c : name) {
            if (!isalpha(c)) return false;
        }
        return true;
    }

    static bool isValidPassword(string password) {
        if (password.length() < 8 || password.length() > 20) return false;
        if (password.find(' ') != string::npos) return false;
        return true;
    }

    static bool isValidBalance(double balance) {
        return balance >= 1500;
    }

    static bool isValidSalary(double salary) {
        return salary >= 5000;
    }
};

class Person {
protected:
    int id;
    string name;
    string password;

public:
    Person() : id(0) {}
    Person(int id, string name, string password) {
        this->id = id;
        setName(name);
        setPassword(password);
    }

    void setId(int id) { this->id = id; }
    int getId() { return id; }

    void setName(string name) {
        if (Validation::isValidName(name)) this->name = name;
        else cout << "Invalid Name!" << endl;
    }
    string getName() { return name; }

    void setPassword(string password) {
        if (Validation::isValidPassword(password)) this->password = password;
        else cout << "Invalid Password!" << endl;
    }
    string getPassword() { return password; }

    virtual void display() {
        cout << "ID: " << id << "\nName: " << name << endl;
    }
};

class Client : public Person {
private:
    double balance;

public:
    Client() : Person(), balance(0) {}
    Client(int id, string name, string password, double balance) : Person(id, name, password) {
        setBalance(balance);
    }

    void setBalance(double balance) {
        if (Validation::isValidBalance(balance)) this->balance = balance;
        else cout << "Invalid Balance!" << endl;
    }
    double getBalance() { return balance; }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    bool transferTo(double amount, Client& other) {
        if (withdraw(amount)) {
            other.deposit(amount);
            return true;
        }
        return false;
    }

    void display() override {
        Person::display();
        cout << "Balance: " << balance << endl;
    }
};

class Parser {
public:
    static vector<string> split(string line) {
        stringstream ss(line);
        string part;
        vector<string> parts;
        while (getline(ss, part, '|')) {
            parts.push_back(part);
        }
        return parts;
    }

    static Client parseToClient(string line) {
        vector<string> data = split(line);
        Client c;
        if (data.size() < 4) return c;
        c.setId(stoi(data[0]));
        c.setName(data[1]);
        c.setPassword(data[2]);
        c.setBalance(stod(data[3]));
        return c;
    }
};

class FilesHelper {
public:
    static void saveClient(Client c) {
        ofstream file("Clients.txt", ios::app);
        if (file.is_open()) {
            file << c.getId() << "|" << c.getName() << "|" << c.getPassword() << "|" << c.getBalance() << endl;
            file.close();
        }
    }

    static vector<Client> getClients() {
        vector<Client> clients;
        string line;
        ifstream file("Clients.txt");
        while (getline(file, line)) {
            if (!line.empty()) clients.push_back(Parser::parseToClient(line));
        }
        file.close();
        return clients;
    }
};

class Employee : public Person {
protected:
    int id;
    string name;
    string password;

public:
    Employee() : Person(), salary(0) {}
    Employee(int id, string name, string password, double salary) : Person(id, name, password) {
        setSalary(salary);
    }

    void setSalary(double salary) {
        if (Validation::isValidSalary(salary)) {
            this->salary = salary;
        }
        else {
            cout << "Invalid Salary! Minimum salary is 5000." << endl;
        }
    }

    double getSalary() { return salary; }

    void display() override {
        Person::display();
        cout << "Salary: " << salary << endl;
    }

    void addClient(Client& client) {
        FilesHelper::saveClient(client);
        cout << "Client added and saved successfully.\n";
    }

    Client* searchClient(int id) {
        vector<Client> allClients = FilesHelper::getClients();
        for (int i = 0; i < allClients.size(); i++) {
            if (allClients[i].getId() == id) {
                return new Client(allClients[i]);
            }
        }
        return nullptr;
    }

    void listClient() {
        vector<Client> allClients = FilesHelper::getClients();
        cout << "\n--- All Clients List ---\n";
        for (int i = 0; i < allClients.size(); i++) {
            allClients[i].display();
            cout << "----------------------\n";
        }
    }

    void editClient(int id, string name, string password, double balance) {
        cout << "Edit request for ID " << id << " received.\n";
    }
    // ====== Clients Management ======

    void addClient(Client c) {
        clients.push_back(c);
    }

    Client* searchClient(int id) {
        for (int i = 0; i < clients.size(); i++) {
            if (clients[i].getId() == id)
                return &clients[i];
        }
        return nullptr;
    }

    void listClients() {
        for (int i = 0; i < clients.size(); i++) {
            clients[i].display();
            cout << "------------------\n";
        }
    }

    void editClient(int id, string newName) {
        Client* c = searchClient(id);
        if (c != nullptr) {
            c->setName(newName);
        }
    }

    // ====== Employees Management ======

    void addEmployee(Employee e) {
        employees.push_back(e);
    }

    void getAllEmployees() {
        for (int i = 0; i < employees.size(); i++) {
            employees[i].display();
            cout << "------------------\n";
        }
    }

    void removeAllEmployees() {
        employees.clear();
    }
};

int main() {
    Employee emp(101, "AhmedEmp", "pass12345", 6000);
    Client cl(500, "Nermeen", "clientPass123", 3000);

    emp.addClient(cl);
    emp.listClient();

    return 0;
}
