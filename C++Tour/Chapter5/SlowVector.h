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
    double& operator[](int);
};