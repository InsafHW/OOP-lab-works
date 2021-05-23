#include <iostream>
#include <sstream>
#include <Windows.h>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../Task7/FindMaxEx.h"
#include "../Task7/Sportsman.h"

const int DEFAULT_INT_VALUE = 0;
const double DEFAULT_DOUBLE_VALUE = 0.0;
const string DEFAULT_STRING_VALUE = "";

SCENARIO("Максимальный среди int")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Если вектор int пустой, функция вернет false и значения max, не изменится" << endl;
	vector<int> empty;
	int maxForEmpty = DEFAULT_INT_VALUE;
	REQUIRE(FindMaxEx(empty, maxForEmpty, [](int x1, int x2) {return x1 < x2; }) == false);
	REQUIRE(maxForEmpty == DEFAULT_INT_VALUE);

	cout << "Для вектора int только с одним элементом, функция вернет true и значение max будет тем самым элементом" << endl;
	vector<int> x1{ 100 };
	int maxForX1 = DEFAULT_INT_VALUE;
	REQUIRE(FindMaxEx(x1, maxForX1, [](int x1, int x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX1 == 100);

	cout << "Для непустого вектора int только с отрицательными числами, функция вернет true и значение max будет максимальным из массива" << endl;
	vector<int> x2{ -1, -3 ,-82, -3, -214, -3, -100 };
	int maxForX2 = DEFAULT_INT_VALUE;
	REQUIRE(FindMaxEx(x2, maxForX2, [](int x1, int x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX2 == -1);

	cout << "Для непустого вектора int только с положительными числами, функция вернет true и значение max будет максимальным из массива" << endl;
	vector<int> x3{ 1, 3, 82, 3, 214, 3, 100 };
	int maxForX3 = DEFAULT_INT_VALUE;
	REQUIRE(FindMaxEx(x3, maxForX3, [](int x1, int x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX3 == 214);

	cout << "Для непустого вектора int только со смешанными числами, функция вернет true и значение max будет максимальным из массива" << endl;
	vector<int> x4{ 1, -32, 23, 0, -23, 129 };
	int maxForX4 = DEFAULT_INT_VALUE;
	REQUIRE(FindMaxEx(x4, maxForX4, [](int x1, int x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX4 == 129);
}

SCENARIO("Максимальный среди double")
{
	cout << "Если вектор double пустой, функция вернет false и значения max, не изменится" << endl;
	vector<double> empty;
	double maxForEmpty = DEFAULT_DOUBLE_VALUE;
	REQUIRE(FindMaxEx(empty, maxForEmpty, [](double x1, double x2) {return x1 < x2; }) == false);
	REQUIRE(maxForEmpty == DEFAULT_DOUBLE_VALUE);

	cout << "Для вектора double только с одним элементом, функция вернет true и значение max будет тем самым элементом" << endl;
	vector<double> x1{ 100.0 };
	double maxForX1 = DEFAULT_DOUBLE_VALUE;
	REQUIRE(FindMaxEx(x1, maxForX1, [](double x1, double x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX1 == 100.0);

	cout << "Для непустого вектора duble только с отрицательными числами, функция вернет true и значение max будет максимальным из массива" << endl;
	vector<double> x2{ -1.0, -3.2 ,-82.45, -3.3, -214.124, -3.42, -100.4 };
	double maxForX2 = DEFAULT_DOUBLE_VALUE;
	REQUIRE(FindMaxEx(x2, maxForX2, [](double x1, double x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX2 == -1.0);

	cout << "Для непустого вектора double только с положительными числами, функция вернет true и значение max будет максимальным из массива" << endl;
	vector<double> x3{ 1.0, 3.23, 82.4, 3.13, 214.43, 3.45, 100.66 };
	double maxForX3 = DEFAULT_DOUBLE_VALUE;
	REQUIRE(FindMaxEx(x3, maxForX3, [](double x1, double x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX3 == 214.43);

	cout << "Для непустого вектора double только со смешанными числами, функция вернет true и значение max будет максимальным из массива" << endl;
	vector<double> x4{ 1.00, -32.32, 23.5, 0.54, -23.21, 129.43 };
	double maxForX4 = DEFAULT_DOUBLE_VALUE;
	REQUIRE(FindMaxEx(x4, maxForX4, [](double x1, double x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX4 == 129.43);
}

SCENARIO("Максимальный среди string")
{
	cout << "Если вектор string пустой, функция вернет false и значения max, не изменится" << endl;
	vector<string> empty;
	string maxForEmpty = DEFAULT_STRING_VALUE;
	REQUIRE(FindMaxEx(empty, maxForEmpty, [](string x1, string x2) {return x1 < x2; }) == false);
	REQUIRE(maxForEmpty == DEFAULT_STRING_VALUE);

	cout << "Для вектора string только с одним элементом, функция вернет true и значение max будет тем самым элементом" << endl;
	vector<string> x1{ "test" };
	string maxForX1 = DEFAULT_STRING_VALUE;
	REQUIRE(FindMaxEx(x1, maxForX1, [](string x1, string x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX1 == "test");

	cout << "Для непустого вектора string, функция вернет true и значение max будет максимальным из элементом по лексиграфическому правилу" << endl;
	vector<string> x2{ "Aport", "Apricot" , "test" };
	string maxForX2 = DEFAULT_STRING_VALUE;
	REQUIRE(FindMaxEx(x2, maxForX2, [](string x1, string x2) {return x1 < x2; }) == true);
	REQUIRE(maxForX2 == "test");
}

SCENARIO("Максимальный среди спортсменов")
{
	vector<Sportsman> people;
	people.push_back(Sportsman("Ivan Egorov", 170, 56));
	people.push_back(Sportsman("Andrey Okunev", 162, 76));
	people.push_back(Sportsman("Denis Aktuganov", 180, 100));
	people.push_back(Sportsman("Danila Lipatnikov", 175, 112));
	people.push_back(Sportsman("Leha Sadovin", 150, 59));

	Sportsman max;

	FindMaxEx(people, max, [](Sportsman s1, Sportsman s2) {return s1.GetHeight() < s2.GetHeight(); });
	REQUIRE(max.GetFIO() == "Denis Aktuganov");
	FindMaxEx(people, max, [](Sportsman s1, Sportsman s2) {return s1.GetWeight() < s2.GetWeight(); });
	REQUIRE(max.GetFIO() == "Danila Lipatnikov");
}