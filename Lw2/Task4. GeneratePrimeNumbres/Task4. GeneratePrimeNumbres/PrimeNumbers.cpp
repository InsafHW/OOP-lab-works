#include "PrimeNumbers.h"

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
	{
		return set<int> {};
	}
	if (upperBound == 2)
	{
		return set<int> {2};
	}

	set<int> primeNumbers;
	vector<bool> numbers(upperBound, true);

	for (int i = 2; i * i <= upperBound; i++)
	{
		if (numbers[i])
		{
			for (int j = i * i; j < upperBound; j += i)
			{
				numbers[j] = false;
			}
		}
	}

	for (int i = 2; i < upperBound; i++)
	{
		if (numbers[i])
		{
			primeNumbers.insert(i);
		}
	}

	return primeNumbers;
}

void PrintPrimeNumbersSet(set<int>& primes)
{
	for (auto it = primes.begin(); it != primes.end(); it++)
	{
		cout << *it << endl;
	}
}

int GetNumbersCount(set<int>& primes)
{
	int count = 0;
	for (auto it = primes.begin(); it != primes.end(); it++)
	{
		count++;
	}
	return count;
}