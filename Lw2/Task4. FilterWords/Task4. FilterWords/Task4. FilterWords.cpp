#include <iostream>
#include <string>
#include <set>
#include <optional>
#include "Filter.h"

using namespace std;

optional<string> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: FilterWords.exe <input>\n";
        return std::nullopt;
    }
    return argv[1];
}



int main(int argc, char *argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    set<string> filter = ReadFilterWords(args.value());

    string line;
    while (getline(cin, line))
    {
        cout << Filter(line, filter) << endl;
    }

    return 0;
}