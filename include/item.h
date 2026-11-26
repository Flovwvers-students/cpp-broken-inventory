#pragma once

#include <string>

class Item
{
public:
    Item(const std::string& name, int quantity);

    virtual ~Item() = default;

    [[nodiscard]] const std::string& GetName() const noexcept;
    [[nodiscard]] int GetQuantity() const noexcept;

    void SetQuantity(int value) noexcept;

    virtual std::string Use();

private:
    std::string m_name;
    int m_quantity;
};
