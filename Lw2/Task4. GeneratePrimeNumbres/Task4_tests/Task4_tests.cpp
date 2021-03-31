#include <iostream>
#include <Windows.h>
#include <ctime>

#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../Task4. GeneratePrimeNumbres/PrimeNumbers.h"

int const MILLISECONDS = 1000;

SCENARIO("Пустое множество, если число upperBound < 2")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Пустое множество, если число upperBound < 2" << endl;
	auto x = GeneratePrimeNumbersSet(-3);
	REQUIRE(x.empty());
}

SCENARIO("Нет простых чисел до 1")
{
	cout << "Нет простых чисел до 1" << endl;
	auto x = GeneratePrimeNumbersSet(1);
	REQUIRE(x.empty());
}

SCENARIO("Только одно простое число до 2 - это 2")
{
	cout << "Только одно простое число до 2 - это 2" << endl;
	auto x = GeneratePrimeNumbersSet(2);
	REQUIRE(x.size() == 1);
	REQUIRE(*x.begin() == 2);
}

SCENARIO("Проверка скорости работы при поиске простых чисел до 100 миллионов")
{
	cout << "Всего 5761455 простых чисел до 100 миллионов. ";
	unsigned int start_time = clock();
	auto x = GeneratePrimeNumbersSet(100000000);
	int count = GetNumbersCount(x);
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	REQUIRE(count == 5761455);
	cout << "Время работы программы: " << search_time / MILLISECONDS << "сек" << endl;
}