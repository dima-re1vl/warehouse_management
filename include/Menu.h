#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include "../include/Warehouse.h"
#include "../include/Logger.h"
#include "../include/User.h"
#include "../include/UsersManager.h"

class Menu {
public:
    Menu(const std::string& inventoryFilePath, User* user);
    void displayMenu();
    void displayInfo();

private:
    Warehouse warehouse;
    User* currentUser;
    Logger logger;
    UsersManager usersManager;
    std::vector<std::shared_ptr<User>> users;
    int lastUserId = 0;

    void manageUsers();
    void manageInventory();
};

#endif
