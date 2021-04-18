#include <iostream>
#include <Windows.h>
#include "CShapeController.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	CShapeController controller;

	string x = "ff0000";

	cout << (stoul(x));
	controller.ReadShapes(cin);


}
