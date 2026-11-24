#include <iostream>
#include "inventory.hpp"

int failures = 0;

void check(bool condition, const char* label) {
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

int main() {
    Weapon sword("Sword", 1, 10);
    Armor shield("Shield", 1, 5);
    Potion potion("Health", 2, 20);

    Inventory inv;
    check(inv.size() == 0, "empty size");
    check(inv.find("Sword") == nullptr, "find in empty returns nullptr");

    check(inv.add(&sword), "add weapon");
    check(inv.size() == 1, "one object");
    check(!inv.add(nullptr), "add nullptr rejected");
    check(!inv.add(&sword), "add duplicate address rejected");

    Item* base = &sword;
    check(base->use() == "Attack: Sword", "virtual dispatch weapon");

    Weapon badWeapon("Bad", 1, -50);
    check(badWeapon.damage() == 0, "negative damage becomes zero");
    
    Item badItem("Item", -5);
    check(badItem.quantity() == 0, "negative quantity becomes zero");

    check(potion.use() == "Drink: Health", "potion drink");
    check(potion.quantity() == 1, "potion quantity decreased");
    check(potion.use() == "Drink: Health", "potion drink second time");
    check(potion.quantity() == 0, "potion quantity is zero");
    check(potion.use() == "Empty: Health", "potion empty");
    check(potion.quantity() == 0, "potion stays zero");

    check(inv.find("Sword") == &sword, "find sword");
    check(inv.find("sword") == nullptr, "find is case sensitive");

    check(inv.at(0) == &sword, "at valid index");
    check(inv.at(99) == nullptr, "at invalid index");

    inv.add(&shield);
    inv.add(&potion);
    check(inv.size() == 3, "added 3 items");
    check(!inv.remove(99), "remove invalid index");
    check(inv.remove(1), "remove middle item");
    check(inv.size() == 2, "size decreased");
    check(inv.at(1) == &potion, "item shifted correctly");

    inv.clear();
    check(inv.size() == 0, "clear inventory");
    inv.clear();
    check(inv.size() == 0, "clear twice is safe");

    std::cout << "Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
