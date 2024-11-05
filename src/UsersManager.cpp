#include "../include/UsersManager.h"
#include "../include/Admin.h"
#include "../include/Employee.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

void UsersManager::saveUserToFile(int id, const std::string& username, const std::string& password, const std::string& role) {
    std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        std::string lowerRole = role;
        std::transform(lowerRole.begin(), lowerRole.end(), lowerRole.begin(), ::tolower);
        file << id << " " << username << " " << password << " " << lowerRole << std::endl;
        file.close();
    } else {
        std::cerr << "Не вдалося відкрити файл для збереження користувача." << std::endl;
    }
}

int UsersManager::loadLastUserId() {
    std::ifstream file("users.txt");
    std::string line;
    int maxId = -1;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        iss >> id;
        maxId = std::max(maxId, id);
    }
    return maxId + 1;
}

void UsersManager::loadUsersFromFile(std::vector<std::shared_ptr<User>>& users, int& lastUserId) {
    std::ifstream file("users.txt");
    if (file.is_open()) {
        for (const auto& user : users) {
            if (user->getId() > lastUserId) {
                lastUserId = user->getId();
            }
        }
        int id;
        std::string username, password, role;
        while (file >> id >> username >> password >> role) {
            if (role == "admin") {
                users.push_back(std::make_shared<Admin>(id, username, password));
            } else if (role == "employee") {
                users.push_back(std::make_shared<Employee>(id, username, password));
            }
        }
        file.close();
    } else {
        std::cerr << "Не вдалося відкрити файл для завантаження користувачів." << std::endl;
    }
}

void UsersManager::saveUsersToFile(const std::vector<std::shared_ptr<User>>& users) {
    std::ofstream file("users.txt");
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user->getId() << " " << user->getUsername() << " " << user->getPassword() << " " << user->getRole() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Не вдалося відкрити файл для збереження користувачів." << std::endl;
    }
}
