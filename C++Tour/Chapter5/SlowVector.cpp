
#include <SlowVector.h>

//Constructors
SlowVector::SlowVector(int sz)
:size{sz}
{
    data = new double[size];
}

//Copy Constructor
SlowVector::SlowVector(const SlowVector& v) :
size{v.size}
{
    data = new double[size];
    for(int i =0; i < size; ++i)
    {
        data[i] = v.data[i];
    }
}

//Move Constructor
SlowVector::SlowVector(SlowVector&& v):
size{v.size},
data{v.data}
{
    v.size = 0;
    v.data = nullptr;
}

//Destructor
SlowVector::~SlowVector()
{
    delete[] data;
}


//Operators
//Copy assignment
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

//Move assignment
SlowVector &SlowVector::operator=(SlowVector && v)
{
    delete[] data;
    size = v.size;
    data = v.data;
    v.size = 0;
    v.data = nullptr;

}

double& SlowVector::operator[](int i) 
{
    return data[i];
}