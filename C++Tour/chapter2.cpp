#include <iostream>

using namespace std;
enum class Traffic_light
{
    green,
    yellow,
    red    
};
Traffic_light& operator++ (Traffic_light& t)
{
    switch (t)
    {
    case Traffic_light::green:
        return t = Traffic_light::yellow;
    case Traffic_light::yellow:
        return t = Traffic_light::red;
    case Traffic_light::red:
        return t = Traffic_light::green;
    }
}

void printLight(Traffic_light& t)
{
    switch (t)
    {
    case Traffic_light::green:
        cout << "Green\n";
        break;
    case Traffic_light::yellow:
        cout << "Yellow\n";
        break;
    case Traffic_light::red:
        cout << "Red\n";
        break;
    }
}

int main()
{
    Traffic_light light{Traffic_light::green};
    cout << "what's the starting state for the traffic light?\n0 - green\n1 - yellow\n2 - red\n";
    int startingLightStatus{0}; //Starting at green light as default
    cin >> startingLightStatus;
    switch (startingLightStatus)
    {
    case 0:
         cout << "Starting at the green light!\n";       
        break;
    case 1:
         cout << "Starting at the yellow light!\n";
         light = Traffic_light::yellow;
        break;
    case 2:
         cout << "Starting at the red light!\n";
         light = Traffic_light::red;
        break;    
    default:
        startingLightStatus = 0;
         cout << "Assuming '0'\nStarting at the green light!\n";
        break;
    }

    cout << "How many iteractions?\n";
    
    int i;
    cin >> i;
    for (;i > 0; --i)
    {
        printLight(light);
        ++light;
    }

    
    return 0;
}