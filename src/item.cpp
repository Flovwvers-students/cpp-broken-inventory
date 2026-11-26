#include "item.h"

Item::Item(const std::string& name, int quantity)
    : m_name(name)
    , m_quantity(quantity < 0 ? 0 : quantity)
{
}

const std::string& Item::GetName() const noexcept
{
    return m_name;
}

int Item::GetQuantity() const noexcept
{
    return m_quantity;
}

void Item::SetQuantity(int value) noexcept
{
    m_quantity = value < 0 ? 0 : value;
}

std::string Item::Use()
{
    return "Item: " + m_name;
}
