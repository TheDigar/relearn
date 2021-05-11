template <typename T>
class MyVector
{
private:
    int size;
    T* data;
public:
    explicit MyVector(int);
    MyVector(const MyVector&); //copy constructor
    MyVector(MyVector&&); //move constructor

    ~MyVector();

    MyVector& operator=(const MyVector&); //copy assignment
    MyVector& operator=(MyVector&&); //move assignment
    T& operator[](int);
};


template <typename T> 
MyVector<T>::MyVector(int sz)
{
    if(sz < 0)
        sz = 0;
    size = sz;
    data = new T[size];
}


//Copy Constructor
template <typename T>
MyVector<T>::MyVector(const MyVector<T>& v) :
size{v.size}
{
    data = new T[size];
    for(int i = 0; i < size; ++i)
    {
        data[i] = v.data[i];
    }
}

//Move Constructor
template <typename T>
MyVector<T>::MyVector(MyVector<T>&& v):
size{v.size},
data{v.data}
{
    v.size = 0;
    v.data = nullptr;
}

//Destructor
template <typename T>
MyVector<T>::~MyVector()
{
    delete[] data;
}


//Operators
//Copy assignment
template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &v)
{
    delete[] data;
    size = v.size;
    data = new T[size];
    for(int i =0; i < size; ++i)
    {
        data[i] = v.data[i];
    }
}

//Move assignment
template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector<T> && v)
{
    delete[] data;
    size = v.size;
    data = v.data;
    v.size = 0;
    v.data = nullptr;

}

template <typename T>
T& MyVector<T>::operator[](int i) 
{
    return data[i];
}
