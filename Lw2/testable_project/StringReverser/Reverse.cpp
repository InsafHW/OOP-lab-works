#include "Reverse.h"
#include <algorithm>
#include <iostream>

std::string Reverse(const std::string &str)
{
	std::string reversed;
	reversed.reserve(str.length());

	std::reverse_copy(str.begin(), str.end(), std::back_inserter(reversed));
	return reversed;
}

void ReverseLines(std::istream& input, std::ostream& output)
{
	std::string line;
	bool isFirstLine = true;
	while (std::getline(input, line))
	{
		if (!isFirstLine)
		{
			output << "\n";
		}
		output << Reverse(line);
		isFirstLine = false;
	}
}
