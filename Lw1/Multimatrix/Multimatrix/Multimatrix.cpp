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
    matrix matrix = {0};

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

void showMatrix(matrix matrix)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout <<  std::fixed << std::setprecision(3) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

matrix MatrixMultplier(matrix m1, matrix m2)
{
    matrix resultMatrix;
    double result = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                result += m1[i][k] * m2[k][j];
            }

            resultMatrix[i][j] = result;
            result = 0;
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

    matrix matrix1;
    matrix matrix2;
    matrix resultMatrix;

    std::ifstream firstFile(args->matrixFile1);
    if (!firstFile.is_open())
    {
        std::cout << "Failed to open '" << args->matrixFile1 << "' for reading\n";
        return 1;
    }

    std::ifstream secondFile(args->matrixFile2);
    if (!secondFile.is_open())
    {
        std::cout << "Failed to open '" << args->matrixFile2 << "' for reading\n";
        return 1;
    }

    matrix1 = ReadMatrix(firstFile);
    matrix2 = ReadMatrix(secondFile);

    resultMatrix = MatrixMultplier(matrix1, matrix2);
    showMatrix(resultMatrix);
    return 0;
}
