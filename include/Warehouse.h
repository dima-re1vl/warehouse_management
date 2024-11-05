#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <vector>
#include "InventoryItem.h"

class Warehouse {
public:
    Warehouse(const std::string& filePath);

    const std::vector<InventoryItem>& getInventory() const;
    std::vector<InventoryItem> getItemsByCategory(const std::string& category) const;
    std::vector<InventoryItem> items;
    std::vector<InventoryItem> inventory;

    InventoryItem* getItemById(int id);
    std::string getFilePath() const;
    int getNextItemId() const;

    bool itemExists(int id) const;

    void updateItemName(int id, const std::string& newName);
    void updateItemCategory(int id, const std::string& newCategory);
    void updateItemLocation(int id, const std::string& newLocation);
    void updateItem(int id, const InventoryItem& updatedItem);

    void displayAllItems() const;
    void addItem(const InventoryItem& item);
    void updateItemQuantity(int id, int newQuantity);
    void removeItem(int id);
    void supplyItem(int id, int quantity);
    void writeOffItem(int id, int quantity);

    void saveInventory();
    void loadInventory();

private:
    std::string filePath;
};

#endif
