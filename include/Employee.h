#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

class Employee : public User {
public:
    Employee(int id, const std::string& username, const std::string& password)
        : User(id, username, password, "employee") {}

    std::string getRole() const override;
};

#endif // EMPLOYEE_H
