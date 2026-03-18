#pragma once
#include <iostream>
#include <string>
#include "Admin.h"
#include "EmployeeManager.h"
#include "FileManager.h"

using namespace std;

class AdminManager {
public:
    static void printAdminMenu() {
        system("cls");
        cout << "==== Admin Menu ====" << endl;
        cout << "(1) Add New Employee" << endl;
        cout << "(2) List All Employees" << endl;
        cout << "(3) Search for Employee" << endl;
        cout << "(4) Edit Employee Info" << endl;
        cout << "(5) Display My Info" << endl;
        cout << "(6) Update Password" << endl;
        cout << "(7) Logout" << endl;
        cout << "Choice: ";
    }

    static Admin* login(int id, string password) {
        for (int i = 0; i < allAdmins.size(); i++) {
            if (allAdmins[i].getId() == id && allAdmins[i].getpass() == password) {
                return &allAdmins[i];
            }
        }
        return nullptr;
    }

    static bool adminOptions(Admin* admin) {
        printAdminMenu();
        int choice, id;
        string name, pass;
        double salary;
        if (!(cin >> choice)) { cin.clear(); cin.ignore(); return true; }

        switch (choice) {
        case 1: {
            int nextId = FilesHelper::getLast(E_last_Id_path) + 1;
            cout << "Name: "; cin >> name;
            cout << "Pass: "; cin >> pass;
            cout << "Salary: "; cin >> salary;
            Employee e(nextId, name, pass, salary);
            admin->addEmployee(e);
            FilesHelper::saveEmployee(e);
            cout << "\nEmployee Added Successfully!";
            break;
        }
        case 2: admin->listEmployees(); break;
        case 3:
            cout << "Enter Employee ID: "; cin >> id;
            if (admin->searchEmployee(id)) admin->searchEmployee(id)->displayInfo();
            else cout << "\nEmployee not found!";
            break;
        case 4: { 
            cout << "Enter Employee ID to edit: "; cin >> id;
            Employee* e = admin->searchEmployee(id);
            if (e != nullptr) {
                cout << "New Name: "; cin >> name;
                cout << "New Password: "; cin >> pass;
                cout << "New Salary: "; cin >> salary;
                admin->editEmployee(e, name, pass, salary);
                cout << "\nEmployee info updated!";
            }
            else cout << "\nEmployee not found!";
            break;
        }
        case 5: admin->displayInfo(); break;
        case 6: ClientManager::updatePassword(admin); break;
        case 7: return false; // Logout
        }
        system("pause");
        return true;
    }
};
