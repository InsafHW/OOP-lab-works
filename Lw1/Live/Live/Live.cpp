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

// проверить размер строки в инпуте

void ShowSpace(const Space& space, std::ostream& outputFile) // объединить функции
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

bool ReadGeneration(std::istream& input, Space& firstGeneration, Space& secondGeneration)
{
    std::string temp;
    int step = 0;
    while (std::getline(input, temp))
    {
        std::vector<char> row;
        for (unsigned i = 0; i < temp.length(); i++)
        {
            row.push_back(temp[i]);
        }
        if (step > 0 && firstGeneration[step - 1].size() != row.size())
        {
            std::cout << "The row's length is not similar to previous\n";
            return false;
        }
        firstGeneration.push_back(row);
        secondGeneration.push_back(row);
        step++;
    }
    return true;
}

int GetNeighbourCount(const Space &s, int Y, int X) // упростить
{
    int neighbourCount = 0;
    bool canGoTop = Y - 1 >= 0;
    bool canGoLeft = X - 1 >= 0;
    bool canGoRight = X + 1 < s[0].size();
    bool canGoBottom = Y + 1 < s.size();

    if (canGoLeft && s[Y][X - 1] == '#') // слева от него
    {
        neighbourCount++;
    }
    if (canGoRight && s[Y][X + 1] == '#') // справа от него
    {
        neighbourCount++;
    }
    if (canGoTop && s[Y - 1][X] == '#') // сверху от него
    {
        neighbourCount++;
    }
    if (canGoBottom && s[Y + 1][X] == '#') // снизу от него
    {
        neighbourCount++;
    }
    if (canGoTop && canGoLeft && s[Y - 1][X - 1] == '#') // слева верхняя диагональ от него
    {
        neighbourCount++;
    }
    if (canGoTop && canGoRight && s[Y - 1][X + 1] == '#') // справа верхняя диагональ от него
    {
        neighbourCount++;
    }
    if (canGoBottom && canGoLeft && s[Y + 1][X - 1] == '#') // слева нижняя диагональ от него
    {
        neighbourCount++;
    }
    if (canGoBottom && canGoRight && s[Y + 1][X + 1] == '#') // справа нижняя диагональ от него
    {
        neighbourCount++;
    }

    return neighbourCount;
}

void ExploreNewGeneration(const Space& oldGeneration, Space& newGeneration)
{
    for (unsigned i = 1; i < oldGeneration.size() - 1; i++) // выделить циклы в функцию
    {
        for (unsigned j = 1; j < oldGeneration[0].size() - 1; j++)
        {
            int neighbourCount = GetNeighbourCount(oldGeneration, i, j);

            if (neighbourCount < 2 || neighbourCount > 3) // клетка умирает
            {
                newGeneration[i][j] = ' ';
            }
            if (oldGeneration[i][j] == ' ' && neighbourCount == 3) // клетка оживает
            {
                newGeneration[i][j] = '#';
            }
        }
    }
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
    
    Space firstGeneration;
    Space secondGeneration;
    if (!ReadGeneration(input, firstGeneration, secondGeneration))
    {
        return 1;
    }
    ExploreNewGeneration(firstGeneration, secondGeneration);

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
        ShowSpace(secondGeneration, std::cout);
    }

    return 0;
}