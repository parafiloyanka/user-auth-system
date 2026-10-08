#include "user.h"
#include "log.h"
#include <sstream>

using namespace std;

string pHash(const string& password) {
    string hash = "";
    unsigned int result = 0;

    for (char c : password) {
        result ^= (c * 7);  // XOR операція для комбінування байтів
    }
    stringstream ss;
    ss << hex << setw(2) << setfill('0') << result;
    hash += ss.str();
    return hash;
}

string genID(int userCount) {
    string id = "ID";
    int num = userCount + 1;

    // Формуємо число у форматі XXXX (додаємо нулі, якщо треба)
    if (num < 10) id += "000" + to_string(num);
    else if (num < 100) id += "00" + to_string(num);
    else if (num < 1000) id += "0" + to_string(num);
    else id += to_string(num);

    return id;
}

bool loginUnique(const User* users, int userCount, const string& login) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].login == login) {
            return false; // Логін вже існує
        }
    }
    return true; // Логін унікальний
}

bool authentic(User* users, int userCount, const string& login, const string& password) {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].login == login) {
            if (users[i].isLocked) {
                cout << "\033[1;31m" << "Ваш акаунт заблоковано.\n" << "\033[0m";
                return false;
            }

            if (users[i].passHash == pHash(password)) {
                return true;
            } else {
                users[i].isLocked = true;
                writeLog("Користувач " + login + " заблокований після невдалих спроб входу.");
                return false;
            }
        }
    }
    return false;
}

void addUser(User*& users, int &userCount) {
    User newUser;
    cout << "Введіть логін користувача: " << "\033[1;35m";
    cin >> newUser.login;
    cout << "\033[0m";

    if (!loginUnique(users, userCount, newUser.login)) {
        cout << "\033[1;31m" << "Такий логін вже існує.\n" << "\033[0m";
        return;
    }
    if (newUser.login == "guest") {
        newUser.accessLvl = "guest";
        newUser.passHash = "";
    } else {
        if (newUser.login.back() == '_') {
            newUser.login.pop_back();
            newUser.accessLvl = "admin";
        } else {
            newUser.accessLvl = "user";
        }

        cout << "Введіть пароль: " << "\033[1;35m";
        string password;
        cin >> password;
        cout << "\033[0m";
        newUser.passHash = pHash(password);
    }

    newUser.id = genID(userCount);
    newUser.isLocked = false;

    User* newUsers = new User[userCount + 1];
    for (int i = 0; i < userCount; i++) {
        newUsers[i] = users[i];
    }
    newUsers[userCount] = newUser;
    delete[] users;
    users = newUsers;
    userCount++;

    writeLog("Додано нового користувача: " + newUser.login);
    cout << "\033[1;32m" << "Користувач доданий успішно!\n" << "\033[0m";
}

void cPass(User* users, int userCount) {
    string login, oldPassword, newPassword;

    cout << "Введіть логін: " << "\033[1;35m";
    cin >> login;
    cout << "\033[0m";
    cout << "Введіть старий пароль: " << "\033[1;35m";
    cin >> oldPassword;
    cout << "\033[0m";

    for (int i = 0; i < userCount; ++i) {
        if (users[i].login == login && users[i].passHash == pHash(oldPassword)) {
            cout << "Введіть новий пароль: " << "\033[1;35m";
            cin >> newPassword;
            cout << "\033[0m";
            users[i].passHash = pHash(newPassword);
            writeLog("Змінено пароль для користувача: " + login);
            cout << "\033[1;32m" << "Пароль успішно змінено.\n" << "\033[0m";
            return;
        }
    }

    cout << "\033[1;31m" << "Невірний логін або пароль.\n" << "\033[0m";
}

void guest(User*& users, int userCount) {
    string login = "guest";
    int guestNumber = 1;

    while (!loginUnique(users, userCount, login)) {
        login = "guest" + to_string(guestNumber++);
    }
    cout << "Ви увійшли як " << "\033[1;36m" << login << "\033[0m"<< ".\n";
}