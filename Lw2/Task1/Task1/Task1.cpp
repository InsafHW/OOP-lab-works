#include <iostream>
#include <string>
#include <vector>
#include "Matrix.h"

#include <Windows.h>

void SetRuEnc()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

int main()
{
	SetRuEnc();
	std::string line;
	while (getline(std::cin, line))
	{
		std::vector<double> numbers = ReadNumbers(line);
		if (numbers.empty())
		{
			std::cout << std::endl;
			return 1;
		}
		CalculateNumbers(numbers);
		ShowNumbers(numbers);
		std::cout << std::endl;
	}
	return 0;
}
