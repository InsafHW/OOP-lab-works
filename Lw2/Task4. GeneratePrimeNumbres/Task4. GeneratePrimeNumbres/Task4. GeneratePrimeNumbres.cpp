#include "PrimeNumbers.h"
#include <Windows.h>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	if (argc != 2)
	{
		cout << "Invalid syntax." << endl;
		cout << "Usage GeneratePrimeNumbers.cpp <upperBound>" << endl;
		system("pause");
		return 1;
	}
	int upperBound = stoi(argv[1]);
	auto primeNumbers = GeneratePrimeNumbersSet(upperBound);

	cout << "Количество простых чисел в диапозоне до " << upperBound << " = " << GetNumbersCount(primeNumbers) << endl;

	cout << "Распечатать числа? Y /y - да" << endl;
	char answer;
	cin >> answer;
	if (answer == 'Y' || answer == 'y')
	{
		PrintPrimeNumbersSet(primeNumbers);
		system("pause");
	}

	return 0;
}
