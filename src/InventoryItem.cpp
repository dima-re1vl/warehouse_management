#include "../include/InventoryItem.h"

InventoryItem::InventoryItem(int id, const std::string& name, int quantity, const std::string& category, const std::string& location)
    : id(id), name(name), quantity(quantity), category(category), location(location) {}

int InventoryItem::getId() const {
    return id;
}

const std::string &InventoryItem::getName() const {
    return name;
}

int InventoryItem::getQuantity() const {
    return quantity;
}

const std::string &InventoryItem::getCategory() const {
    return category;
}

const std::string &InventoryItem::getLocation() const {
    return location;
}

void InventoryItem::setName(const std::string& newName) {
    name = newName;
}

void InventoryItem::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

void InventoryItem::setCategory(const std::string& newCategory) {
    category = newCategory;
}

void InventoryItem::setLocation(const std::string& newLocation) {
    location = newLocation;
}

