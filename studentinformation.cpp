#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};

// Function to add a new student
void addStudent() {
    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    Student student;
    cout << "Enter roll number: ";
    cin >> student.rollNumber;
    cin.ignore(); // Ignore newline character in input buffer
    cout << "Enter name: ";
    getline(cin, student.name);
    cout << "Enter division: ";
    getline(cin, student.division);
    cout << "Enter address: ";
    getline(cin, student.address);

    // Writing student information to the file
    outFile << student.rollNumber << "," << student.name << "," << student.division << "," << student.address << endl;
    cout << "Student information added successfully." << endl;

    outFile.close();
}

// Function to delete a student by roll number
void deleteStudent(int rollNumber) {
    ifstream inFile("students.txt");
    ofstream tempFile("temp.txt");
    if (!inFile || !tempFile) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        int currentRollNumber = stoi(line.substr(0, line.find(',')));
        if (currentRollNumber != rollNumber) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student information deleted successfully." << endl;
    } else {
        cout << "Student with roll number " << rollNumber << " not found." << endl;
    }
}

// Function to display information of a particular student by roll number
void displayStudent(int rollNumber) {
    ifstream inFile("students.txt");
    if (!inFile) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        int currentRollNumber = stoi(line.substr(0, line.find(',')));
        if (currentRollNumber == rollNumber) {
            cout << line << endl;
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "Student with roll number " << rollNumber << " not found." << endl;
    }
}

int main() {
    int choice;
    cout << "Welcome to Student Information System" << endl;
    do {
        cout << "\n1. Add Student\n2. Delete Student\n3. Display Student\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2: {
                int rollNumber;
                cout << "Enter roll number of student to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            }
            case 3: {
                int rollNumber;
                cout << "Enter roll number of student to display: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            }
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}
