cmake_minimum_required(VERSION 3.16)
project(BrokenInventory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INVENTORY_SOURCES
    src/item.cpp
    src/weapon.cpp
    src/armor.cpp
    src/potion.cpp
    src/inventory.cpp
)

add_executable(inventory_demo src/main.cpp ${INVENTORY_SOURCES})
target_include_directories(inventory_demo PRIVATE include)

add_executable(inventory_tests src/tests.cpp ${INVENTORY_SOURCES})
target_include_directories(inventory_tests PRIVATE include)

if(MSVC)
    target_compile_options(inventory_demo PRIVATE /W4 /utf-8)
    target_compile_options(inventory_tests PRIVATE /W4 /utf-8)
else()
    target_compile_options(inventory_demo PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(inventory_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME inventory_tests COMMAND inventory_tests)
