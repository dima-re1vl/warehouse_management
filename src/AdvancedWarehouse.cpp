#include "../include/AdvancedWarehouse.h"
#include <iostream>

void AdvancedWarehouse::displayInventory() {
    for (const auto& item : inventory) {
        std::cout << "ID: " << item.getId() << ", Назва: " << item.getName()
                  << ", Кількість: " << item.getQuantity() << "\n";
    }
}