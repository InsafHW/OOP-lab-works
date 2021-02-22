#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

typedef std::vector<std::vector< char>> Space;

struct Args
{
    std::string inputFile;
    std::optional<std::string> outputFile;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cout << "Invalid count parameters\n";
        std::cout << "Usage Live.exe <input file> [output file]\n";
        return std::nullopt;
    }

    Args args;

    if (argc == 2)
    {
        args.inputFile = argv[1];
        args.outputFile = std::nullopt;
    }
    else
    {
        args.inputFile = argv[1];
        args.outputFile = argv[2];
    }

    return args;
}

void ShowSpace(const Space &space)
{
    for (int i = 0; i < space.size(); i++)
    {
        for (int j = 0; j < space.size(); j++)
        {
            std::cout << space[i][j];
        }
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[])
{
    auto args = ParseArgs(argc, argv);
    std::string temp;

    if (!args)
    {
        return 1;
    }

    std::ifstream input(args->inputFile);
    if (!input.is_open())
    {
        std::cout << "Failed to open " << args->inputFile << " for reading\n";
        return 1;
    }
 

    int rows = 0;
    while (std::getline(input, temp))
    {
        rows++;
    }
    std::vector<std::vector<char>> space(rows);
    input.seekg(0);

    int step = 0;
    while (std::getline(input,temp))
    {
        std::vector<char> row;
        for (int i = 0; i < temp.length(); i++)
        {
            row[i] = temp[i];
        }
        space[step] = row;
        step++;
    }

    std::cout << "\n\n";
    ShowSpace(space);
}
