#include "inventory.h"

#include <algorithm>
#include <iterator>

std::size_t Inventory::GetSize() const noexcept
{
    return m_items.size();
}

Item* Inventory::At(std::size_t index) const noexcept
{
    if (index >= m_items.size())
    {
        return nullptr;
    }

    return m_items[index];
}

Item* Inventory::Find(const std::string& name) const
{
    for (Item* item : m_items)
    {
        if (item->GetName() == name)
        {
            return item;
        }
    }

    return nullptr;
}

bool Inventory::Add(Item* item)
{
    if (item == nullptr)
    {
        return false;
    }

    if (std::find(m_items.begin(), m_items.end(), item) != m_items.end())
    {
        return false;
    }

    m_items.push_back(item);
    return true;
}

bool Inventory::Remove(std::size_t index)
{
    if (index >= m_items.size())
    {
        return false;
    }

    m_items.erase(m_items.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

std::vector<std::string> Inventory::UseAll()
{
    std::vector<std::string> messages;
    messages.reserve(m_items.size());

    for (Item* item : m_items)
    {
        messages.push_back(item->Use());
    }

    return messages;
}

void Inventory::Clear() noexcept
{
    m_items.clear();
}
