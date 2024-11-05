#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <string>

class InventoryItem {
public:
    InventoryItem(int id, const std::string& name, int quantity, const std::string& category, const std::string& location);
    int getId() const;
    int getQuantity() const;
    const std::string& getName() const;
    const std::string& getCategory() const;
    const std::string& getLocation() const;
    void setName(const std::string& newName);
    void setQuantity(int newQuantity);
    void setCategory(const std::string& newCategory);
    void setLocation(const std::string& newLocation);

private:
    int id;
    std::string name;
    int quantity;
    std::string category;
    std::string location;
};

#endif
