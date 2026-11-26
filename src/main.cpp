#include "armor.h"
#include "inventory.h"
#include "item.h"
#include "potion.h"
#include "weapon.h"

#include <iostream>

int main()
{
    Weapon sword("Sword", 1, 10);
    Armor shield("Shield", 1, 5);
    Potion potion("Health", 2, 20);

    Inventory inventory;
    inventory.Add(&sword);
    inventory.Add(&shield);
    inventory.Add(&potion);

    for (const auto& message : inventory.UseAll())
    {
        std::cout << message << '\n';
    }

    std::cout << "Objects: " << inventory.GetSize() << '\n';

    Item* baseWeapon = &sword;
    Item* baseArmor = &shield;
    Item* basePotion = &potion;

    std::cout << "Polymorphic calls:\n";
    std::cout << baseWeapon->Use() << '\n';
    std::cout << baseArmor->Use() << '\n';
    std::cout << basePotion->Use() << '\n';

    return 0;
}
