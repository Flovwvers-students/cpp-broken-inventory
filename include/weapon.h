#pragma once

#include "item.h"

#include <string>

class Weapon final : public Item
{
public:
    Weapon(const std::string& name, int quantity, int damage);

    ~Weapon() override = default;

    [[nodiscard]] int GetDamage() const noexcept;

    std::string Use() override;

private:
    int m_damage;
};
