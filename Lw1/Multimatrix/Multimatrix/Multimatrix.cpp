#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <optional>
#include <cmath>
#include <iomanip>

typedef std::array<std::array<double, 3>, 3> matrix;

struct Args
{
    std::string matrixFile1;
    std::string matrixFile2;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: Multimatrix.exe <matrix file1> <matrix file2>\n";
        return std::nullopt;
    }
    Args args;
    args.matrixFile1 = argv[1];
    args.matrixFile2 = argv[2];
    return args;
}


matrix ReadMatrix(std::ifstream& file)
{
    int outterStep = 0;
    std::string temp;
    matrix matrix = { 0 };

    while (getline(file, temp))
    {
        int innerStep = 0;
        std::string digit;
        for (int i = 0; i < temp.length(); i++)
        {
            if (temp[i] != ' ')
            {
                digit += temp[i];
                continue;
            }
            matrix[outterStep][innerStep] = stoi(digit);
            innerStep++;
            digit = "";
        }
        matrix[outterStep][innerStep] = stoi(digit);
        outterStep++;
    }

    return matrix;
}

std::optional<matrix> ReadMatrixFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Failed to open '" << &file << "' for reading\n";
        return std::nullopt;
    }
    matrix matrix = ReadMatrix(file);
    return matrix;
}

void ShowMatrix(matrix matrix)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << std::fixed << std::setprecision(3) << matrix[i][j];
            if (j != 2) std::cout << " ";
        }
       
        if (i != 2) std::cout << std::endl;
    }
}

matrix MultiplyMatrix(const matrix& m1, const matrix& m2)
{
    matrix resultMatrix;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            double result = 0;
            for (int k = 0; k < 3; k++)
            {
                result += m1[i][k] * m2[k][j];
            }

            resultMatrix[i][j] = result;
        }
    }

    return resultMatrix;
}


int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }
    matrix resultMatrix;
    
    auto matrix1 = ReadMatrixFromFile(args->matrixFile1);
    auto matrix2 = ReadMatrixFromFile(args->matrixFile2);

    if (!matrix1 || !matrix2)
    {
        return 1;
    }

    resultMatrix = MultiplyMatrix(*matrix1, *matrix2);
    ShowMatrix(resultMatrix);
    return 0;
}