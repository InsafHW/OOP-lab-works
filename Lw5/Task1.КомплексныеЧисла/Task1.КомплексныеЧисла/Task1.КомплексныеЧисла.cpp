// Task1.КомплексныеЧисла.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CComplex.h"

int main()
{
	CComplex c1(2, -1);
	CComplex c2(1, 1);
	CComplex c3 = c1 / c2;
	cout << c3;
}
