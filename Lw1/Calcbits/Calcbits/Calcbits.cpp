#include <iostream>
#include <string>


int toBinary(int number)
{
    int b, c = 0;
    for(int i = 0; number > 0; i++)
    {
        b = number % 2;
        number = (number - b) / 2;
        c += b * pow(10, i);

    }
    return c;
}

int main(int argc, char* argv[])
{
    if (argc < 1) return 1;
    int number = atoi(argv[1]);
    int binaryNumber = toBinary(number);
    std::cout << binaryNumber;
    std::string binaryNumStr = std::to_string(binaryNumber);
    int count = 0;
    for (int i = 0; i < binaryNumStr.length(); i++)
    {
        if (binaryNumStr[i] == '1')
        {
            count++;
        }
    }
    std::cout << "The amount of 1: " << count;
}
