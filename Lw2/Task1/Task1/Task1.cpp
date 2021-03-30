#include <iostream>
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
		std::ofstream out("input.txt");
		out << line;
		out.close();
		std::cout << MakeCalculation("input.txt") << std::endl;
	}
	return 0;
}
