#include <iostream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../Task1.КомплексныеЧисла/CComplex.h";

SCENARIO("CComplex. Проверка базовых функций")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double real = -4;
	double image = 3;
	CComplex complex(real, image);
	cout << "Есть возможность посмотреть действительную часть" << endl;
	REQUIRE(complex.Re() == real);
	cout << "Есть возможность посмотреть мнимую часть" << endl;
	REQUIRE(complex.Im() == image);
	cout << "Модуль комплексного числа - это корень суммы квадрата мнимой и действ. части" << endl;
	REQUIRE(complex.GetMagnitude() == sqrt(pow(real, 2) + pow(image, 2)));
	cout << "Аргумент комплексного числа - это арктангес отношения мнимой части к действ" << endl;
	REQUIRE(complex.GetArgument() == atan(image / real));
}


SCENARIO("Бинарный + и -")
{
	CComplex complex1(1, 4);
	CComplex complex2(7, 5);
	CComplex complexSum = complex1 + complex2;
	CComplex complexSub = complex1 - complex2;
	cout << "Бинарный плюс происходит по формуле c1 + c2 = x1+x2 + (y1 + y2)i" << endl;
	REQUIRE(complexSum.Re() == complex1.Re() + complex2.Re());
	REQUIRE(complexSum.Im() == complex1.Im() + complex2.Im());
	cout << "Бинарный минус происходит по формуле c1 - c2 = x1-x2 + (y1  y2)i" << endl;
	REQUIRE(complexSub.Re() == complex1.Re() - complex2.Re());
	REQUIRE(complexSub.Im() == complex1.Im() - complex2.Im());
}

SCENARIO("Умножение комплексного числа на комплексное, умножение комплексного на скаляр, умножения скаляра на комплексное")
{
	double scalar = 5;
	CComplex complex1(2, 3);
	CComplex complex2(3, -1);
	CComplex complexMultiComplex = complex1 * complex2;
	CComplex complexMultiScalar = complex1 * scalar;
	CComplex scalarMultiComplex = scalar * complex1;
	cout << "Умножение комплексного на комплексное происходит по формуле c1 * c2 = x1x2 - y1y2 + (x1y2 + x2y1)i" << endl;
	REQUIRE(complexMultiComplex.Re() == complex1.Re() * complex2.Re() - complex1.Im() * complex2.Im());
	REQUIRE(complexMultiComplex.Im() == complex1.Re() * complex2.Im() + complex2.Re() * complex1.Im());
	cout << "Умножение комплексного числа на скаляр происходит по формуле c1 * k = x1 * k + (y1 * k)i" << endl;
	REQUIRE(complexMultiScalar.Re() == complex1.Re() * scalar);
	REQUIRE(complexMultiScalar.Im() == complex1.Im() * scalar);
	cout << "Умножение скаляра на комплексное происходит по формуле k * c1 = x1 * k + (y1 * k)i" << endl;
	REQUIRE(scalarMultiComplex.Re() == complex1.Re() * scalar);
	REQUIRE(scalarMultiComplex.Im() == complex1.Im() * scalar);
}

SCENARIO("Деление комплексного числа на комплексное, деление комплексного на скаляр")
{
	double zero = 0;
	double scalar = 5;
	CComplex zeroComplex(0, 0);
	CComplex c1(6.0, 8.0);
	CComplex c2(4.0, -2.0);

	CComplex c1DivZeroComplex = c1 / zeroComplex;
	CComplex c1DivC2 = c1 / c2;
	CComplex c1DivZeroScalar = c1 / zero;
	CComplex c1DivScalar = c1 / scalar;

	cout << "Деление комплексного числа на нулевое комплексное невозможно. Вернет то же самое комлпексное число" << endl;
	REQUIRE(c1DivZeroComplex.Re() == c1.Re());
	REQUIRE(c1DivZeroComplex.Im() == c1.Im());
	cout << "Деление комплексного числа на ненулевое комплексное происходит по формуле c1 / c2 = (x1x2 + y1y2) / (x2*x2 + y2*y2) + ((y1x2 -x1y2) / (x2*x2 + y2*y2))i" << endl;
	double powXY = c2.Re() * c2.Re() + c2.Im() * c2.Im();
	REQUIRE(c1DivC2.Re() == ((c1.Re() * c2.Re() + c1.Im() * c2.Im()) / powXY));
	REQUIRE(c1DivC2.Im() == ((c1.Im() * c2.Re() - c1.Re() * c2.Im()) / powXY));
	cout << "Деление комплексного числа на ноль невозможно. Вернет то же самое комлпексное число" << endl;
	REQUIRE(c1DivZeroScalar.Re() == c1.Re());
	REQUIRE(c1DivZeroScalar.Im() == c1.Im());
	cout << "Деление комлпексеного числа не ненулевой скаляр происходит по формуле c1 / k = x1 / k + (y1 / k)i" << endl;
	REQUIRE(c1DivScalar.Re() == c1.Re() / scalar);
	REQUIRE(c1DivScalar.Im() == c1.Im() / scalar);
}

