#include "../include/InventoryManager.h"
#include <iostream>

InventoryManager::InventoryManager(Warehouse& warehouse, Logger& logger, User* currentUser)
    : warehouse(warehouse), logger(logger), currentUser(currentUser) {}

void InventoryManager::deleteItem() {
    int id;
    std::cout << "Введіть ID товару для видалення: ";
    std::cin >> id;

    if (warehouse.itemExists(id)) {
        warehouse.removeItem(id);
        std::cout << "Товар видалено." << std::endl;
        logger.addLog(currentUser->getUsername(), "Видалено товар з ID: " + std::to_string(id));
    } else {
        std::cout << "Товар з таким ID не знайдено." << std::endl;
    }
}

void InventoryManager::addItem() {

    std::string name, category, location;
    int quantity = 0;

    std::cout << "Введіть назву товару: ";
    std::cin >> name;
    std::cout << "Введіть категорію товару: ";
    std::cin >> category;
    std::cout << "Введіть локацію товару: ";
    std::cin >> location;
    while (true) {
        std::cout << "Введіть кількість товару: ";
        std::cin >> quantity;

        if (std::cin.fail() || quantity < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Будь ласка, введіть дійсне не від’ємне число для кількості." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    InventoryItem newItem(warehouse.getNextItemId(), name, quantity, category, location);
    warehouse.addItem(newItem);

    logger.addLog(currentUser->getUsername(), "Додано товар: " + name);
    std::cout << "Товар додано успішно." << std::endl;
}

void InventoryManager::showAllItems() {
    std::cout << "Список усіх товарів на складі:" << std::endl;
    warehouse.displayAllItems();
}

void InventoryManager::editItem() {
    int id;
    std::cout << "Введіть ID товару для редагування: ";
    std::cin >> id;

    InventoryItem* item = warehouse.getItemById(id);

    if (item) {
        std::string newName, newCategory, newLocation;
        int newQuantity;

        std::cout << "Поточна назва: " << item->getName() << "\n";
        std::cout << "Введіть нову назву (або залиште порожнім для збереження поточного значення): ";
        std::getline(std::cin >> std::ws, newName);
        if (!newName.empty()) item->setName(newName);

        std::cout << "Поточна категорія: " << item->getCategory() << "\n";
        std::cout << "Введіть нову категорію (або залиште порожнім для збереження поточного значення): ";
        std::getline(std::cin >> std::ws, newCategory);
        if (!newCategory.empty()) item->setCategory(newCategory);

        std::cout << "Поточна локація: " << item->getLocation() << "\n";
        std::cout << "Введіть нову локацію (або залиште порожнім для збереження поточного значення): ";
        std::getline(std::cin >> std::ws, newLocation);
        if (!newLocation.empty()) item->setLocation(newLocation);

        std::cout << "Поточна кількість: " << item->getQuantity() << "\n";
        std::cout << "Введіть нову кількість: ";
        std::cin >> newQuantity;
        item->setQuantity(newQuantity);

        logger.addLog(currentUser->getUsername(), "Редаговано товар ID: " + std::to_string(id));
    } else {
        std::cout << "Товар з таким ID не знайдено." << std::endl;
    }
}

void InventoryManager::supplyItem() {

    int id, quantity;
    std::cout << "Введіть ID товару для постачання: ";
    std::cin >> id;
    std::cout << "Введіть кількість для постачання: ";
    std::cin >> quantity;

    warehouse.supplyItem(id, quantity);
    logger.addLog(currentUser->getUsername(), "Постачено товар ID " + std::to_string(id) + " кількість: " + std::to_string(quantity));
}

void InventoryManager::writeOffItem() {

    int id, quantity;
    std::cout << "Введіть ID товару для списання: ";
    std::cin >> id;
    std::cout << "Введіть кількість для списання: ";
    std::cin >> quantity;

    warehouse.writeOffItem(id, quantity);
    logger.addLog(currentUser->getUsername(), "Списано товар, кількість: " + std::to_string(quantity));
}

void InventoryManager::viewItemsByCategory() {
    std::cout << "Доступні категорії:\n";
    std::unordered_map<std::string, bool> categories;

    for (const auto& item : warehouse.getInventory()) {
        categories[item.getCategory()] = true;
    }

    int index = 1;
    for (const auto& category : categories) {
        std::cout << index++ << ". " << category.first << "\n";
    }

    int categoryChoice;
    std::cout << "Оберіть номер категорії: ";
    std::cin >> categoryChoice;
    auto it = categories.begin();
    std::advance(it, categoryChoice - 1);
    std::string selectedCategory = it->first;

    auto itemsInCategory = warehouse.getItemsByCategory(selectedCategory);
    std::cout << "Товари в категорії \"" << selectedCategory << "\":\n";

    for (const auto& item : itemsInCategory) {
        std::cout << "Item ID: " << item.getId()
                  << ", Name: " << item.getName()
                  << ", Quantity: " << item.getQuantity() << std::endl;
    }

    if (itemsInCategory.empty()) {
        std::cout << "Немає товарів у цій категорії." << std::endl;
    }
}
