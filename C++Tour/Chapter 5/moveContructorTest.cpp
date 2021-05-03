#include <algorithm>
#include <chrono>
#include <iostream>


class SlowVector
{
private:
    int size;
    double* data;
public:
    SlowVector(int);
    SlowVector(const SlowVector&); //copy constructor
    SlowVector(SlowVector&&); //move constructor

    ~SlowVector();

    SlowVector& operator=(const SlowVector&); //copy assignment
    SlowVector& operator=(SlowVector&&); //move assignment
    double& operator[](int i) {return data[i];}
};

SlowVector::SlowVector(int sz)
:size{sz}
{
    data = new double[size];
}

SlowVector::SlowVector(const SlowVector& v) :
size{v.size}
{
    data = new double[size];
    for(int i =0; i < size; ++i)
    {
        data[i] = v.data[i];
    }
}

SlowVector &SlowVector::operator=(const SlowVector &v)
{
    delete[] data;
    size = v.size;
    data = new double[size];
    for(int i =0; i < size; ++i)
    {
        data[i] = v.data[i];
    }
}

SlowVector &SlowVector::operator=(SlowVector && v)
{
    delete[] data;
    size = v.size;
    data = v.data;
    v.size = 0;
    v.data = nullptr;

}

SlowVector::SlowVector(SlowVector&& v):
size{v.size},
data{v.data}
{
    v.size = 0;
    v.data = nullptr;
}

SlowVector::~SlowVector()
{
    delete[] data;
}

int main()
{
    SlowVector v1{10000000};
    SlowVector v2 {10000000};

    auto t1 = std::chrono::steady_clock::now();
    SlowVector v3 = std::move(v1);
    auto t2 = std::chrono::steady_clock::now();
    auto d_nano = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();

    std::cout << "Move time: " << d_nano << std::endl;
}