SCENARIO("Унарный + и -")
{
	CComplex complex(1, 3);
	CComplex binarPlus = +complex;
	CComplex binarMin = -complex;
	cout << "Унарный плюс возвращает такое же мнимое число" << endl;
	REQUIRE(binarPlus.Re() == complex.Re());
	REQUIRE(binarPlus.Im() == complex.Im());
	cout << "Унарный минус меняет знаки действительной и мнимой части" << endl;
	REQUIRE(binarMin.Re() == -complex.Re());
	REQUIRE(binarMin.Im() == -complex.Im());
}

SCENARIO("Оператор +=")
{
	cout << "Оператор += изменяет текущее комплексное число, добавляя мнимую и действ. части другого числа" << endl;
	CComplex c1(1, 2);
	CComplex c2(1, 3);
	c1 += c2;
	REQUIRE(c1.Re() == 2);
	REQUIRE(c1.Im() == 5);
}

SCENARIO("Оператор -=")
{
	cout << "Оператор -= изменяет текущее комплексное число, вычитая из этого числа мнимую и действ. части другого числа" << endl;
	CComplex c1(1, 2);
	CComplex c2(1, 3);
	c1 -= c2;
	REQUIRE(c1.Re() == 0);
	REQUIRE(c1.Im() == -1);
}

SCENARIO("Оператор *=")
{
	cout << "Оператор *= изменяет текущее комплексное число, умножая его на другое комплексное число по формуле c1 * c2 = x1x2 - y1y2 + (x1y2 + x2y1)i" << endl;
	CComplex c1(1, 2);
	CComplex c2(1, 3);
	c1 *= c2;
	REQUIRE(c1.Re() == 1 * 1 - 2 * 3);
	REQUIRE(c1.Im() == 1 * 3 + 1 * 2);
}

SCENARIO("Оператор /=")
{
	cout << "Оператор /= не изменяет текущее число, если делить на нулевое комплексное число" << endl;
	cout << "Оператор /= изменяет текущее комплексное число, деля его на другое комплексное число по формуле c1 / c2 = (x1x2 + y1y2) / (x2*x2 + y2*y2) + ((y1x2 -x1y2) / (x2*x2 + y2*y2))i" << endl;
	CComplex c1(1, 2);
	CComplex c2(1, 3);
	CComplex cZero(0, 0);
	c1 /= cZero;
	REQUIRE(c1.Re() == 1);
	REQUIRE(c1.Im() == 2);
	c1 /= c2;
	REQUIRE(c1.Re() == (1.0 * 1.0 + 2.0 * 3.0) / (1.0 + 9.0));
	REQUIRE(c1.Im() == (2.0 * 1.0 - 1.0 * 3.0) / (1.0 + 9.0));
}

SCENARIO("Оператор ==")
{
	CComplex c1(1, 1);
	CComplex c2(1, 1);
	CComplex c3(3, 4);
	CComplex c4(1, 3);
	CComplex c5(4, 1);
	CComplex c6(1, 0);

	double s1 = 1;
	double s2 = 2;

	cout << "Оператор ==. Комплексные числа с разными действ. и мнимыми частями не равны" << endl;
	bool c1Eqc3 = c1 == c3;
	REQUIRE(c1Eqc3 == false);
	cout << "Оператор ==. Комплексные числа с равными действ., но разными мнимыми частями не равны" << endl;
	bool c1Eqc4 = c1 == c4;
	REQUIRE(c1Eqc4 == false);
	cout << "Оператор ==. Комплексные числа с равными мнимыми, но разными действ. частями не равны" << endl;
	bool c1Eqc5 = c1 == c5;
	REQUIRE(c1Eqc5 == false);
	cout << "Оператор ==. Комплексные числа с равными действ., и мнимыми частями равны" << endl;
	bool c1Eqc2 = c1 == c2;
	REQUIRE(c1Eqc2 == true);
	cout << "Оператор ==. Скаляр и комлексное число не равны, если действ. часть не равна скаляру" << endl;
	bool c1Eqs2 = c1 == s1;
	REQUIRE(c1Eqs2 == false);
	cout << "Оператор ==. Скаляр и комлексное число не равны, если действ. часть равна скаляру, а мнимая отлична от 0" << endl;
	bool c1Eqs1 = c1 == s1;
	REQUIRE(c1Eqs1 == false);
	cout << "Оператор ==. Скаляр и комлексное число равны, если действ. часть равна скаляру, а мнимая 0" << endl;
	bool c6Eqs1 = c6 == s1;
	REQUIRE(c6Eqs1 == true);
	cout << "Оператор ==. Комлексное число и скаляр не равны, если действ. часть не равна скаляру" << endl;
	bool s1Eqc3 = s1 == c3;
	REQUIRE(s1Eqc3 == false);
	cout << "Оператор ==. Комлексное число и скаляр не равны, если действ. часть равна скаляру, а мнимая отлична от 0" << endl;
	bool s1Eqc1 = s1 == c1;
	REQUIRE(s1Eqc1 == false);
	cout << "Оператор ==. Комлексное число и скаляр равны, если действ. часть равна скаляру, а мнимая 0" << endl;
	bool s1Eqc6 = s1 == c6;
	REQUIRE(s1Eqc6 == true);
}

