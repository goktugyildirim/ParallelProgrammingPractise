#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <memory>
#include <functional>
#include <atomic>

class MyClass{
public:
    MyClass()
    {
        unsigned int c = std::thread::hardware_concurrency();
        std::cout << "Maximum available thread count is: " << c <<  std::endl;

        std::vector<int> shared_data = {1,2,3,4,5};
        std::atomic<int> shared_atomic_data(5);

        std::mutex m;


        std::thread thread_1([&shared_data, &m](){return F1(2,shared_data, m);});
        std::thread thread_2(&MyClass::F2, this, 2, std::ref(shared_data));

        thread_2.join();
        thread_1.join();

    }

    static void F1(const int& input1, std::vector<int>& shared_data, std::mutex& m)
    {
        std::cout << "F1 is executed." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::lock_guard<std::mutex> guard(m);
        std::scoped_lock
        shared_data.push_back(6);

        std::cout << "Done1." << std::endl;


    }



    void F2(const int& input1, std::vector<int>& shared_data)
    {
        std::cout << "F2 is executed." << std::endl;

        for(int i=0; i<10000000000; i++)
            shared_data.push_back(i);

        std::cout << shared_data.size() << std::endl;

        std::cout << "Done2." << std::endl;
    }


};

int main()
{
    MyClass obj_;

    return 0;
}