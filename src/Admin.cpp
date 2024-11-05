#include "../include/Admin.h"

Admin::Admin(int id, const std::string& username, const std::string& password)
    : User(id, username, password, "admin") {}


std::string Admin::getRole() const {
    return "admin";
}
