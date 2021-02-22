#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <vector>

enum class Mode
{
    Crypt, Decrypt
};

struct Args
{
    Mode mode;
    std::string inputFile;
    std::string outputFile;
    int key;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: Crypt.exe <crypt/decrypt> <input file> <output file> <key>\n";
        return std::nullopt;
    }

    std::string mode = argv[1];

    if (mode != "crypt" && mode != "decrypt")
    {
        std::cout << "Invalid mode. Must be either <crypt> or <decrypt>\n";
        return std::nullopt;
    }

    if (argv[4][0] == '0')
    {
        std::cout << "Key must be decimal\n";
        return std::nullopt;
    }

    Args args;
    args.mode = mode == "crypt" ? Mode::Crypt : Mode::Decrypt;
    args.inputFile = argv[2];
    args.outputFile = argv[3];
    args.key = std::stoi(argv[4]);

    return args;
}

std::string to_binary_string(int n)
{
    std::string result;
    do
    {
        result += ('0' + (n % 2));
        n = n / 2;
    } while (n > 0);

    std::string reversedRes;
    for (int i = result.length() -1; i > 0; i--)
    {
        reversedRes += result[i];
    }
    return reversedRes;
}

int ShuffleBits(int b)
{
    b = (b & 0b10000000) >> 2;
    b = (b & 0b01100000) >> 5;
    b = (b & 0b00011000) << 3;
    b = (b & 0b00000111) << 2;

    return b;
}

void Crypt(std::string& str, int key)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = ShuffleBits(str[i]);
        str[i] = str[i] ^ key;
    }
}

int UnshuffleBits(int b)
{
    b = (b & 0b10000000) << 2;
    b = (b & 0b01100000) << 5;
    b = (b & 0b00011000) >> 3;
    b = (b & 0b00000111) >> 2;

    return b;
}

void Decrypt(std::string& str, int key)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = UnshuffleBits(str[i]);
        str[i] = str[i] ^ key;
    }
}

void ShowString(std::string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        std::cout << str[i];
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    
    std::string msg = "Hello world!";
    ShowString(msg);

    Crypt(msg, args->key);
    ShowString(msg);

    Decrypt(msg, args->key);
    ShowString(msg);
    
}
