#include <iostream>

// Функция, демонстрирующая утечку памяти
// Из-за бесконечного цикла память не освобождается
// (delete не вызывается)
void memoryLeak() {
    for (int i = 0; i < 100; ++i) {
        // Выделяем память, но не освобождаем
        int* leak = new int(i);
        // Некоторые действия...
        // delete leak; // <- Этой строки нет, что приводит к утечке
    }
}

int main() {
    std::cout << "=== Demonstration of Memory Leak ===" << std::endl;
    memoryLeak();

    return 0;
}
