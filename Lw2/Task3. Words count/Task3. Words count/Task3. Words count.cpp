#include <iostream>
#include <string>
#include <map>
#include "Count.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    map<string, int> frequency;
    string line;

    while (getline(cin, line))
    {
        Count(line, frequency);
    }

    for (const auto& word : frequency)
    {
        cout << word.first << " was suspected " << word.second << " times" << endl;
    }
    return 0;
}
