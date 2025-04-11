#include <iostream>
#include <memory>
#include <fstream>

// Пример класса, который управляет ресурсом (файл) через RAII
class FileRAII {
private:
    std::unique_ptr<std::fstream> file;
public:
    // Открываем файл в конструкторе (активация ресурса)
    FileRAII(const std::string& filename) {
        file = std::make_unique<std::fstream>(filename, std::ios::out);
        if (file->is_open()) {
            std::cout << "File '" << filename << "' opened.\n";
        } else {
            std::cout << "Failed to open file '" << filename << "'.\n";
        }
    }

    // Деструктор автоматически закрывает файл (освобождение ресурса)
    ~FileRAII() {
        if (file && file->is_open()) {
            file->close();
            std::cout << "File closed in destructor.\n";
        }
    }

    // Можно добавить метод для записи в файл
    void write(const std::string &text) {
        if (file && file->is_open()) {
            (*file) << text << std::endl;
        }
    }
};

void uniquePtrExample() {
    for (int i = 0; i < 100; ++i) {
        // std::unique_ptr автоматически освободит память
        std::unique_ptr<int> ptr = std::make_unique<int>(i);
        // Можно безопасно использовать ptr
    }
    // Выход из функции — все объекты unique_ptr освобождаются автоматически
}

int main() {
    std::cout << "=== Demonstration of unique_ptr and RAII ===" << std::endl;

    // Устраняем утечку памяти из задачи 1, используя unique_ptr
    uniquePtrExample();

    // Демонстрация RAII: управление файлом
    {
        FileRAII file("example.txt");
        file.write("Hello from RAII-managed file!");
        // При выходе из блока деструктор закроет файл автоматически
    }

    return 0;
}
