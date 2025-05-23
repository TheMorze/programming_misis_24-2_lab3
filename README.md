# Лабораторная работа №3: Управление памятью и умные указатели

## Цели
- Понять принципы ручного и автоматического управления памятью в C++.
- Научиться использовать умные указатели (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`) для предотвращения утечек памяти и упрощения работы с ресурсами.
- Освоить концепцию RAII и уметь её применять.
- Разобрать отличия между разными видами умных указателей и научиться выбирать подходящий.

## Содержание
1. **Утечка памяти при ручном управлении**
2. **Использование `std::unique_ptr`**
3. **Использование `std::shared_ptr`**
4. **Использование `std::weak_ptr`**
5. **Принцип RAII**
6. **CMake и Git**

## 1. Утечка памяти при ручном управлении
Описание, как и почему возникает утечка при использовании `new` без `delete`.
Файл: `task1.cpp`.

## 2. `std::unique_ptr`
- Как `unique_ptr` решает проблему утечек памяти.
- Пример класса с RAII (`FileRAII`).
- Код в `task2.cpp`.

## 3. `std::shared_ptr`
- Пример разделяемого владения (несколько указателей на один объект).
- Подсчёт ссылок и автоматическое освобождение.
- Код в `task3.cpp`.

## 4. `std::weak_ptr`
- Пример сценария "наблюдателя" без продления времени жизни ресурса.
- Использование `weak_ptr.lock()` для проверки доступности объекта.
- Код в `task4.cpp`.

## 5. RAII
- Демонстрация использования класса, который захватывает ресурс в конструкторе и освобождает в деструкторе.
- Код: `FileRAII` в `task2.cpp`.

## 6. CMake и Git
- Процесс сборки через CMake (приложен `CMakeLists.txt`).
- Основы работы с Git (инициализация, коммиты, push).

## Отличия и рекомендации по выбору умных указателей

| Указатель          | Особенности                                                         | Когда использовать                                                 |
|--------------------|---------------------------------------------------------------------|---------------------------------------------------------------------|
| `std::unique_ptr`  | - Уникальное владение<br/>- Не копируется (только перемещение)      | - RAII для одиночного владельца<br/>- Чёткая передача владения      |
| `std::shared_ptr`  | - Разделяемое владение<br/>- Общий счётчик ссылок                   | - Когда ресурс нужен нескольким объектам<br/>- Автоматическое освобождение, когда счётчик достигает 0 |
| `std::weak_ptr`    | - Не владеет ресурсом<br/>- Не увеличивает счётчик ссылок           | - Наблюдение за объектом<br/>- Избежание циклических зависимостей (особенно вместе с `std::shared_ptr`) |

## Проверка на утечки памяти
- Valgrind:
  ```bash
  valgrind --leak-check=full ./task1
