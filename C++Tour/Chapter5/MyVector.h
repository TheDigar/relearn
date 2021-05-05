class MyVector
{
private:
    int size;
    double* data;
public:
    MyVector(int);
    MyVector(const MyVector&); //copy constructor
    MyVector(MyVector&&); //move constructor

    ~MyVector();

    MyVector& operator=(const MyVector&); //copy assignment
    MyVector& operator=(MyVector&&); //move assignment
    double& operator[](int);
};