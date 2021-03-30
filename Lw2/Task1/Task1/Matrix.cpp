#include "Matrix.h"

std::optional<std::vector<double>> ReadNumbers(const std::string& fileName)
{
	// переделал на copy
	std::vector<double> numbers;
	std::ifstream file(fileName);

	if (file.is_open())
	{
		copy(std::istream_iterator<double>(file), std::istream_iterator<double>(), back_inserter(numbers));
		return numbers;
	}
	else
	{
		std::cout << "Не удалось открыть " << fileName << " для чтения" << std::endl;;
		return std::nullopt;
	}
}

void CalculateNumbers(std::vector<double>& numbers)
{
	// переделал на transform
	if (numbers.empty()) return;
	auto minElRef = std::min_element(numbers.begin(), numbers.end());
	double min = *minElRef;
	std::transform(numbers.begin(), numbers.end(), numbers.begin(), [&](double n) {return n * min; });
}

std::string ShowNumbers(std::vector<double>& numbers)
{
	sort(numbers.begin(), numbers.end());
	std::ostringstream streamObj;
	streamObj << std::fixed << std::setprecision(3);
	for (unsigned i = 0; i < numbers.size(); i++)
	{
		if (i != 0)
		{
			streamObj << " ";
		}
		streamObj << numbers[i];
	}

	return streamObj.str();
}

std::string MakeCalculation(const std::string& fileName)
{
	auto numbers = ReadNumbers(fileName);

	if (!numbers || numbers && numbers.value().empty())
	{
		return "";
	}
	CalculateNumbers(numbers.value());
	std::string result = ShowNumbers(numbers.value());
	return result;
}