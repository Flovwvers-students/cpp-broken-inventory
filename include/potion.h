#pragma once

#include "item.h"

#include <string>

class Potion final : public Item
{
public:
    Potion(const std::string& name, int quantity, int healing);

    ~Potion() override = default;

    [[nodiscard]] int GetHealing() const noexcept;

    std::string Use() override;

private:
    int m_healing;
};
