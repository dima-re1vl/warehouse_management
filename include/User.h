#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

class User {
protected:
    int id;
    std::string username;
    std::string password;
    std::string role;
public:
    User(int id, const std::string& username, const std::string& password, const std::string& role);
    virtual ~User() = default;

    virtual void displayInfo() const;
    virtual std::string getRole() const;
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;

    virtual bool canEditInventory() const { return false; }
    virtual bool canManageUsers() const { return false; }

    bool checkCredentials(const std::string& username, const std::string& password) const;
};

#endif
