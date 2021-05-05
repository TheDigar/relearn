//STD includes
#include <algorithm>
#include <chrono>
#include <iostream>

//My includes
#include <MyVector.h>

int main()
{
    MyVector v1{10000000};
    MyVector v2 {10000000};

    auto t1 = std::chrono::steady_clock::now();
    MyVector v3 = std::move(v1);
    auto t2 = std::chrono::steady_clock::now();
    auto d_nano = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();

    std::cout << "Move time: " << d_nano << std::endl;
}
