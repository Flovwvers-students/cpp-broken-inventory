#pragma once

#include "item.h"

#include <cstddef>
#include <string>
#include <vector>

class Inventory
{
public:
    [[nodiscard]] std::size_t GetSize() const noexcept;
    [[nodiscard]] Item* At(std::size_t index) const noexcept;
    [[nodiscard]] Item* Find(const std::string& name) const;

    bool Add(Item* item);
    bool Remove(std::size_t index);
    std::vector<std::string> UseAll();
    void Clear() noexcept;

private:
    std::vector<Item*> m_items;
};
