#include <iostream>
#include <fstream>
#include <string>
#include <optional>

bool IsValidInput(const std::string& str)
{
	if (str == "0")
	{
		return true;
	}

	for (int i = 0; i < str.length(); i++) 
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			return true;
		}
	}

	return false;
}


std::optional<int> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: Flipbyte.exe <input byte> \n";
		return std::nullopt;
	}

	if (!IsValidInput(argv[1]))
	{
		std::cout << "Invalid input. Must be decimal\n";
		return std::nullopt;
	}

	int number = std::stoi(argv[1]);
	if (number > 255 || number < 0)
	{
		std::cout << number << " is out of range\n";
		std::cout << "Usage: 0 <= <input byte> <= 255\n";
		return std::nullopt;
	}
	
	return number;
}

int ReverseBits(int x)
{
	x = (x & 0x55) << 1 | (x & 0xAA) >> 1;
	x = (x & 0x33) << 2 | (x & 0xCC) >> 2;
	x = (x & 0x0F) << 4 | (x & 0xF0) >> 4;
	return x;
}

int main(int argc, char* argv[])
{
	auto byte = ParseArgs(argc, argv);

	if (!byte)
	{
		return 1;
	}

	int reversedByte = ReverseBits(byte.value());
	std::cout << reversedByte << "\n";
}