#include "armor.h"
#include "inventory.h"
#include "item.h"
#include "potion.h"
#include "weapon.h"

#include <iostream>
#include <vector>

namespace
{
void Check(bool condition, const char* label, int& failures)
{
    if (!condition)
    {
        std::cerr << "FAIL: " << label << '\n';
        ++failures;
    }
}
}

int main()
{
    int failures = 0;

    Item baseDefault("Stone", 3);
    Check(baseDefault.GetName() == "Stone", "item name", failures);
    Check(baseDefault.GetQuantity() == 3, "item quantity", failures);
    Check(baseDefault.Use() == "Item: Stone", "item use message", failures);
    Check(baseDefault.GetQuantity() == 3, "item use keeps quantity", failures);

    Item baseEmptyName("", -10);
    Check(baseEmptyName.GetName().empty(), "item empty name preserved", failures);
    Check(baseEmptyName.GetQuantity() == 0, "item negative quantity clamped to 0", failures);
    Check(baseEmptyName.Use() == "Item: ", "item empty name use message", failures);

    baseDefault.SetQuantity(7);
    Check(baseDefault.GetQuantity() == 7, "item setQuantity positive", failures);
    baseDefault.SetQuantity(-5);
    Check(baseDefault.GetQuantity() == 0, "item setQuantity negative clamped to 0", failures);
    Check(baseDefault.Use() == "Item: Stone", "item use at zero quantity", failures);
    Check(baseDefault.GetQuantity() == 0, "item quantity remains zero", failures);

    Weapon sword("Sword", 2, 15);
    Check(sword.GetName() == "Sword", "weapon name", failures);
    Check(sword.GetQuantity() == 2, "weapon quantity", failures);
    Check(sword.GetDamage() == 15, "weapon damage", failures);
    Check(sword.Use() == "Attack: Sword", "weapon use", failures);
    Check(sword.GetQuantity() == 2, "weapon use keeps quantity", failures);

    Weapon brokenSword("Rusty", -3, -25);
    Check(brokenSword.GetQuantity() == 0, "weapon negative quantity clamped", failures);
    Check(brokenSword.GetDamage() == 0, "weapon negative damage clamped", failures);
    Check(brokenSword.Use() == "Attack: Rusty", "weapon use at zero quantity", failures);
    Check(brokenSword.GetQuantity() == 0, "weapon quantity stays zero", failures);

    Armor shield("Shield", 1, 8);
    Check(shield.GetName() == "Shield", "armor name", failures);
    Check(shield.GetQuantity() == 1, "armor quantity", failures);
    Check(shield.GetDefense() == 8, "armor defense", failures);
    Check(shield.Use() == "Equip: Shield", "armor use", failures);
    Check(shield.GetQuantity() == 1, "armor use keeps quantity", failures);

    Armor brokenShield("Broken", -1, -12);
    Check(brokenShield.GetQuantity() == 0, "armor negative quantity clamped", failures);
    Check(brokenShield.GetDefense() == 0, "armor negative defense clamped", failures);
    Check(brokenShield.Use() == "Equip: Broken", "armor use at zero quantity", failures);

    Potion potion("Health", 2, 20);
    Check(potion.GetName() == "Health", "potion name", failures);
    Check(potion.GetQuantity() == 2, "potion quantity", failures);
    Check(potion.GetHealing() == 20, "potion healing", failures);
    Check(potion.Use() == "Drink: Health", "potion first drink", failures);
    Check(potion.GetQuantity() == 1, "potion quantity decremented to 1", failures);
    Check(potion.Use() == "Drink: Health", "potion second drink", failures);
    Check(potion.GetQuantity() == 0, "potion quantity decremented to 0", failures);
    Check(potion.Use() == "Empty: Health", "potion empty message", failures);
    Check(potion.GetQuantity() == 0, "potion empty stays 0", failures);

    Potion brokenPotion("Weak", -4, -30);
    Check(brokenPotion.GetQuantity() == 0, "potion negative quantity clamped", failures);
    Check(brokenPotion.GetHealing() == 0, "potion negative healing clamped", failures);
    Check(brokenPotion.Use() == "Empty: Weak", "potion starts empty", failures);

    Item* basePtrWeapon = &sword;
    Item* basePtrArmor = &shield;
    Item* basePtrPotion = &potion;
    Check(basePtrWeapon->Use() == "Attack: Sword", "virtual dispatch weapon", failures);
    Check(basePtrArmor->Use() == "Equip: Shield", "virtual dispatch armor", failures);
    Check(basePtrPotion->Use() == "Empty: Health", "virtual dispatch potion", failures);


    Inventory inv;
    Check(inv.GetSize() == 0, "empty inventory size", failures);
    Check(inv.At(0) == nullptr, "empty inventory at(0)", failures);
    Check(inv.Find("Sword") == nullptr, "empty inventory find", failures);
    Check(!inv.Remove(0), "empty inventory remove(0)", failures);
    Check(inv.UseAll().empty(), "empty inventory useAll", failures);
    inv.Clear();
    Check(inv.GetSize() == 0, "empty inventory clear safe", failures);

    Check(!inv.Add(nullptr), "add nullptr rejected", failures);
    Check(inv.GetSize() == 0, "size unchanged after nullptr", failures);

    Check(inv.Add(&sword), "add weapon", failures);
    Check(inv.GetSize() == 1, "size is 1 after adding weapon", failures);
    Check(!inv.Add(&sword), "duplicate pointer rejected", failures);
    Check(inv.GetSize() == 1, "size unchanged after duplicate pointer", failures);

    Weapon sameNameSword("Sword", 5, 30);
    Check(inv.Add(&sameNameSword), "different object with same name allowed", failures);
    Check(inv.GetSize() == 2, "size is 2 with same-name distinct objects", failures);
    Check(inv.Find("Sword") == &sword, "find returns first matching pointer", failures);
    Check(inv.Find("sword") == nullptr, "find is case-sensitive", failures);
    Check(inv.Find("Missing") == nullptr, "find missing returns nullptr", failures);

    Check(inv.Add(&shield), "add shield", failures);
    potion.SetQuantity(1);
    Check(inv.Add(&potion), "add potion", failures);
    Check(inv.GetSize() == 4, "size is 4 objects not sum of quantities", failures);

    Check(inv.At(0) == &sword, "at(0)", failures);
    Check(inv.At(1) == &sameNameSword, "at(1)", failures);
    Check(inv.At(2) == &shield, "at(2)", failures);
    Check(inv.At(3) == &potion, "at(3)", failures);
    Check(inv.At(4) == nullptr, "at out of range", failures);

    const std::vector<std::string> messages = inv.UseAll();
    Check(messages.size() == 4, "useAll message count", failures);
    Check(messages[0] == "Attack: Sword", "useAll[0]", failures);
    Check(messages[1] == "Attack: Sword", "useAll[1]", failures);
    Check(messages[2] == "Equip: Shield", "useAll[2]", failures);
    Check(messages[3] == "Drink: Health", "useAll[3]", failures);
    Check(potion.GetQuantity() == 0, "useAll decremented potion once", failures);

    Check(!inv.Remove(4), "remove out of range", failures);
    Check(inv.GetSize() == 4, "size unchanged after invalid remove", failures);

    Check(inv.Remove(1), "remove middle element", failures);
    Check(inv.GetSize() == 3, "size after middle remove", failures);
    Check(
        inv.At(0) == &sword && inv.At(1) == &shield && inv.At(2) == &potion,
        "order preserved after middle remove",
        failures);
    Check(sameNameSword.GetQuantity() == 5, "removed object still alive", failures);

    Check(inv.Remove(0), "remove first element", failures);
    Check(inv.GetSize() == 2, "size after first remove", failures);
    Check(
        inv.At(0) == &shield && inv.At(1) == &potion,
        "order preserved after first remove",
        failures);

    Check(inv.Remove(1), "remove last element", failures);
    Check(inv.GetSize() == 1, "size after last remove", failures);
    Check(inv.At(0) == &shield, "remaining element after last remove", failures);

    inv.Clear();
    Check(inv.GetSize() == 0, "clear empties inventory", failures);
    Check(inv.At(0) == nullptr, "at(0) nullptr after clear", failures);
    Check(shield.GetQuantity() == 1, "objects still alive after clear", failures);
    inv.Clear();
    Check(inv.GetSize() == 0, "second clear is safe", failures);

    std::cout << "Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
