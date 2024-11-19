#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

struct FriendInfo {
    string last_name;
    string first_name;
    string phone_number;
    int birthday[3]; // [day, month, year]
};

void Create(const string& file_name);
void Print(const string& file_name);
void AddToFile(const string& file_name);
void Search(const string& file_name);
bool IsValidDate(int day, int month, int year);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string file_name;
    cout << "Введіть ім'я файлу: ";
    getline(cin, file_name);

    int menu_item;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1 - Створити список друзів\n";
        cout << "2 - Переглянути список\n";
        cout << "3 - Додати до списку\n";
        cout << "4 - Пошук за номером телефону\n";
        cout << "0 - Вихід\n";
        cout << "Виберіть дію: ";
        cin >> menu_item;

        switch (menu_item) {
        case 1:
            Create(file_name);
            break;
        case 2:
            Print(file_name);
            break;
        case 3:
            AddToFile(file_name);
            break;
        case 4:
            Search(file_name);
            break;
        case 0:
            return 0;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }
}

void Create(const string& file_name) {
    ofstream file(file_name, ios::out);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    cin.ignore();
    string keep;

    do {
        FriendInfo friend_info;
        cout << "Прізвище: ";
        getline(cin, friend_info.last_name);
        cout << "Ім'я: ";
        getline(cin, friend_info.first_name);
        cout << "Номер телефону: ";
        getline(cin, friend_info.phone_number);

        cout << "День народження (дд мм рррр): ";
        cin >> friend_info.birthday[0] >> friend_info.birthday[1] >> friend_info.birthday[2];

        if (!IsValidDate(friend_info.birthday[0], friend_info.birthday[1], friend_info.birthday[2])) {
            cout << "Некоректна дата! Введіть дані знову.\n";
            cin.ignore();
            continue;
        }

        file << friend_info.last_name << endl
            << friend_info.first_name << endl
            << friend_info.phone_number << endl
            << friend_info.birthday[0] << " " << friend_info.birthday[1] << " " << friend_info.birthday[2] << endl;

        cin.ignore();
        cout << "Продовжити введення? (Y/N): ";
        getline(cin, keep);
    } while (keep == "Y" || keep == "y");

    file.close();
}

void Print(const string& file_name) {
    ifstream file(file_name, ios::in);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    FriendInfo friend_info;
    int index = 1;

    cout << "=================================================================================\n";
    cout << "| №   |   Прізвище   |      Ім'я      |     Номер телефону    | Дата народження |\n";
    cout << "---------------------------------------------------------------------------------\n";

    while (getline(file, friend_info.last_name) &&
        getline(file, friend_info.first_name) &&
        getline(file, friend_info.phone_number)) {
        file >> friend_info.birthday[0] >> friend_info.birthday[1] >> friend_info.birthday[2];
        file.ignore();

        cout << "| " << setw(3) << index++ << " | "
            << setw(12) << friend_info.last_name << " | "
            << setw(14) << friend_info.first_name << " | "
            << setw(21) << friend_info.phone_number << " | "
            << setw(2) << friend_info.birthday[0] << "."
            << setw(2) << friend_info.birthday[1] << "."
            << setw(4) << friend_info.birthday[2] << "      |\n";
    }

    cout << "=================================================================================\n";
    file.close();
}

void AddToFile(const string& file_name) {
    ofstream file(file_name, ios::app);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    cin.ignore();
    string keep;

    do {
        FriendInfo friend_info;
        cout << "Прізвище: ";
        getline(cin, friend_info.last_name);
        cout << "Ім'я: ";
        getline(cin, friend_info.first_name);
        cout << "Номер телефону: ";
        getline(cin, friend_info.phone_number);

        cout << "День народження (дд мм рррр): ";
        cin >> friend_info.birthday[0] >> friend_info.birthday[1] >> friend_info.birthday[2];

        if (!IsValidDate(friend_info.birthday[0], friend_info.birthday[1], friend_info.birthday[2])) {
            cout << "Некоректна дата! Введіть дані знову.\n";
            cin.ignore();
            continue;
        }

        file << friend_info.last_name << endl
            << friend_info.first_name << endl
            << friend_info.phone_number << endl
            << friend_info.birthday[0] << " " << friend_info.birthday[1] << " " << friend_info.birthday[2] << endl;

        cin.ignore();
        cout << "Продовжити введення? (Y/N): ";
        getline(cin, keep);
    } while (keep == "Y" || keep == "y");

    file.close();
}

void Search(const string& file_name) {
    ifstream file(file_name, ios::in);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    string phone_to_find;
    cout << "Введіть номер телефону для пошуку: ";
    cin.ignore();
    getline(cin, phone_to_find);

    FriendInfo friend_info;
    bool found = false;

    while (getline(file, friend_info.last_name) &&
        getline(file, friend_info.first_name) &&
        getline(file, friend_info.phone_number)) {
        file >> friend_info.birthday[0] >> friend_info.birthday[1] >> friend_info.birthday[2];
        file.ignore();

        if (friend_info.phone_number == phone_to_find) {
            cout << "Знайдено:\n";
            cout << "Прізвище: " << friend_info.last_name << "\n";
            cout << "Ім'я: " << friend_info.first_name << "\n";
            cout << "Номер телефону: " << friend_info.phone_number << "\n";
            cout << "Дата народження: " << friend_info.birthday[0] << "."
                << friend_info.birthday[1] << "." << friend_info.birthday[2] << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Друга з таким номером телефону не знайдено.\n";
    }

    file.close();
}

bool IsValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) days_in_month[1] = 29;

    return day <= days_in_month[month - 1];
}
