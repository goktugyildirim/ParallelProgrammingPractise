#include <thread>
#include <iostream>

class MyClass{
public:

    MyClass()
    {
        unsigned int c = std::thread::hardware_concurrency();
        std::cout << "Maximum available thread count is: " << c <<  std::endl;

        std::thread thread_1(&MyClass::F1, 2);
        std::thread thread_2(&MyClass::F2, this, 2); // this due to static function

        thread_1.join();
        thread_2.join();

    }

    static void F1(const int& input1)
    {
        std::cout << "F1 is executed." << std::endl;
    }



    void F2(const int& input1)
    {
        std::cout << "F2 is executed." << std::endl;
    }

    
};

int main()
{
    MyClass obj_;

    return 0;
}