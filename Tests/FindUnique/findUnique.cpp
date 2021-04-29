#include <iostream>
#include <map>
using namespace std;

struct entry
{
    int count;
    int position;
};

int main()
{
    string input;
    cin >> input;

    // map<char,entry> ocurrences;
    entry ocurrences[256];
    for (auto &o : ocurrences)
    {
        o = {0, 0};
    }

    int position = 0;
    for (auto c : input)
    {
        ++ocurrences[c].count;
        ocurrences[c].position = position;
        ++position;
    }

    char unique{0};
    char i{0};
    for (const auto& o : ocurrences)
    {
        if((o.count == 1) && (o.position < position))
        {
            position = o.position;
            unique = i;
        }
        ++i;
    }



    if( position < input.size() )
        cout << "First Unique character: " << unique << " at " << position << endl;
    else
        cout << "No unique characters on input string!" << endl;

    return 0;
}
