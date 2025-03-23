#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

bool fileExists(const string &files) {
    ifstream file(files);
    return file.good();
}

void registerUser() {
    string username, password;
    cout << "Enter a username: ";
    getline(cin, username); 

    while (true) {
        cout << "Enter a password of minimum 6 characters: ";
        getline(cin, password);
        if (password.length() >= 6) {
            break;
        } else {
            cout << "Invalid Password... Must be at least 6 characters.\n";
        }
    }

    ifstream readFile("users.txt");
    string storedUsername, storedPassword;
    bool userExists = false;

    string line;
    while (getline(readFile, line)) {
        istringstream iss(line);
        getline(iss, storedUsername, '|');
        getline(iss, storedPassword); 

        if (storedUsername == username) {
            cout << "Username already exists! Try again.\n";
            userExists = true;
            break;
        }
    }
    readFile.close();

    if (!userExists) {
        ofstream writeFile("users.txt", ios::app);
        writeFile << username << "|" << password << "\n"; 
        writeFile.close();
        cout << "Registration successful!\n==========================\n";
    }
}

void loginUser() {
    if (!fileExists("users.txt")) {
        cout << "No registered users found. Please register first.\n";
        return;
    }

    string username, password;
    cout << "Enter your username: ";
    getline(cin, username); 

    ifstream readFile("users.txt");
    string storedUsername, storedPassword;
    bool userFound = false;

    string line;
    while (getline(readFile, line)) {
        istringstream iss(line);
        getline(iss, storedUsername, '|'); 
        getline(iss, storedPassword);

        if (storedUsername == username) {
            userFound = true;
            break; 
        }
    }
    readFile.close();

    if (!userFound) {
        cout << "Invalid username. Try again.\n";
        return;
    }

    for (int attempts = 1; attempts <= 5; attempts++) {
        cout << "Enter your password (Attempt " << attempts << "/5): ";
        getline(cin, password);

        if (password == storedPassword) {
            cout << "Login successful! Welcome, " << username << "!\n";
            return;
        } else {
            cout << "Incorrect password. ";
            if (attempts < 5) cout << "Try again.\n";
        }
    }

    cout << "Too many failed attempts. Exiting...\n";
}

int main() {
    int choice;
    do {
        cout << "\n1. Register\n2. Login\n3. Exit\nEnter your choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(); 

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}