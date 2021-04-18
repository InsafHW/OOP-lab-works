#include "Matrix.h"
#include <string>

const string CANNOT_OPEN = "Не удалось открыть";
const string FOR_READING = "для чтения";

optional<vector<double>> ReadNumbers(const string& fileName)
{
	// переделал на copy
	vector<double> numbers;
	ifstream file(fileName);

	if (!file.is_open())
	{
		cout << CANNOT_OPEN << " " << fileName << " " << FOR_READING << endl;;
		return nullopt;
	}

	copy(istream_iterator<double>(file), istream_iterator<double>(), back_inserter(numbers));
	return numbers;

}

void CalculateNumbers(vector<double>& numbers)
{
	// переделал на transform
	if (numbers.empty()) return;
	auto minElRef = min_element(numbers.begin(), numbers.end());
	double min = *minElRef;
	transform(numbers.begin(), numbers.end(), numbers.begin(), [&](double n) {return n * min; });
}

string ShowNumbers(vector<double>& numbers)
{
	sort(numbers.begin(), numbers.end());
	ostringstream streamObj;
	streamObj << fixed << setprecision(3);
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

string MakeCalculation(const string& fileName)
{
	auto numbers = ReadNumbers(fileName);

	if (!numbers || numbers && numbers.value().empty())
	{
		return "";
	}
	CalculateNumbers(numbers.value());
	string result = ShowNumbers(numbers.value());
	return result;
}