#pragma once
#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimeNumbersSet(set<int>& primes);
int GetNumbersCount(set<int>& primes);