#include <iostream>
#include <memory>

class Observer {
public:
    // weak_ptr не увеличивает счетчик ссылок shared_ptr
    // значит, если объект освобождается у владельцев, здесь он тоже
    // становится недействительным
    std::weak_ptr<int> data;

    void checkData() {
        // Преобразуем weak_ptr во временный shared_ptr, чтобы проверить,
        // жив ли еще объект
        if (auto shared = data.lock()) {
            std::cout << "Observer sees data: " << *shared << std::endl;
        } else {
            std::cout << "Observed object has been freed.\n";
        }
    }
};

int main() {
    std::cout << "=== Demonstration of weak_ptr ===" << std::endl;

    Observer obs;
    {
        auto sharedPtr = std::make_shared<int>(100);
        obs.data = sharedPtr;  // Привязываем weak_ptr к живому shared_ptr

        std::cout << "Inside block, before destruction:\n";
        obs.checkData();
    }

    // Вышли из блока, sharedPtr уничтожен, объект освободился,
    // weak_ptr уже не валиден (не продляет время жизни).
    std::cout << "Outside block, after destruction:\n";
    obs.checkData();

    return 0;
}
