#include "Filter.h"
#include <algorithm>
#include <string>
#include <iostream>

std::set<std::string> ReadFilterWords(const std::string& fileName)
{
    std::ifstream file(fileName);
    std::set<std::string> filter;
    if (!file.is_open())
    {
        std::cout << "Failed to open '" << &file << "' for reading\n";
    }
    else
    {
        std::string line;
        std::string word;
        while (getline(file, line))
        {
            for (unsigned i = 0; i < line.length(); i++)
            {
                if (line[i] == ' ' || line[i] == '\n')
                {
                    if (!word.empty())
                    {
                        filter.insert(word);
                    }
                    word = "";
                    continue;
                }
                word += tolower(line[i]);
            }
        }
        if (!word.empty())
        {
            filter.insert(word);
        }
    }

    return filter;
}

std::string Filter(const std::string& str, const std::set<std::string> &filter)
{
    std::string word;
    std::string line;
    bool hasSpace = false;
    for (unsigned i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            hasSpace = true;
            std::string copyWord = word;
            std::transform(copyWord.begin(), copyWord.end(), copyWord.begin(), tolower);
            if (filter.find(copyWord) == filter.end() && !word.empty())
            {
                line += word;
            }
            word = "";
            continue;
        }
        if (hasSpace && i != str.length() && line[line.length() - 1] != ' ')
        {
            line += " ";
        }
        word += str[i];
        hasSpace = false;
    }
    
    std::string copyWord = word;
    std::transform(copyWord.begin(), copyWord.end(), copyWord.begin(), tolower);
    if (!word.empty() && filter.find(copyWord) == filter.end())
    {
        line += word;
    }
    if (!line.empty() && line[line.length() - 1] == ' ')
    {
        line.erase(line.length() - 1, 1);
    }
    return line;
}


void FilterLines(std::istream& input, std::ostream& output, const std::set<std::string> &filter)
{
    std::string line;
    bool isFirstLine = true;
    while (std::getline(input, line))
    {
        if (!isFirstLine)
        {
            output << "\n";
        }
        output << Filter(line, filter);
        isFirstLine = false;
    }
}