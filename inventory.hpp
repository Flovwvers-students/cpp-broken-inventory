#pragma once
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

class Item {
public:
    Item(const std::string& name, int quantity)
        : name_(name), quantity_(quantity < 0 ? 0 : quantity) {}

    virtual ~Item() = default;

    const std::string& name() const { return name_; }
    int quantity() const { return quantity_; }

    void setQuantity(int value) {
        quantity_ = (value < 0) ? 0 : value;
    }

    virtual std::string use() { return "Item: " + name_; }

protected:
    std::string name_;
    int quantity_;
};

class Weapon : public Item {
public:
    Weapon(const std::string& name, int quantity, int damage)
        : Item(name, quantity), damage_(damage < 0 ? 0 : damage) {}
    
    int damage() const { return damage_; }
    std::string use() override { return "Attack: " + name_; }

private:
    int damage_;
};

class Armor : public Item {
public:
    Armor(const std::string& name, int quantity, int defense)
        : Item(name, quantity), defense_(defense < 0 ? 0 : defense) {}
    
    int defense() const { return defense_; }
    std::string use() override { return "Equip: " + name_; }

private:
    int defense_;
};

class Potion : public Item {
public:
    Potion(const std::string& name, int quantity, int healing)
        : Item(name, quantity), healing_(healing < 0 ? 0 : healing) {}
    
    int healing() const { return healing_; }
    
    std::string use() override {
        if (quantity_ == 0) {
            return "Empty: " + name_;
        }
        --quantity_;
        return "Drink: " + name_;
    }

private:
    int healing_;
};

class Inventory {
public:
    bool add(Item* item) {
        if (item == nullptr) {
            return false;
        }
        if (std::find(items_.begin(), items_.end(), item) != items_.end()) {
            return false;
        }
        items_.push_back(item);
        return true;
    }

    std::size_t size() const { 
        return items_.size(); 
    }

    Item* at(std::size_t index) const {
        if (index >= items_.size()) {
            return nullptr;
        }
        return items_[index];
    }

    Item* find(const std::string& name) const {
        for (Item* item : items_) {
            if (item->name() == name) {
                return item;
            }
        }
        return nullptr;
    }

    bool remove(std::size_t index) {
        if (index >= items_.size()) {
            return false;
        }
        items_.erase(items_.begin() + index); 
        return true;
    }

    std::vector<std::string> useAll() {
        std::vector<std::string> messages;
        for (Item* item : items_) {
            messages.push_back(item->use());
        }
        return messages;
    }

    void clear() { 
        items_.clear(); 
    }

private:
    std::vector<Item*> items_;
}; 
