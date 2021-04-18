#include "PrimeNumbers.h"
#include <Windows.h>
#include <string>

using namespace std;

const string INVALID_SYNTAX = "Неправильный ввод.";
const string USAGE = "Использовать:  GeneratePrimeNumbers.cpp <upperBound>";
const string PRIME_COUNT_UP_TO = "Количество простых чисел в диапозоне до";
const string WRITE_OR_NOT = "Распечатать числа? Д /д - да";

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	if (argc != 2)
	{
		cout << INVALID_SYNTAX << endl;
		cout << USAGE << endl;
		system("pause");
		return 1;
	}
	int upperBound = stoi(argv[1]);
	auto primeNumbers = GeneratePrimeNumbersSet(upperBound);

	cout << PRIME_COUNT_UP_TO << " " << upperBound << " = " << GetNumbersCount(primeNumbers) << endl;

	cout << WRITE_OR_NOT << endl;
	char answer;
	cin >> answer;
	if (answer == 'Д' || answer == 'д')
	{
		PrintPrimeNumbersSet(primeNumbers);
		system("pause");
	}

	return 0;
}
