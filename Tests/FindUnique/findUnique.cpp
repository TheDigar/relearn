#include <iostream>
#include <map>
#include <limits>
using namespace std;

struct entry
{
    int ocurrences {0};
    int lastPosition{std::numeric_limits<int>::max()};
};

int main()
{
    cout << "Enter the string to be searched for the first unique character:" << endl;
    string input;
    cin >> input;

    map<char,entry> characterHash;

    //Populate hash with ocurrences and last position for each character present on the input string
    int position = 0;
    for (auto c : input)
    {
        ++characterHash[c].ocurrences;
        characterHash[c].lastPosition = position;
        ++position;
    }

    //Go through the characterHash looking for an unique character
    //if found stor its positions on the position local variable
    char uniqueChar{0};
    for (const auto& o : characterHash)
    {
        if((o.second.ocurrences == 1) && (o.second.lastPosition < position))
        {
            position = o.second.lastPosition;
            uniqueChar = o.first;
        }
    }


    if( position < input.size() )
        cout << "First Unique character: " << uniqueChar << " at " << position << endl;
    else
        cout << "No unique characters on input string!" << endl;

    return 0;
}
