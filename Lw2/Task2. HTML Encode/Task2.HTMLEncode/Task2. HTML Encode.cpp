#include <iostream>
#include <string>
#include "Encode.h"

int main()
{
	std::string line;
	while (getline(std::cin, line))
	{
		std::cout << Encode(line) << "\n";
	}
}
