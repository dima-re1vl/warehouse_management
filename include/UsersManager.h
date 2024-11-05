#ifndef USERS_MANAGER_H
#define USERS_MANAGER_H

#include "User.h"

class UsersManager {
public:
    void saveUserToFile(int id, const std::string& username, const std::string& password, const std::string& role);
    void loadUsersFromFile(std::vector<std::shared_ptr<User>>& users, int& lastUserId);
    void saveUsersToFile(const std::vector<std::shared_ptr<User>>& users);
    int loadLastUserId();
};

#endif
