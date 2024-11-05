#include "../include/Menu.h"
#include "../include/InventoryManager.h"
#include "../include/UsersManager.h"
#include "../include/Admin.h"
#include "../include/Employee.h"
#include "../include/Warehouse.h"
#include "../include/User.h"
#include "../include/Logger.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

Menu::Menu(const std::string& inventoryFilePath, User* user)
    : warehouse(inventoryFilePath), currentUser(user), logger("logs.txt") {
    usersManager.loadUsersFromFile(users, lastUserId);
}

void Menu::displayInfo() {
    std::cout << "\n";
    std::cout << std::setw(45) << std::setfill('-') << "" << "\n";
    std::cout << "|     Prod by D.Shkolenko 4-KH-21 v.0.0.1     |\n";
    std::cout << std::setw(45) << std::setfill('-') << "" << "\n";
    std::cout << "\n";
}

void Menu::displayMenu() {
    displayInfo();
    std::string username, password;

    std::cout << "Введіть логін: ";
    std::cin >> username;
    std::cout << "Введіть пароль: ";
    std::cin >> password;

    bool loggedIn = false;
    for (const auto& user : users) {
        if (user->checkCredentials(username, password)) {
            currentUser = user.get();
            loggedIn = true;
            break;
        }
    }

    if (!loggedIn) {
        std::cout << "Неправильний логін або пароль!" << std::endl;
        return;
    }

    int choice = 0;

    while (choice != 4) {
        std::cout << "\n=== Головне Меню ===" << std::endl;
        std::cout << "1. Управління користувачами (Доступно тільки для Admin)" << std::endl;
        std::cout << "2. Управління інвентарем" << std::endl;
        std::cout << "3. Переглянути всі логи" << std::endl;
        std::cout << "4. Вихід" << std::endl;
        std::cout << "\n--> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                if (currentUser->canManageUsers()) {
                    manageUsers();
                } else {
                    std::cout << "У вас немає прав для управління користувачами." << std::endl;
                }
            break;
            case 2:
                if (currentUser->canEditInventory()) {
                    manageInventory();
                } else {
                    std::cout << "У вас немає прав для управління інвентарем." << std::endl;
                }
            break;
            case 3:
                std::cout << "Перегляд всіх логів:" << std::endl;
                logger.displayLogs();
            break;
            case 4:
                std::cout << "Вихід..." << std::endl;
            break;
            default:
                std::cout << "Невірний вибір, спробуйте знову." << std::endl;
            break;
        }
    }
}

void Menu::manageUsers() {
    UsersManager usersManager;
    lastUserId = usersManager.loadLastUserId();

    int choice;
    do {
        std::cout << "\n=== Робота з користувачами ===" << std::endl;
        std::cout << "1. Додати користувача\n";
        std::cout << "2. Переглянути всіх користувачів\n";
        std::cout << "3. Видалити користувача\n";
        std::cout << "0. Повернутись до головного меню\n";
        std::cout << "\n--> ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string username, password, role;
                std::cout << "Ім'я користувача: ";
                std::cin >> username;
                std::cout << "Пароль: ";
                std::cin >> password;
                std::cout << "Роль (admin/employee): ";
                std::cin >> role;

                if (role == "admin") {
                    users.push_back(std::make_shared<Admin>(lastUserId, username, password));
                } else if (role == "employee") {
                    users.push_back(std::make_shared<Employee>(lastUserId, username, password));
                } else {
                    std::cout << "Невідома роль!" << std::endl;
                    break;
                }
                usersManager.saveUserToFile(lastUserId, username, password, role);
                logger.addLog(currentUser->getUsername(), "Додано користувача: " + username + ", Роль: " + role);
                lastUserId++;
                break;
            }
            case 2:
                for (const auto& user : users) {
                    user->displayInfo();
                }
                logger.addLog(currentUser->getUsername(), "Переглянуто всіх користувачів");
                break;
            case 3: {
                int idToDelete;
                std::cout << "Введіть ID користувача для видалення: ";
                std::cin >> idToDelete;
                auto it = std::remove_if(users.begin(), users.end(), [idToDelete](const std::shared_ptr<User>& user) {
                    return user->getId() == idToDelete;
                });
                if (it != users.end()) {
                    users.erase(it, users.end());
                    std::cout << "Користувача з ID " << idToDelete << " видалено." << std::endl;
                    usersManager.saveUsersToFile(users);
                    logger.addLog(currentUser->getUsername(), "Видалено користувача з ID " + std::to_string(idToDelete));
                } else {
                    std::cout << "Користувача з ID " << idToDelete << " не знайдено." << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Повернення до головного меню." << std::endl;
                break;
            default:
                std::cout << "Невірний вибір. Спробуйте ще раз." << std::endl;
                break;
        }
    } while (choice != 0);
}

void Menu::manageInventory() {
    int choice;
    InventoryManager inventoryManager(warehouse, logger, currentUser);

    while (choice != 0) {
        std::cout << "\n=== Робота зі складом ===" << std::endl;
        std::cout << "1. Додати товар\n";
        std::cout << "2. Редагувати товар\n";
        std::cout << "3. Видалити товар\n";
        std::cout << "4. Показати всі товари\n";
        std::cout << "5. Переглянути по категорії\n";
        std::cout << "6. Постачання товару\n";
        std::cout << "7. Списання товару\n";
        std::cout << "0. Повернутись до головного меню\n";
        std::cout << "\n--> ";
        std::cin >> choice;

        switch (choice) {
            case 1: inventoryManager.addItem(); break;
            case 2: inventoryManager.editItem(); break;
            case 3: inventoryManager.deleteItem(); break;
            case 4: inventoryManager.showAllItems(); break;
            case 5: inventoryManager.viewItemsByCategory(); break;
            case 6: inventoryManager.supplyItem(); break;
            case 7: inventoryManager.writeOffItem(); break;
            case 0: std::cout << "Повернення до головного меню." << std::endl; break;
            default: std::cout << "Невірний вибір. Спробуйте ще раз." << std::endl;
        }
    }
}