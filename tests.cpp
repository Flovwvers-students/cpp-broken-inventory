#include "inventory.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int failures = 0;

void check(bool condition, const char* label) {
    if (!condition) {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}

void checkEq(const std::string& actual, const std::string& expected, const char* label) {
    if (actual != expected) {
        std::cerr << "FAIL: " << label << " (expected '" << expected
                  << "', got '" << actual << "')\n";
        ++failures;
    }
}

int main() {
    // ---------- 1. Item: имя и количество ----------
    {
        Item normal("Sword", 3);
        checkEq(normal.name(), "Sword", "item name kept");
        check(normal.quantity() == 3, "item quantity kept");

        Item negative("Bad", -5);
        check(negative.quantity() == 0, "negative quantity -> 0");

        Item emptyName("", 1);
        checkEq(emptyName.name(), "", "empty name allowed");

        normal.setQuantity(-2);
        check(normal.quantity() == 0, "setQuantity negative -> 0");
        normal.setQuantity(7);
        check(normal.quantity() == 7, "setQuantity positive kept");
    }

    // ---------- 2. Weapon/Armor/Potion: характеристики ----------
    {
        Weapon w("W", 1, 10);
        check(w.damage() == 10, "weapon damage kept");
        Weapon wNeg("W", 1, -3);
        check(wNeg.damage() == 0, "negative damage -> 0");

        Armor a("A", 1, 5);
        check(a.defense() == 5, "armor defense kept");
        Armor aNeg("A", 1, -4);
        check(aNeg.defense() == 0, "negative defense -> 0");

        Potion p("P", 2, 20);
        check(p.healing() == 20, "potion healing kept");
        Potion pNeg("P", 1, -6);
        check(pNeg.healing() == 0, "negative healing -> 0");
    }

    // ---------- 3. use через Item* и строки ----------
    {
        Item item("Thing", 1);
        Weapon sword("Sword", 1, 10);
        Armor shield("Shield", 1, 5);
        Potion potion("Health", 1, 20);

        Item* baseItem = &item;
        Item* baseSword = &sword;
        Item* baseShield = &shield;
        Item* basePotion = &potion;

        checkEq(baseItem->use(), "Item: Thing", "Item::use text");
        checkEq(baseSword->use(), "Attack: Sword", "Weapon::use text");
        checkEq(baseShield->use(), "Equip: Shield", "Armor::use text");
        checkEq(basePotion->use(), "Drink: Health", "Potion::use text with qty>0");

        // use не меняет количество у не-зелий
        check(item.quantity() == 1, "Item::use keeps quantity");
        check(sword.quantity() == 1, "Weapon::use keeps quantity");
        check(shield.quantity() == 1, "Armor::use keeps quantity");

        // use не меняет количество, даже если 0
        Weapon zeroW("ZW", 0, 1);
        Item* baseZW = &zeroW;
        checkEq(baseZW->use(), "Attack: ZW", "Weapon::use with qty 0");
        check(zeroW.quantity() == 0, "Weapon::use keeps 0 quantity");
    }

    // ---------- 4. Potion: уменьшение количества и Empty ----------
    {
        Potion potion("Health", 2, 20);
        Item* base = &potion;
        checkEq(base->use(), "Drink: Health", "potion use 1st");
        check(potion.quantity() == 1, "potion qty after 1 use");
        checkEq(base->use(), "Drink: Health", "potion use 2nd");
        check(potion.quantity() == 0, "potion qty after 2 uses");
        checkEq(base->use(), "Empty: Health", "potion empty message");
        check(potion.quantity() == 0, "potion stays 0");
    }

    // ---------- 5. add: nullptr, дубликат адреса ----------
    {
        Inventory inv;
        Item a("A", 1);
        Item b("B", 1);

        check(inv.add(nullptr) == false, "add nullptr -> false");
        check(inv.size() == 0, "nullptr did not change size");

        check(inv.add(&a) == true, "add first -> true");
        check(inv.size() == 1, "size after first add");

        check(inv.add(&a) == false, "add duplicate address -> false");
        check(inv.size() == 1, "duplicate did not change size");

        check(inv.add(&b) == true, "add second -> true");
        check(inv.size() == 2, "size after second add");
    }

    // ---------- 6. size = число указателей ----------
    {
        Inventory inv;
        Item a("A", 5);
        Item b("B", 10);
        inv.add(&a);
        inv.add(&b);
        check(inv.size() == 2, "size counts pointers, not quantities");
    }

    // ---------- 7. at: индексы ----------
    {
        Inventory inv;
        Item a("A", 1);
        Item b("B", 1);
        inv.add(&a);
        inv.add(&b);

        check(inv.at(0) == &a, "at(0)");
        check(inv.at(1) == &b, "at(1)");
        check(inv.at(2) == nullptr, "at(size) -> nullptr");
        check(inv.at(999) == nullptr, "at(big) -> nullptr");
    }

    // ---------- 8. find: точное совпадение, регистр, первый ----------
    {
        Inventory inv;
        Item a("Sword", 1);
        Item b("Sword", 1);
        Item c("sword", 1);
        inv.add(&a);
        inv.add(&b);
        inv.add(&c);

        check(inv.find("Sword") == &a, "find returns first match");
        check(inv.find("sword") == &c, "find case-sensitive");
        check(inv.find("SWORD") == nullptr, "find no match");
        check(inv.find("") == nullptr, "find empty name -> nullptr");
    }

    // ---------- 9. remove: первый/средний/последний, неверный индекс ----------
    {
        Inventory inv;
        Item a("A", 1);
        Item b("B", 1);
        Item c("C", 1);
        inv.add(&a);
        inv.add(&b);
        inv.add(&c);

        check(inv.remove(5) == false, "remove wrong index -> false");
        check(inv.size() == 3, "failed remove keeps size");

        check(inv.remove(1) == true, "remove middle -> true");
        check(inv.size() == 2, "size after middle remove");
        check(inv.at(0) == &a, "order kept after middle remove: first");
        check(inv.at(1) == &c, "order kept after middle remove: last");

        check(inv.remove(0) == true, "remove first -> true");
        check(inv.at(0) == &c, "remove first: remaining is c");

        check(inv.remove(0) == true, "remove last -> true");
        check(inv.size() == 0, "size after removing all");

        check(inv.remove(0) == false, "remove from empty -> false");
    }

    // ---------- 10. useAll: порядок и пустой инвентарь ----------
    {
        Inventory empty;
        check(empty.useAll().empty(), "useAll on empty inventory");

        Item item("I", 1);
        Weapon sword("Sword", 1, 10);
        Armor shield("Shield", 1, 5);
        Potion potion("Health", 1, 20);

        Inventory inv;
        inv.add(&item);
        inv.add(&sword);
        inv.add(&shield);
        inv.add(&potion);

        std::vector<std::string> msgs = inv.useAll();
        check(msgs.size() == 4, "useAll size");
        checkEq(msgs[0], "Item: I", "useAll[0]");
        checkEq(msgs[1], "Attack: Sword", "useAll[1]");
        checkEq(msgs[2], "Equip: Shield", "useAll[2]");
        checkEq(msgs[3], "Drink: Health", "useAll[3]");
        check(potion.quantity() == 0, "useAll consumed potion");
    }

    // ---------- 11. clear: пусто, повторный вызов ----------
    {
        Inventory inv;
        Item a("A", 1);
        Item b("B", 1);
        inv.add(&a);
        inv.add(&b);

        inv.clear();
        check(inv.size() == 0, "clear empties inventory");
        check(inv.at(0) == nullptr, "at after clear");
        check(inv.useAll().empty(), "useAll after clear");

        inv.clear();
        check(inv.size() == 0, "second clear safe");

        check(inv.add(&a) == true, "add after clear");
        check(inv.size() == 1, "size after add following clear");
    }

    // ---------- 12. Жизнь объектов: инвентарь не удаляет ----------
    {
        Inventory inv;
        Item a("A", 1);
        inv.add(&a);
        inv.remove(0);
        inv.add(&a);
        check(inv.find("A") == &a, "object alive after remove");
        inv.clear();
        inv.add(&a);
        check(inv.at(0) == &a, "object alive after clear");
    }

    std::cout << "Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
