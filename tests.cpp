#include "inventory.hpp"
#include <iostream>

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
    check(inv.add(&sword), "add weapon");
    check(inv.size() == 1, "one object");

    Item* base = &sword;
    check(base->use() == "Attack: Sword", "virtual dispatch weapon");

    check(!inv.add(nullptr), "add nullptr");
    check(!inv.add(&sword), "add duplicate address");
    check(inv.size() == 1, "size after duplicate rejected");

    Weapon sword2("Sword", 1, 5);
    check(inv.add(&sword2), "add different object with same name");
    check(inv.size() == 2, "size after same name");

    check(inv.find("Sword") == &sword, "find returns first matching");
    check(inv.find("Nonexistent") == nullptr, "find missing returns nullptr");

    check(inv.at(0) == &sword, "at index 0");
    check(inv.at(1) == &sword2, "at index 1");
    check(inv.at(99) == nullptr, "at out of range returns nullptr");

    check(inv.remove(0), "remove first");
    check(inv.size() == 1, "size after remove first");
    check(inv.at(0) == &sword2, "order preserved after remove first");

    check(!inv.remove(99), "remove invalid index");

    inv.clear();
    check(inv.size() == 0, "clear empties inventory");
    inv.clear();
    check(inv.size() == 0, "clear twice safe");

    Inventory emptyInv;
    check(emptyInv.at(0) == nullptr, "at on empty returns nullptr");
    check(emptyInv.remove(0) == false, "remove on empty returns false");
    check(emptyInv.find("Anything") == nullptr, "find on empty returns nullptr");
    check(emptyInv.useAll().empty(), "useAll on empty returns empty vector");

    Weapon negativeDamage("NegWeapon", 1, -10);
    Armor negativeDefense("NegArmor", 1, -5);
    Potion negativeHealing("NegPotion", 1, -20);
    check(negativeDamage.damage() == 0, "negative damage becomes 0");
    check(negativeDefense.defense() == 0, "negative defense becomes 0");
    check(negativeHealing.healing() == 0, "negative healing becomes 0");

    Item zeroItem("ZeroItem", -5);
    check(zeroItem.quantity() == 0, "negative quantity becomes 0");
    zeroItem.setQuantity(-3);
    check(zeroItem.quantity() == 0, "negative setQuantity becomes 0");

    Potion emptyPotion("EmptyPotion", 0, 10);
    check(emptyPotion.use() == "Empty: EmptyPotion", "potion empty use");
    check(emptyPotion.quantity() == 0, "potion empty quantity stays 0");

    Potion onePotion("OnePotion", 1, 10);
    check(onePotion.use() == "Drink: OnePotion", "potion drink use");
    check(onePotion.quantity() == 0, "potion quantity decremented");

    Inventory midInv;
    Weapon w1("W1", 1, 1);
    Weapon w2("W2", 1, 2);
    Weapon w3("W3", 1, 3);
    midInv.add(&w1);
    midInv.add(&w2);
    midInv.add(&w3);
    check(midInv.remove(1), "remove middle");
    check(midInv.size() == 2, "size after remove middle");
    check(midInv.at(0) == &w1, "first stays");
    check(midInv.at(1) == &w3, "last shifts left");

    Inventory lastInv;
    lastInv.add(&w1);
    lastInv.add(&w2);
    check(lastInv.remove(1), "remove last");
    check(lastInv.size() == 1, "size after remove last");
    check(lastInv.at(0) == &w1, "first stays after remove last");

    check(sword.use() == "Attack: Sword", "item use does not change quantity");
    check(sword.quantity() == 1, "weapon quantity unchanged");

    std::cout << "Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
