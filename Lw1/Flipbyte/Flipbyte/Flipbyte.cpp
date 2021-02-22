#include <iostream>
#include <fstream>
#include <string>
#include <optional>


bool HasLetter(const std::string &str)
{
	for (int i = 0; i < str.length(); i++) 
	{
		if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z')
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

	if (argv[1][0] == '0' || HasLetter(argv[1]))
	{
		std::cout << "Invalid input. Must be decimal\n";
		return std::nullopt;
	}

	if (std::stoi(argv[1]) > 255 || std::stoi(argv[1]) < 0)
	{
		std::cout << std::stoi(argv[1]) << " is out of range\n";
		std::cout << "Usage: 0 <= <input byte> <= 255\n";
		return std::nullopt;
	}
	
	return std::stoi(argv[1]);
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
	auto x = ParseArgs(argc, argv);

	if (!x)
	{
		return 1;
	}

	int reversedX = ReverseBits(x.value());
	std::cout << reversedX << "\n";
}