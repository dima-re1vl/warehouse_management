#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
private:
    std::string logFilePath;

    std::string getCurrentTime();

    int getNextLogNumber();

public:
    Logger(const std::string& logFilePath);

    void addLog(const std::string& username, const std::string& action);
    void displayLogs();
};

#endif
