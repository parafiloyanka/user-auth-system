#include "user.h"
#include "encrypt.h"
#include "log.h"
#include "utils.h"

#include <iostream>
using namespace std;

int main() {
    User* users = nullptr;
    int userCount = 0;

    welcome();
    menu();

    while (true) {
        cout << "\nОберіть опцію: " << "\033[1;35m";
        int choice;
        cin >> choice;
        cout << "\033[0m";

        switch (choice) {
            case 1:
                addUser(users, userCount);
            break;
            case 2: {
                string login, password;
                cout << "Введіть логін: " << "\033[1;35m";
                cin >> login;
                cout << "\033[0m";

                if (login == "guest") {
                    guest(users, userCount);
                    break;
                    }

                cout << "Введіть пароль: " << "\033[1;35m";
                cin >> password;
                cout << "\033[0m";

                if (authentic(users, userCount, login, password)) {
                    cout << "Вітаємо, " << "\033[1;36m" << login << "\033[0m" << "!\n";
                } else {
                    cout << "\033[1;31m" << "Не вдалося увійти.\n" << "\033[0m";
                }
                break;
            }
            case 3:
                cPass(users, userCount);
            break;
            case 4:
                encrypt(users, userCount);
            cout << "\033[1;32m" << "Дані зашифровано.\n" << "\033[0m";
            break;
            case 5:
                decrypt(users, userCount);
            cout << "\033[1;32m" << "Дані розшифровано.\n" << "\033[0m";
            break;
            case 6:
                outp(users, userCount);
            break;
            default:
                delete[] users;
                return 0;
            }
    }
}
