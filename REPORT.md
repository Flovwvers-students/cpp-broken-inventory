# Отчёт по практической работе C++: сломанный инвентарь

- **Студент:** Завалишин Дмитрий
- **Группа:** 33/2
- **Ветка:** `zavalishin-dmitriy`

## 1. Найденные и исправленные ошибки

1. **Отрицательное количество (`Item`):** в конструкторе и `SetQuantity` добавлена проверка `< 0` с заменой на `0`. Проверено тестами `item negative quantity clamped to 0` и `item setQuantity negative clamped to 0`.
2. **Отрицательные характеристики (`Weapon`, `Armor`, `Potion`):** урон, защита и лечение в конструкторах ограничены снизу нулём. Проверено тестами на отрицательные характеристики.
3. **Полиморфизм `Use()` через `Item*`:** в `Item` метод объявлен как `virtual`, в наследниках добавлен `override`. Проверено тестами `virtual dispatch weapon/armor/potion`.
4. **Логика `Potion::Use()`:** при `GetQuantity() == 0` возвращается `"Empty: " + GetName()`, иначе выполняется `SetQuantity(GetQuantity() - 1)` и возвращается `"Drink: " + GetName()`. Проверено тестами `potion first/second drink` и `potion empty message`.
5. **Проверка `nullptr` и дубликатов в `Inventory::Add`:** при `nullptr` или повторном адресе возвращается `false`, размер не меняется. Проверено тестами `add nullptr rejected` и `duplicate pointer rejected`.
Remove()` и `Clear()`.

## 3. Команды сборки и проверки

```sh
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
./build/inventory_demo
ctest --test-dir build --output-on-failure
```

Результат: 100% tests passed, 0 tests failed out of 1.
