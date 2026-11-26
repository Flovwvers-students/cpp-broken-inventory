#include "potion.h"

Potion::Potion(const std::string& name, int quantity, int healing)
    : Item(name, quantity)
    , m_healing(healing < 0 ? 0 : healing)
{
}

int Potion::GetHealing() const noexcept
{
    return m_healing;
}

std::string Potion::Use()
{
    const int currentQuantity = GetQuantity();
    if (currentQuantity == 0)
    {
        return "Empty: " + GetName();
    }

    SetQuantity(currentQuantity - 1);
    return "Drink: " + GetName();
}