SCENARIO("Оператор !=")
{
	CComplex c1(1, 1);
	CComplex c2(1, 1);
	CComplex c3(3, 4);
	CComplex c4(1, 3);
	CComplex c5(4, 1);
	CComplex c6(1, 0);

	double s1 = 1;
	double s2 = 2;

	cout << "Оператор !=. Комплексные числа с разными действ. и мнимыми частями не равны" << endl;
	bool c1Eqc3 = c1 != c3;
	REQUIRE(c1Eqc3 == true);
	cout << "Оператор !=. Комплексные числа с равными действ., но разными мнимыми частями не равны" << endl;
	bool c1Eqc4 = c1 != c4;
	REQUIRE(c1Eqc4 == true);
	cout << "Оператор !=. Комплексные числа с равными мнимыми, но разными действ. частями не равны" << endl;
	bool c1Eqc5 = c1 != c5;
	REQUIRE(c1Eqc5 == true);
	cout << "Оператор !=. Комплексные числа с равными действ., и мнимыми частями равны" << endl;
	bool c1Eqc2 = c1 != c2;
	REQUIRE(c1Eqc2 == false);
	cout << "Оператор !=. Скаляр и комлексное число не равны, если действ. часть не равна скаляру" << endl;
	bool c1Eqs2 = c1 != s1;
	REQUIRE(c1Eqs2 == true);
	cout << "Оператор !=. Скаляр и комлексное число не равны, если действ. часть равна скаляру, а мнимая отлична от 0" << endl;
	bool c1Eqs1 = c1 != s1;
	REQUIRE(c1Eqs1 == true);
	cout << "Оператор !=. Скаляр и комлексное число равны, если действ. часть равна скаляру, а мнимая 0" << endl;
	bool c6Eqs1 = c6 != s1;
	REQUIRE(c6Eqs1 == false);
	cout << "Оператор !=. Комлексное число и скаляр не равны, если действ. часть не равна скаляру" << endl;
	bool s1Eqc3 = s1 != c3;
	REQUIRE(s1Eqc3 == true);
	cout << "Оператор !=. Комлексное число и скаляр не равны, если действ. часть равна скаляру, а мнимая отлична от 0" << endl;
	bool s1Eqc1 = s1 != c1;
	REQUIRE(s1Eqc1 == true);
	cout << "Оператор !=. Комлексное число и скаляр равны, если действ. часть равна скаляру, а мнимая 0" << endl;
	bool s1Eqc6 = s1 != c6;
	REQUIRE(s1Eqc6 == false);
}

SCENARIO("Оператор <<")
{
	CComplex c1(0, 0);
	ostringstream output;
	string expectedOutput = "0";
	output << c1;
	cout << "Если нет ни действ., ни мнимой части, то выведет в поток 0" << endl;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть только действ. число с +, то выведет в поток это число" << endl;
	CComplex c2(1, 0);
	expectedOutput = "1";
	output.str("");
	output << c2;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть только действ. число с -, то выведет в поток это число" << endl;
	CComplex c3(-4, 0);
	expectedOutput = "-4";
	output.str("");
	output << c3;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть только мнимое положительное число, то выведет в поток это число + i" << endl;
	CComplex c4(0, 1);
	expectedOutput = "1i";
	output.str("");
	output << c4;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть только мнимое отрицательно число, то выведет в поток это число + i" << endl;
	CComplex c5(0, -1);
	expectedOutput = "-1i";
	output.str("");
	output << c5;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть положительное действ. число и полож. мнимое, то выведет в поток это действ. + мнимое + i" << endl;
	CComplex c6(1, 1);
	expectedOutput = "1+1i";
	output.str("");
	output << c6;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть положительное действ. число и отрицательное. мнимое, то выведет в поток это действ. + мнимое + i" << endl;
	CComplex c7(1, -1);
	expectedOutput = "1-1i";
	output.str("");
	output << c7;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть отрицательное действ. число и полож. мнимое, то выведет в поток это действ. + мнимое + i" << endl;
	CComplex c8(-1, 1);
	expectedOutput = "-1+1i";
	output.str("");
	output << c8;
	REQUIRE(output.str() == expectedOutput);
	cout << "Если есть отрицательное действ. число и отр. мнимое, то выведет в поток это действ. + мнимое + i" << endl;
	CComplex c9(-1, -1);
	expectedOutput = "-1-1i";
	output.str("");
	output << c9;
	REQUIRE(output.str() == expectedOutput);
}

SCENARIO("Оператор >>")
{
	cout << "" << endl;
}