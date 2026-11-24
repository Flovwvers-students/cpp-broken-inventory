#include <iostream>
#include "inventory.hpp"

int main() {
    Weapon sword("Sword", 1, 10);
    Armor shield("Shield", 1, 5);
    Potion potion("Health", 2, 20);
    Inventory inventory;
    
    inventory.add(&sword);
    inventory.add(&shield);
    inventory.add(&potion);
    
    for (const auto& message : inventory.useAll()) {
        std::cout << message << '\n';
    }
    std::cout << "Objects: " << inventory.size() << '\n';
    
    Item* base = &sword;
    std::cout << "Polymorphism check: " << base->use() << '\n';
    
    return 0;
}
