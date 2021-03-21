#include <iostream>
#include <string>
#include "Decode.h"


int main()
{
	std::string line;
	while (getline(std::cin, line))
	{
		std::cout << Decode(line) << "\n";
	}
}
