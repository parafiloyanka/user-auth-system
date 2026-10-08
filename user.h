#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

struct User {
    string id;
    string login;
    string passHash;
    string accessLvl;
    bool isLocked; // Додаємо ознаку блокування
};

void addUser(User*& users, int &userCount);
string genID(int userCount);
bool loginUnique(const User* users, int userCount, const string& login); // Функція для перевірки унікальності
bool authentic(User* users, int userCount, const string& login, const string& password); // Для входу
void cPass(User* users, int userCount); // Функція для зміни пароля
void guest(User*& users, int userCount);

#endif //USER_H
