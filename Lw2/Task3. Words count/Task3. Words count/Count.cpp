#include "Count.h"

void Count(const std::string& line, std::map<std::string, int> &frequency)
{
    std::string word;
    for (unsigned i = 0; i <= line.length(); i++)
    {
        if (!isalpha(line[i]) || i == line.length())
        {
            if (!word.empty())
            {
                frequency[word]++;
            }
            word = "";
            continue;
        }

        word += tolower(line[i]);
    }
}
