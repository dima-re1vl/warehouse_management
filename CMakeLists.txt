cmake_minimum_required(VERSION 3.29)
project(kursova)

set(CMAKE_CXX_STANDARD 20)

add_executable(kursova src/main.cpp
        src/InventoryItem.cpp
        include/InventoryItem.h
        src/Warehouse.cpp
        src/User.cpp
        src/Admin.cpp
        src/Employee.cpp
        src/Menu.cpp
        include/Warehouse.h
        include/User.h
        include/Admin.h
        include/Employee.h
        include/Menu.h
        include/Logger.h
        src/Logger.cpp
        include/AdvancedWarehouse.h
        src/AdvancedWarehouse.cpp
        include/InventoryManager.h
        src/InventoryManager.cpp
        include/UsersManager.h
        src/UsersManager.cpp
)
