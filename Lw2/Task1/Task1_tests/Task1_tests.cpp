#include <iostream>
#define CATCH_CONFIG_MAIN
#include <Windows.h>
#include "../../../../catch2/catch.hpp"

#include "../Task1/Matrix.h"


using namespace std;

// проверяем ReadNumbers

void WriteInFile(const string& str, const string& fileName = "input.txt")
{
	ofstream out(fileName);
	out << str;
	out.close();
}

SCENARIO("Считывание с несущ. файла")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Считывание с несущ. файла вернет nullopt" << endl;
	auto y = ReadNumbers("несуществфайл.txt");
	REQUIRE(!y);
}

SCENARIO("Считываем пустую строку")
{
	WriteInFile("");
	cout << "Считывание пустой строке вернет пустой вектор" << endl;
	auto x = ReadNumbers("input.txt");
	REQUIRE(x);
	REQUIRE(x.value().empty());
}

SCENARIO("Считывание только положительных чисел")
{
	WriteInFile("1 45 34");
	cout << "Считывание только положительных чисел" << endl;
	vector<double> x{ 1.000, 45.000, 34.000 };
	auto y = ReadNumbers("input.txt");
	REQUIRE(y);
	REQUIRE(x == y.value());
}

SCENARIO("Считывание только отрицательных чисел")
{
	WriteInFile("-1 -45 -34");
	cout << "Считывание только отрицательных чисел" << endl;
	vector<double> x{ -1.000, -45.000, -34.000 };
	auto y = ReadNumbers("input.txt");
	REQUIRE(y);
	REQUIRE(x == y.value());
}

SCENARIO("Считывание смешнных чисел")
{
	WriteInFile("-1 45 -34 4 0");
	cout << "Считывание смешанных чисел" << endl;
	vector<double> x{ -1.000, 45.000, -34.000, 4.000, 0.000 };
	auto y = ReadNumbers("input.txt");
	REQUIRE(x == y);
}

// Проверяем CalculateNumbers

SCENARIO("Вычисления с пустым вектром останется пустым вектором")
{
	cout << "Вычисления с пустым вектром останется пустым вектором" << endl;
	vector<double> x;
	CalculateNumbers(x);
	REQUIRE(x.empty());
}


SCENARIO("Вычесление вектора только с одним числом, вернет вектор с квадратом его элемента")
{
	cout << "Вычесление вектора только с одним числом, вернет вектор с квадратом его элемента" << endl;
	vector<double> x = { -5 };
	CalculateNumbers(x);
	REQUIRE(x.size() == 1);
	REQUIRE(x[0] == 25.000);
}

SCENARIO("Вычесление вектора, элементы которого положительны и у кот. есть эле-т 0, обнулит все элементы")
{
	cout << "Вычесление вектора, элементы которого положительны и у кот. есть эле-т 0, обнулит все элементы" << endl;
	vector<double> x = { 5, 102.343, 323, 9192, 0, 24, 42 };
	CalculateNumbers(x);
	REQUIRE(x.size() == 7);
	for (unsigned i = 0; i < x.size(); i++)
	{
		REQUIRE(x[i] == 0.000);
	}
}

SCENARIO("Вычесление вектора, минимальный эл-т которого 1, вернет тот же вектор")
{
	cout << "Вычесление вектора, минимальный эл-т которого 1, вернет тот же вектор" << endl;
	vector<double> x = { 5, 102.343, 323, 9192, 1, 24, 42 };
	vector<double> y = { 5, 102.343, 323, 9192, 1, 24, 42 };
	CalculateNumbers(x);
	REQUIRE(x == y);
}

SCENARIO("Вычесление вектора только с отрицательными числами")
{
	cout << "Вычесление вектора только с отрицательными числами" << endl;
	vector<double> x = { -3, -5, -8 };
	vector<double> y = { 24, 40, 64 };
	CalculateNumbers(x);
	REQUIRE(x == y);
}

SCENARIO("Вычесление вектора только с положительными числами")
{
	cout << "Вычесление вектора только с положительными числами" << endl;
	vector<double> x = { 3, 5, 8 };
	vector<double> y = { 9, 15, 24 };
	CalculateNumbers(x);
	REQUIRE(x == y);
}

SCENARIO("Вычесление вектора со смешанными числами")
{
	cout << "Вычесление вектора со смешанными числами" << endl;
	vector<double> x = { 3, -5, 8 };
	vector<double> y = { -15, 25, -40 };
	CalculateNumbers(x);
	REQUIRE(x == y);
}

