#include <iostream>
#include <memory>
#include <vector>

class SharedData {
public:
    SharedData(int value) : data(value) {
        std::cout << "SharedData constructor. Value = " << data << std::endl;
    }
    ~SharedData() {
        std::cout << "SharedData destructor. Value = " << data << std::endl;
    }
    int getData() const { return data; }
private:
    int data;
};

void sharedPtrExample() {
    // Создаем shared_ptr на объект SharedData
    std::shared_ptr<SharedData> sharedPtr1 = std::make_shared<SharedData>(42);

    {
        // Создаем еще один shared_ptr, указывающий на тот же объект
        std::shared_ptr<SharedData> sharedPtr2 = sharedPtr1;

        std::cout << "sharedPtr1 use_count = " << sharedPtr1.use_count() << std::endl;
        std::cout << "sharedPtr2 use_count = " << sharedPtr2.use_count() << std::endl;

        // Оба указывают на один и тот же ресурс
        std::cout << "sharedPtr1 data = " << sharedPtr1->getData() << std::endl;
        std::cout << "sharedPtr2 data = " << sharedPtr2->getData() << std::endl;
    }
    // Выходим из блока, sharedPtr2 уничтожен, но ресурс еще жив,
    // так как sharedPtr1 продолжает владеть им.

    std::cout << "After block, sharedPtr1 use_count = " << sharedPtr1.use_count() << std::endl;
}

int main() {
    std::cout << "=== Demonstration of shared_ptr ===" << std::endl;
    sharedPtrExample();
    // Когда sharedPtr1 выйдет из области видимости (в конце main),
    // ресурс будет освобожден автоматически, если больше никто на него не ссылается.
    return 0;
}
