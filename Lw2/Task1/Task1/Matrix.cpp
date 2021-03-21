#include "Matrix.h"
#include <fstream>
#include <optional>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

std::vector<double> ReadNumbers(const std::string& str)
{
	std::string digit;
	std::vector<double> numbers;

	if (str.empty())
	{
		return numbers;
	}

	int error = std::find_if_not(str.begin(), str.end(), [](char c) { return c == ' ' || (c >= '0' && c <= '9'); }) != str.end();
	if (error)
	{
		std::cout << "Invalid input, expected only numbers\n";
		return numbers;
	}

	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i])
			if (str[i] == ' ')
			{
				if (stod(digit))
				{
					numbers.push_back(stod(digit) * 1.000);
				}
				digit = "";
				continue;
			}
		digit += str[i];
	}
	if (stod(digit))
	{
		numbers.push_back(stod(digit) * 1.000);
	}
	return numbers;
}


void CalculateNumbers(std::vector<double>& numbers)
{
	auto minElRef = std::min_element(numbers.begin(), numbers.end());
	double min = *minElRef;
	for (unsigned i = 0; i < numbers.size(); i++)
	{
		numbers[i] *= min;
	}
}

void ShowNumbers(std::vector<double>& numbers)
{
	sort(numbers.begin(), numbers.end());
	std::string result;
	for (unsigned i = 0; i < numbers.size(); i++)
	{
		if (i != 0)
		{
			std::cout << " ";
		}
		std::cout << std::fixed << std::setprecision(3) << numbers[i];
	}
}