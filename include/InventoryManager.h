#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "../include/Warehouse.h"
#include "../include/Logger.h"
#include "../include/User.h"

class InventoryManager {
public:
    InventoryManager(Warehouse& warehouse, Logger& logger, User* currentUser);
    void deleteItem();
    void addItem();
    void showAllItems();
    void editItem();
    void viewItemsByCategory();
    void writeOffItem();
    void supplyItem();

private:
    Warehouse& warehouse;
    Logger& logger;
    User* currentUser;
};

#endif
