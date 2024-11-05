#include "../include/User.h"

User::User(int id, const std::string& username, const std::string& password, const std::string& role)
    : id(id), username(username), password(password), role(role) {}

void User::displayInfo() const {
    std::cout << "ID: " << id << ", Ім'я: " << username << ", Роль: " << role << std::endl;
}

std::string User::getRole() const {
    return role;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getUsername() const {
    return username;
}

bool User::checkCredentials(const std::string& username, const std::string& password) const {
    return this->username == username && this->password == password;
}

int User::getId() const {
    return id;
}