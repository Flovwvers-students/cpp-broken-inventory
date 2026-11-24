\# Отчёт по практике C++: сломанный инвентарь



ФИО: Барашев Григорий Романович

Группа:24.2



\## Исправления



| Ошибка | Причина | Исправление | Проверка |

|---|---|---|---|

| Отрицательное количество не превращалось в 0 | Конструктор и setQuantity сохраняли любое значение | Добавлено `quantity < 0 ? 0 : quantity` | Тесты `negative quantity -> 0`, `setQuantity negative -> 0` |

| `use` не был виртуальным | В `Item` отсутствовал `virtual`, в наследниках не было `override` | `virtual std::string use()` в Item, `override` в наследниках | Тест `virtual dispatch weapon`, секция 3 в tests.cpp |

| `Weapon/Armor/Potion` принимали отрицательные характеристики | Конструкторы не проверяли знак | Ограничение снизу нулём | Тесты `negative damage/defense/healing -> 0` |

| `Potion::use` увеличивал количество и возвращал `Drink` при 0 | Инвертированная логика | При qty>0 уменьшаем на 1 и `Drink`, иначе `Empty` | Секция 4 в tests.cpp |

| `add(nullptr)` возвращал true | Неверное условие | `return false` при `nullptr` | Тест `add nullptr -> false` |

| `add` дубликата возвращал true | Неверное условие | `return false` при найденном адресе | Тест `add duplicate address -> false` |

| `size` возвращал `items\_.size() + 1` | Лишняя единица | `return items\_.size()` | Тесты `empty size`, `one object`, `size counts pointers` |

| `find` возвращал несовпадающий элемент | Условие `!=` вместо `==` | `if (item->name() == name)` | Тест `find returns first match` |

| `remove` удалял последний элемент вместо указанного | `pop\_back()` вместо `erase` | `items\_.erase(items\_.begin() + index)` | Секция 9 в tests.cpp |

| `clear` ничего не делал | Пустое тело метода | `items\_.clear()` | Секция 11 в tests.cpp |



\## Дополненные тесты



В `tests.cpp` добавлены проверки на:

\- пустой инвентарь, `nullptr`, повторный адрес;

\- одинаковые имена разных объектов, регистр в `find`;

\- отрицательные характеристики;

\- нулевое количество зелья;

\- неверные индексы в `at` и `remove`;

\- удаление первого, среднего, последнего;

\- `useAll` через `Item\*` с проверкой порядка;

\- `clear` дважды;

\- жизнь объектов после `remove`/`clear`.



\## Сборка и тесты

cmake -S . -B build -G "Unix Makefiles" -DCMAKE\_CXX\_COMPILER=C:/Users/Lenovo/gcc/bin/g++.exe -DCMAKE\_MAKE\_PROGRAM=C:/Users/Lenovo/gcc/bin/make.exe

cmake --build build

ctest --test-dir build --output-on-failure



Результат: `100% tests passed`.



\## Полиморфизм и владение



`Inventory` хранит `Item\*`, но не владеет предметами. Объекты создаются снаружи и должны жить дольше инвентаря. `remove` и `clear` убирают только указатели, не удаляя сами объекты — поэтому `new`/`delete` не используются.



Полиморфизм: `use` объявлен `virtual` в `Item` и переопределён через `override` в `Weapon`, `Armor`, `Potion`. В `useAll` вызов идёт через `Item\*`, и попадает в реализацию фактического класса.

