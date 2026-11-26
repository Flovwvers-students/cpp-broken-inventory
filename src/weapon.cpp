#include "weapon.h"

Weapon::Weapon(const std::string& name, int quantity, int damage)
    : Item(name, quantity)
    , m_damage(damage < 0 ? 0 : damage)
{
}

int Weapon::GetDamage() const noexcept
{
    return m_damage;
}

std::string Weapon::Use()
{
    return "Attack: " + GetName();
}
