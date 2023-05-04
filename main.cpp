#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct statement {
    string name = "unknown";
    string surname = "unknown";
    string date = "null";
    int money = 0;
};

bool isCorrectStr(string a) {

    for (char i: a) {
        if ((i < 'a' || i > 'z') && (i < 'A' || i > 'Z')) {
            return false;
        }
    }
    return true;
}

bool isValidDate(string date) {
    if (date.size() != 10 || date[2] != '.' || date[5] != '.') return false;

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    if (day < 1 || day > 31 || month < 1 || month > 12) return false;

    int maxDays = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30;
    } else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28;
        }
    }
    if (day > maxDays) {
        return false;
    }
    return true;
}

int main() {
    vector<statement> array;
    string command;

    while (command != "list" && command != "add") {
        cout << R"(Enter the command ("list" or "add"): )";
        cin >> command;
    }

    if (command == "list") {
        std::ifstream file("./files/pay.txt");
        if (!file.is_open()) {
            cerr << "FILE READ ERROR";
            return 1;
        } else {
            while (!file.eof()) {
                statement person;
                getline(file, person.name, ' ');
                getline(file, person.surname, ' ');
                getline(file, person.date, ' ');
                file >> person.money;
                file.ignore();
                if (!person.name.empty()) {
                    array.push_back(person);
                }
            }
            file.close();

            for (auto& persons: array) {
                cout.width(20);
                cout << persons.name;
                cout.width(20);
                cout << persons.surname;
                cout.width(20);
                cout << persons.date;
                cout.width(20);
                cout << persons.money << endl;
            }

        }
    } else if (command == "add") {
        std::ofstream outFile("./files/pay.txt", std::ios::app);
        if (!outFile.is_open()) {
            cerr << "FILE WRITE ERROR";
            return 1;
        } else {
            statement rec;
            do {
                cout << "Enter name:";
                cin >> rec.name;

                if (!isCorrectStr(rec.name) || rec.name.empty()) {
                    cerr << "Error: invalid format name!" << endl;
                    continue;
                }
            } while (!isCorrectStr(rec.name) || rec.name.empty());

            do {
                cout << "Enter surname:";
                cin >> rec.surname;

                if (!isCorrectStr(rec.surname) || rec.surname.empty()) {
                    cerr << "Error: invalid format surname!" << endl;
                    continue;
                }
            } while (!isCorrectStr(rec.surname) || rec.surname.empty());

            do {
                cout << "Enter date (DD.MM.YYYY):";
                cin >> rec.date;

                if (!isValidDate(rec.date) || rec.date.empty()) {
                    cerr << "Error: invalid format date!" << endl;
                    continue;
                }
            } while (!isValidDate(rec.date) || rec.date.empty());


            cout << "Enter money:";
            cin >> rec.money;


            outFile << rec.name << ' ' << rec.surname << ' '
                    << rec.date << ' ' << rec.money << endl;
        }
        outFile.close();
    }
    return 0;
}
