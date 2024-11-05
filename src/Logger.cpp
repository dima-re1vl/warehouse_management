#include "../include/Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>

Logger::Logger(const std::string& logFilePath) : logFilePath(logFilePath) {}

std::string Logger::getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char timeStr[20];
    sprintf(timeStr, "%04d-%02d-%02d %02d:%02d:%02d",
            ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday,
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    return std::string(timeStr);
}

int Logger::getNextLogNumber() {
    std::ifstream file(logFilePath);
    std::string lastLine;
    while (file.peek() != EOF) {
        std::getline(file, lastLine);
    }
    file.close();

    if (lastLine.empty()) {
        return 1;
    }

    size_t commaPos = lastLine.find(',');
    if (commaPos != std::string::npos) {
        std::string logNumberStr = lastLine.substr(0, commaPos);
        return std::stoi(logNumberStr) + 1;
    }

    return 1;
}

void Logger::addLog(const std::string& username, const std::string& action) {
    std::ofstream file(logFilePath, std::ios::app);
    if (file.is_open()) {
        int logNumber = getNextLogNumber();
        std::string currentTime = getCurrentTime();
        file << logNumber << "," << username << "," << action << "," << currentTime << std::endl;
        file.close();
    } else {
        std::cerr << "Не вдалося відкрити файл для запису логу!" << std::endl;
    }
}

void Logger::displayLogs() {
    std::ifstream file(logFilePath);
    if (file.is_open()) {
        std::string line;
        std::cout << "Номер логу, Користувач, Дія, Час" << std::endl;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Не вдалося відкрити файл для зчитування логів!" << std::endl;
    }
}
