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

    args.inputFile = argv[1];
    args.outputFile = std::nullopt;

    if (argc != 2)
    {
        args.outputFile = argv[2];
    }
   
    return args;
}

void ShowSpace(const Space& space, std::ofstream& outputFile)
{
    for (int i = 0; i < space.size(); i++)
    {
        for (int j = 0; j < space[i].size(); j++)
        {
            outputFile << space[i][j];
        }
        outputFile << std::endl;
    }
}

void ShowSpace(const Space &space)
{
    for (int i = 0; i < space.size(); i++)
    {
        for (int j = 0; j < space[i].size(); j++)
        {
            std::cout << space[i][j];
        }
        std::cout << std::endl;
    }
}

int GetNeighbourCount(const Space &s, int Y, int X)
{
    int neighbourCount = 0;
    if (Y - 1 >= 0 && s[Y][X - 1] == '#') // слева от него
    {
        neighbourCount++;
    }
    if (X + 1 < s[0].size() && s[Y][X + 1] == '#') // справа от него
    {
        neighbourCount++;
    }
    if (Y - 1 >= 0 && s[Y - 1][X] == '#') // сверху от него
    {
        neighbourCount++;
    }
    if (Y + 1 < s.size() && s[Y + 1][X] == '#') // снизу от него
    {
        neighbourCount++;
    }
    if (Y - 1 >= 0 && s[Y - 1][X - 1] == '#') // слева верхняя диагональ от него
    {
        neighbourCount++;
    }
    if (Y - 1 >= 0 && X + 1 < s[0].size() && s[Y - 1][X + 1] == '#') // справа верхняя диагональ от него
    {
        neighbourCount++;
    }
    if (Y + 1 < s.size() && X - 1 < s[0].size() && s[Y + 1][X - 1] == '#') // слева нижняя диагональ от него
    {
        neighbourCount++;
    }
    if (Y + 1 < s.size() && X + 1 < s[0].size() && s[Y + 1][X + 1] == '#') // справа нижняя диагональ от него
    {
        neighbourCount++;
    }

    return neighbourCount;
}

int main(int argc, char * argv[])
{
    auto args = ParseArgs(argc, argv);

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
    
    std::string temp;
    Space firstGeneration;
    Space secondGeneration;
    while (std::getline(input, temp))
    {
        std::vector<char> row;
        for (unsigned i = 0; i < temp.length(); i++)
        {
            row.push_back(temp[i]);
        }
        firstGeneration.push_back(row);
        secondGeneration.push_back(row);
    }

    for (unsigned i = 1; i < firstGeneration.size() - 1; i++)
    {
        for (unsigned j = 1; j < firstGeneration[0].size() - 1; j++)
        {
            int neighbourCount = GetNeighbourCount(firstGeneration, i, j);

            if (neighbourCount < 2 || neighbourCount > 3) // клетка умирает
            {
                secondGeneration[i][j] = ' ';
            }
            if (firstGeneration[i][j] == ' ' && neighbourCount == 3) // клетка оживает
            {
                secondGeneration[i][j] = '#';
            }
        }
    }

    if (args->outputFile)
    {
        std::ofstream output(args->outputFile.value());
        if (!output.is_open())
        {
            std::cout << "Can't open " << args->outputFile.value() << " for writing\n";
            return 1;
        }
        ShowSpace(secondGeneration, output);
    }
    else
    {
        ShowSpace(secondGeneration);
    }

    return 0;
}
