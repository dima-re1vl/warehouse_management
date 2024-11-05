#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(int id, const std::string& username, const std::string& password);

    std::string getRole() const override;

    bool canEditInventory() const override { return true; }
    bool canManageUsers() const override { return true; }
};

#endif
