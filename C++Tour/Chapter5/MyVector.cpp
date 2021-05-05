
#include <MyVector.h>

//Constructors
MyVector::MyVector(int sz)
:size{sz}
{
    data = new double[size];
}

//Copy Constructor
MyVector::MyVector(const MyVector& v) :
size{v.size}
{
    data = new double[size];
    for(int i =0; i < size; ++i)
    {
        data[i] = v.data[i];
    }
}

//Move Constructor
MyVector::MyVector(MyVector&& v):
size{v.size},
data{v.data}
{
    v.size = 0;
    v.data = nullptr;
}

//Destructor
MyVector::~MyVector()
{
    delete[] data;
}


//Operators
//Copy assignment
MyVector &MyVector::operator=(const MyVector &v)
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
MyVector &MyVector::operator=(MyVector && v)
{
    delete[] data;
    size = v.size;
    data = v.data;
    v.size = 0;
    v.data = nullptr;

}

double& MyVector::operator[](int i) 
{
    return data[i];
}