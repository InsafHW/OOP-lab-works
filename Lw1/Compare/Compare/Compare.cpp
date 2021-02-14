#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <optional>

struct Args
{
    std::string firstFileName;
    std::string secondFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: Compare.exe <filename1> <filename2>\n";
        return std::nullopt;
    }
    Args args;
    args.firstFileName = argv[1];
	args.secondFileName = argv[2];
	return args;
}

void ReadFile(std::ifstream& file, std::vector<std::string>& fileLines)
{
    std::string temp;
    while (getline(file, temp))
    {
        fileLines.push_back(temp);
    }
}

void showDifferentLineMessage(int line)
{
    std::cout << "Files are different. Line number is " << line << std::endl;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    std::vector<std::string> firstFileLines;
    std::vector<std::string> secondFileLines;

    std::ifstream file1(args->firstFileName);
    if (!file1.is_open())
    {
        std::cout << "Failed to open '" << args->firstFileName << "' for reading\n";
        return 1;
    }

    std::ifstream file2(args->secondFileName);
    if (!file2.is_open())
    {
        std::cout << "Failed to open '" << args->secondFileName << "' for reading\n";
        return 1;
    }

    ReadFile(file1, firstFileLines);
    ReadFile(file2, secondFileLines);

    int firstFileLinesSize = firstFileLines.size();
    int secondFileLinesSize = secondFileLines.size();

    int maxSteps = firstFileLinesSize > secondFileLinesSize ? firstFileLinesSize : secondFileLinesSize;

    for (int i = 0; i < maxSteps; i++)
    {
        if (i >= firstFileLines.size() || i >= secondFileLines.size())
        {
            showDifferentLineMessage(i + 1);
            return 1;
        }

        int firstFileLineLength = firstFileLines[i].length();
        int secondFileLineLength = secondFileLines[i].length();
        int steps = firstFileLineLength > secondFileLineLength ? firstFileLineLength : secondFileLineLength;

        for (int j = 0; j < steps; j++)
        {
            if (j > firstFileLines[i].length() || j > secondFileLines[i].length())
            {
                showDifferentLineMessage(i + 1);
                return 1;
            }

            if (firstFileLines[i][j] != secondFileLines[i][j])
            {
                showDifferentLineMessage(i + 1);
                return 1;
            }
        }
    }

    std::cout << "Files are equal";
    return 0;
}