// Проверка ShowNumbers
SCENARIO("Показ пустого вектора вернет пустую строку")
{
	cout << "Показ пустого вектора вернет пустую строку" << endl;
	vector<double> x = { };
	REQUIRE(ShowNumbers(x) == "");
}

SCENARIO("Показ вектора только с полож. числами, отсортированный по возрастанию вернет строку с таким же порядком")
{
	cout << "Показ вектора только с полож. числами, отсортированный по возрастанию вернет строку с таким же порядком" << endl;
	vector<double> x = { 1, 2, 3, 4 };
	REQUIRE(ShowNumbers(x) == "1.000 2.000 3.000 4.000");
}

SCENARIO("Показ вектора только с полож. числами, отсортированный по убыванию вернет строку в обратном порядком")
{
	cout << "Показ вектора только с полож. числами, отсортированный по убыванию вернет строку в обратном порядком" << endl;
	vector<double> x = { 4, 3, 2, 1 };
	REQUIRE(ShowNumbers(x) == "1.000 2.000 3.000 4.000");
}

SCENARIO("Показ вектора только с отр. числами, отсортированный по возрастанию вернет строку с таким же порядком")
{
	cout << "Показ вектора только с отр. числами, отсортированный по возрастанию вернет строку с таким же порядком" << endl;
	vector<double> x = { -4, -3, -2, -1 };
	REQUIRE(ShowNumbers(x) == "-4.000 -3.000 -2.000 -1.000");
}

SCENARIO("Показ вектора только с отр. числами, отсортированный по убыванию вернет строку с обратным порядком")
{
	cout << "Показ вектора только с отр. числами, отсортированный по убыванию вернет строку с обратным порядком" << endl;
	vector<double> x = { -1, -2, -3, -4 };
	REQUIRE(ShowNumbers(x) == "-4.000 -3.000 -2.000 -1.000");
}

SCENARIO("Показ вектора со смешанными числами вернет упорядоченную строку")
{
	cout << "Показ вектора со смешанными числами вернет упорядоченную строку" << endl;
	vector<double> x = { -1, 2, 535, -4392, 12 };
	REQUIRE(ShowNumbers(x) == "-4392.000 -1.000 2.000 12.000 535.000");
}

// Проверяем MakeCalculation

SCENARIO("Обработка несущ. файла вернет пустую строк")
{
	cout << "Обработка несущ. файла вернет пустую строк" << endl;
	auto x = MakeCalculation("несущфайл.txt");
	REQUIRE(x.empty());
}

SCENARIO("Обработка пустой строки вернет пустую строку")
{
	WriteInFile("");
	cout << "Обработка пустой строки вернет пустую строку" << endl;
	auto x = MakeCalculation("input.txt");
	REQUIRE(x.empty());
}

SCENARIO("Обработка только положительных чисел")
{
	WriteInFile("7 4 3");
	cout << "Обработка только положительных чисел" << endl;
	REQUIRE(MakeCalculation("input.txt") == "9.000 12.000 21.000");
}

SCENARIO("Обработка только отрицательных чисел")
{
	WriteInFile("-7 -4 -3");
	cout << "Обработка только отрицательных чисел" << endl;
	REQUIRE(MakeCalculation("input.txt") == "21.000 28.000 49.000");
}

SCENARIO("Обработка смешанных чисел")
{
	WriteInFile("-7 -4 3 1");
	cout << "Обработка смешанных чисел" << endl;
	REQUIRE(MakeCalculation("input.txt") == "-21.000 -7.000 28.000 49.000");
}

SCENARIO("Обработка чисел, где все числа полож. и мин равен 1 вернет строку с теми же эелементами")
{
	WriteInFile("1 2 3 4 5");
	cout << "Обработка чисел, где все числа полож. и мин равен 1 вернет строку с теми же эелементами" << endl;
	REQUIRE(MakeCalculation("input.txt") == "1.000 2.000 3.000 4.000 5.000");
}

SCENARIO("Обработка положительных чисел, в кот. есть 0, вернет строку, где все числа станут 0")
{
	WriteInFile("1 2 3 4 0 5");
	cout << "Обработка положительных чисел, в кот. есть 0, вернет строку, где все числа станут 0" << endl;
	REQUIRE(MakeCalculation("input.txt") == "0.000 0.000 0.000 0.000 0.000 0.000");
}