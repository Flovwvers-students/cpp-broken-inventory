#pragma once

#include "item.h"

#include <string>

class Armor final : public Item
{
public:
    Armor(const std::string& name, int quantity, int defense);

    ~Armor() override = default;

    [[nodiscard]] int GetDefense() const noexcept;

    std::string Use() override;

private:
    int m_defense;
};
