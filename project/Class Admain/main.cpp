#include <iostream>
#include <string>
#include <cctype>

using namespace std;
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


int main()
{

}


