#include "../include/Menu.h"
#include "../include/User.h"
#include "../include/Admin.h"
#include "../include/Logger.h"

int main() {
    User* user = new Admin(1, "admin", "admin");

    std::string inventoryFilePath = "inventory.txt";
    Logger logger("logs.txt");
    Menu menu(inventoryFilePath, user);

    menu.displayMenu();

    delete user;
    return 0;
}
