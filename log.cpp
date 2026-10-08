#include "log.h"

void writeLog(const string& logMessage) {
    ofstream logFile("logs.txt", ios_base::app); // Відкриваємо файл для додавання
    if (logFile.is_open()) {
        logFile << logMessage << endl; // Записуємо повідомлення
        logFile.close(); // Закриваємо файл
    } else {
        cerr << "\033[1;31m" << "Не вдалося відкрити файл журналу подій!" << "\033[0m" << endl;
    }
}