#include "../include/Warehouse.h"

#include <fstream>
#include <algorithm>
#include <iostream>

Warehouse::Warehouse(const std::string& filePath) : filePath(filePath) {
    loadInventory();
}

void Warehouse::addItem(const InventoryItem& item) {
    inventory.push_back(item);
    saveInventory();
}

const std::vector<InventoryItem>& Warehouse::getInventory() const {
    return inventory;
}

void Warehouse::updateItemQuantity(int id, int newQuantity) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            item.setQuantity(newQuantity);
            saveInventory();
            return;
        }
    }
}

void Warehouse::removeItem(int id) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(), [id](const InventoryItem& item) {
        return item.getId() == id;
    }), inventory.end());
    saveInventory();
}

bool Warehouse::itemExists(int id) const {
    return std::any_of(inventory.begin(), inventory.end(), [id](const InventoryItem& item) {
        return item.getId() == id;
    });
}

std::string Warehouse::getFilePath() const {
    return filePath;
}

void Warehouse::saveInventory() {
    std::ofstream outFile(filePath);
    for (const auto& item : inventory) {
        outFile << item.getId() << " " << item.getName() << " "
                << item.getQuantity() << " " << item.getCategory() << " "
                << item.getLocation() << std::endl;
    }
}

void Warehouse::loadInventory() {
    std::ifstream inFile(filePath);
    if (inFile) {
        inventory.clear();
        int id, quantity;
        std::string name, category, location;
        while (inFile >> id >> name >> quantity >> category >> location) {
            inventory.push_back(InventoryItem(id, name, quantity, category, location));
        }
    }
}

void Warehouse::displayAllItems() const {
    for (const auto& item : inventory) {
        std::cout << "Item ID: " << item.getId() << ", Name: " << item.getName()
                  << ", Quantity: " << item.getQuantity() << std::endl;
    }
}

void Warehouse::updateItemName(int id, const std::string& newName) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            item.setName(newName);
            std::cout << "Назва товару оновлена." << std::endl;
            return;
        }
    }
    std::cout << "Товар не знайдено." << std::endl;
}

void Warehouse::updateItemCategory(int id, const std::string& newCategory) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            item.setCategory(newCategory);
            std::cout << "Категорія товару оновлена." << std::endl;
            return;
        }
    }
    std::cout << "Товар не знайдено." << std::endl;
}

void Warehouse::updateItemLocation(int id, const std::string& newLocation) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            item.setLocation(newLocation);
            std::cout << "Локація товару оновлена." << std::endl;
            return;
        }
    }
    std::cout << "Товар не знайдено." << std::endl;
}

void Warehouse::supplyItem(int id, int quantity) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            item.setQuantity(item.getQuantity() + quantity);
            std::cout << "Товар " << item.getName() << " постачено: " << quantity << " одиниць." << std::endl;
            saveInventory();
            return;
        }
    }
    std::cout << "Товар з ID " << id << " не знайдено." << std::endl;
}

void Warehouse::writeOffItem(int id, int quantity) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            if (item.getQuantity() >= quantity) {
                item.setQuantity(item.getQuantity() - quantity);
                std::cout << "Товар " << item.getName() << " списано: " << quantity << " одиниць." << std::endl;
                saveInventory();
            } else {
                std::cout << "Недостатня кількість товару для списання." << std::endl;
            }
            return;
        }
    }
    std::cout << "Товар з ID " << id << " не знайдено." << std::endl;
}

std::vector<InventoryItem> Warehouse::getItemsByCategory(const std::string& category) const {
    std::vector<InventoryItem> itemsInCategory;
    for (const auto& item : inventory) {
        if (item.getCategory() == category) {
            itemsInCategory.push_back(item);
        }
    }
    return itemsInCategory;
}

int Warehouse::getNextItemId() const {
    if (inventory.empty()) {
        return 1;
    }
    return inventory.back().getId() + 1;
}

InventoryItem* Warehouse::getItemById(int id) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}

void Warehouse::updateItem(int id, const InventoryItem& updatedItem) {
    for (auto& item : inventory) {
        if (item.getId() == id) {
            item = updatedItem;
            break;
        }
    }
}