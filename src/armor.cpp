#include "armor.h"

Armor::Armor(const std::string& name, int quantity, int defense)
    : Item(name, quantity)
    , m_defense(defense < 0 ? 0 : defense)
{
}

int Armor::GetDefense() const noexcept
{
    return m_defense;
}

std::string Armor::Use()
{
    return "Equip: " + GetName();
}
