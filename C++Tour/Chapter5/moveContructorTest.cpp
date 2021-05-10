//STD includes
#include <chrono>
#include <iostream>

//My includes
#include <MyVector.h>

int main()
{
    //Even smaller vectors will show the differece between a copy and a move
    MyVector v1{1000};

    //Using std::chrono to measure operation time, good enough to demonstrate the difference here
    auto t1 = std::chrono::steady_clock::now();
    MyVector v2 = v1;
    auto t2 = std::chrono::steady_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    std::cout << "Copy time: " << delta << std::endl;

    t1 = std::chrono::steady_clock::now();
    MyVector v3 = std::move(v1);
    t2 = std::chrono::steady_clock::now();
    delta = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    std::cout << "Move time: " << delta << std::endl;
}
