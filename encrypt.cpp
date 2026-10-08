#include "encrypt.h"

#include <fstream>

void encrypt(User* users, int userCount) {
    // Прості шифрувальні алгоритми для даних користувачів
    for (int i = 0; i < userCount; i++) {
        for (char &c : users[i].login) {
            c ^= 0xFF; // XOR для шифрування
        }
        for (char &c : users[i].passHash) {
            c ^= 0xFF; // XOR для шифрування
        }
    }

    ofstream file("users_encrypted.txt");
    for (int i = 0; i < userCount; i++) {
        file << users[i].login << " " << users[i].passHash << "\n";
    }
    file.close();
}

void decrypt(User* users, int userCount) {
    ifstream file("users_encrypted.txt");
    string login, passHash;

    int i = 0;
    while (file >> login >> passHash) {
        for (char &c : login) {
            c ^= 0xFF; // XOR для дешифрування
        }
        for (char &c : users[i].passHash) {
            c ^= 0xFF; // XOR для шифрування
        }

        users[i].login = login;
        users[i].passHash = passHash;
        i++;
    }
    file.close();
}