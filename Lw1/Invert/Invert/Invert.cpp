#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <optional>
#include <cmath>
#include <vector>
#include <iomanip>

typedef std::array<std::array<double, 3>, 3> matrix;

std::optional<std::string> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: Multimatrix.exe <matrix file>\n";
        return std::nullopt;
    }
    std::string arg = argv[1];

    return arg;
}

std::vector<std::string> Split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
        {
            pos = str.length();
        }
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
        {
            tokens.push_back(token);
        }
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}


bool IsValidCharacter(const char & ch)
{
    return (ch == '.' || ch == '-' || (ch <= '9') && (ch >= '0'));
}

std::optional<matrix> ReadMatrix(std::istream& file)
{
    int row = 0;
    std::string matrixLine;
    matrix matrix = { 0 };

    while (getline(file, matrixLine))
    {
        if (Split(matrixLine, " ").size() < 3)
        {
            std::cout << "Matrix hax empty values\n";
            return std::nullopt;
        }
        int column = 0;
        std::string digit;
        for (unsigned i = 0; i < matrixLine.length(); i++)
        {
            if (matrixLine[i] != ' ')
            {
                if (!IsValidCharacter(matrixLine[i]))
                {
                    std::cout << "The file contains non-digit values\n";
                    return std::nullopt;
                }
                digit += matrixLine[i];
                continue;
            }
            matrix[row][column] = stoi(digit);
            column++;
            digit = "";
        }
        matrix[row][column] = stoi(digit);
        row++;
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
    auto matrix = ReadMatrix(file);
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

double GetDetermenant(const matrix &m)
{
    double determenant;
    determenant = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) + m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
    return determenant;
}

matrix GetAlgebraicExtension(const matrix& m)
{
    matrix algebraicExtension;

    algebraicExtension[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];;
    algebraicExtension[0][1] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);;
    algebraicExtension[0][2] = m[1][0] * m[2][1] - m[1][1] * m[2][0];;

    algebraicExtension[1][0] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);;
    algebraicExtension[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];;
    algebraicExtension[1][2] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);;

    algebraicExtension[2][0] = m[0][1] * m[1][2] - m[0][2] * m[1][1];;
    algebraicExtension[2][1] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);;
    algebraicExtension[2][2] = m[0][0] * m[1][1] - m[1][0] * m[0][1];;


    return algebraicExtension;
}

std::optional<matrix> InverseMatrix(const matrix& m)
{
    matrix resultMatrix;
    double det = GetDetermenant(m);

    if (det == 0)
    {
        std::cout << "The determenant is 0\n";
        return std::nullopt;
    }

    matrix algebraicExtension = GetAlgebraicExtension(m);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            resultMatrix[j][i] = (1 / det) * algebraicExtension[i][j];
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

    auto matrix = ReadMatrixFromFile(*args);

    if (!matrix)
    {
        return 1;
    }

    auto resultMatrix = InverseMatrix(*matrix);

    if (!resultMatrix)
    {
        return 1;
    }

    ShowMatrix(*resultMatrix);
    return 0;
}