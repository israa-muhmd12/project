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
        if (name.length() < 3 || name.length() > 20) return false;
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
        cout << "ID: " << id << "\n"
            << "Name " << name << "\n"
            << "Password" << password << "\n";
    }
    virtual ~ Person () {}
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
        if (amount > 0 && (balance - amount >= 1500) {
            balance -= amount;
            return true;
        }
        cout << "Cannot withdraw . Minimum balance is 1500 \n "
        return false;
    }

    bool transferTo(double amount, Client& other) {
        if (withdraw(amount)) {
            other.deposit(amount);
            return true;
        }
        return false;
    }
    void checkBalance() {
        cout << "Current Balance : " << balance << "\n";
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
    static Person parseToEmployee(string line); 
    static Person parseToAdmin(string line);
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
    static void saveEmployee(int id, string name, string password, double salary
        string fileName = "Employees.txt") {
        ofstream file(fileName, ios::app);
        if (file.is_open())
            file << id << "|" << name << "|" << password << "|" << salary << "\n"; 
    }
    static vector<vector<string>> getRawLines(string fileName) {
        vector<vector<string>> result;
        ifstream file(fileName);
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                result.push_back(Parser::split(line));
            }
        }
        return result;
    }

    static void clearFile(string fileName) {
        ofstream file(fileName, ios::trunc);
    }

  
    static void updateClientInFile(int id, string name, string password, double balance) {
        vector<Client> all = getClients();
        clearFile("Clients.txt");
        ofstream file("Clients.txt", ios::app);
        for (auto& c : all) {
            if (c.getId() == id) {
                c.setName(name);
                c.setPassword(password);
                c.setBalance(balance);
            }
            file << c.getId() << "|" << c.getName() << "|"
                << c.getPassword() << "|" << c.getBalance() << "\n";
        }
        cout << "Client updated in file.\n";
};

class Employee : public Person {
protected :
    double salary; 

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
        FilesHelper::updateClientInFile(id, name, password, balance); 
    }
} };
class Admin : public Employee {
private:
    vector<Employee> employees;

public:
    Admin() : Employee() {}
    Admin(int id, string name, string password, double salary)
        : Employee(id, name, password, salary) {
    }

    // ===== Clients Management =====
    void addClient(Client& c) {
        FilesHelper::saveClient(c);
        cout << "Client added.\n";
    }

    Client* searchClient(int id) {
        vector<Client> all = FilesHelper::getClients();
        for (auto& c : all)
            if (c.getId() == id) return new Client(c);
        return nullptr;
    }

    void listClients() {
        vector<Client> all = FilesHelper::getClients();
        cout << "\n--- Clients List ---\n";
        for (auto& c : all) { c.display(); cout << "---\n"; }
    }

 
    void editClient(int id, string name, string password, double balance) {
        FilesHelper::updateClientInFile(id, name, password, balance);
    }

    
    void addEmployee(Employee& e) {
        employees.push_back(e);
        FilesHelper::saveEmployee(e.getId(), e.getName(), e.getPassword(), e.getSalary());
        cout << "Employee added.\n";
    }

    Employee* searchEmployee(int id) {
        for (auto& e : employees)
            if (e.getId() == id) return &e;
        return nullptr;
    }

    void listEmployees() {
        cout << "\n--- Employees List ---\n";
        for (auto& e : employees) { e.display(); cout << "---\n"; }
    }

   
    void editEmployee(int id, string name, string password, double salary) {
        for (auto& e : employees) {
            if (e.getId() == id) {
                e.setName(name);
                e.setPassword(password);
                e.setSalary(salary);
                cout << "Employee updated.\n";
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void display() override {
        Person::display();
        cout << "Salary: " << salary << "\n";
    }
};

//==================== Main(Test) ====================
int main() {
    cout << "===== Employee Tests =====\n";
    Employee emp(101, "Ahmed Ali", "pass12345", 6000);
    emp.display();

    Client cl(500, "Nermeen Salem", "clientPass123", 3000);
    emp.addClient(cl);
    emp.listClient();

    emp.editClient(500, "Nermeen Edited", "newPass123", 4000);
    emp.listClient();

    cout << "\n===== Client Tests =====\n";
    Client c1(1, "Ali Hassan", "pass12345", 5000);
    Client c2(2, "Sara Khaled", "pass67890", 2000);
    c1.deposit(500);
    c1.checkBalance();
    c1.withdraw(300);
    c1.checkBalance();
    c1.transferTo(1000, c2);
    c2.checkBalance();

    c1.withdraw(999999);

    cout << "\n===== Admin Tests =====\n";
    Admin admin(1, "Boss Admin", "adminPass1", 15000);
    admin.display();
    Employee e2(2, "Omar Hassan", "omarPass1", 7000);
    admin.addEmployee(e2);
    admin.listEmployees();
    admin.editEmployee(2, "Omar Edited", "newPass12", 8000);
    admin.listEmployees();
}
