#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct Employee {
    int id;
    string name;
    string designation;
    int dailyHours[30]; // Daily working hours for a month
};

// Function prototypes
void loadEmployees(Employee* &employees, int &employeeCount);
void saveEmployees(Employee* employees, int employeeCount);
void addEmployee(Employee* &employees, int &employeeCount);
void updateWorkingHours(Employee* employees, int employeeCount);
void viewProductivityReport(Employee* employees, int employeeCount);

int main() {
    Employee* employees = nullptr;
    int employeeCount = 0;

    loadEmployees(employees, employeeCount);

    int choice;
    do {
        cout << "\n==== Employee Work Tracking System ====" << endl;
        cout << "1. Add New Employee" << endl;
        cout << "2. Update Working Hours" << endl;
        cout << "3. View Monthly Productivity Report" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(employees, employeeCount);
                break;
            case 2:
                updateWorkingHours(employees, employeeCount);
                break;
            case 3:
                viewProductivityReport(employees, employeeCount);
                break;
            case 4:
                saveEmployees(employees, employeeCount);
                cout << "Exiting... Employee data saved." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    delete[] employees;
    return 0;
}

void loadEmployees(Employee* &employees, int &employeeCount) {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cerr << "Error loading employee file. Starting with no employees." << endl;
        return;
    }

    inFile >> employeeCount;
    employees = new Employee[employeeCount];
    for (int i = 0; i < employeeCount; i++) {
        inFile >> employees[i].id >> employees[i].name >> employees[i].designation;
        for (int j = 0; j < 30; j++) {
            inFile >> employees[i].dailyHours[j];
        }
    }
    inFile.close();
}

void saveEmployees(Employee* employees, int employeeCount) {
    ofstream outFile("employees.txt");
    outFile << employeeCount << endl;
    for (int i = 0; i < employeeCount; i++) {
        outFile << employees[i].id << " " << employees[i].name << " " << employees[i].designation;
        for (int j = 0; j < 30; j++) {
            outFile << " " << employees[i].dailyHours[j];
        }
        outFile << endl;
    }
    outFile.close();
}

void addEmployee(Employee* &employees, int &employeeCount) {
    Employee* newEmployees = new Employee[employeeCount + 1];
    for (int i = 0; i < employeeCount; i++) {
        newEmployees[i] = employees[i];
    }

    delete[] employees;
    employees = newEmployees;

    cout << "\nEnter Employee ID: ";
    cin >> employees[employeeCount].id;
    cout << "Enter Employee Name: ";
    cin >> employees[employeeCount].name;
    cout << "Enter Employee Designation: ";
    cin >> employees[employeeCount].designation;

    for (int i = 0; i < 30; i++) {
        employees[employeeCount].dailyHours[i] = 0;
    }

    employeeCount++;
    cout << "Employee added successfully!" << endl;
}

void updateWorkingHours(Employee* employees, int employeeCount) {
    int id, day, hours;
    cout << "\nEnter Employee ID: ";
    cin >> id;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            cout << "Enter day of the month (1-30): ";
            cin >> day;
            if (day < 1 || day > 30) {
                cout << "Invalid day. Please enter a value between 1 and 30." << endl;
                return;
            }
            cout << "Enter hours worked: ";
            cin >> hours;
            employees[i].dailyHours[day - 1] = hours;
            cout << "Working hours updated successfully!" << endl;
            return;
        }
    }
    cout << "Employee not found." << endl;
}

void viewProductivityReport(Employee* employees, int employeeCount) {
    cout << "\n==== Monthly Productivity Report ====" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Designation" << "Total Hours" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < employeeCount; i++) {
        int totalHours = 0;
        for (int j = 0; j < 30; j++) {
            totalHours += employees[i].dailyHours[j];
        }
        cout << left << setw(10) << employees[i].id
             << setw(20) << employees[i].name
             << setw(20) << employees[i].designation
             << totalHours << endl;
    }
}
