#include <iostream>
#include <Windows.h>
#include "CShapeController.h"

using namespace std;

const string ADD_NEW_SHAPE = "Добавить новую фигиуру";
const string FIND_MIN_PERIMETER = "Показать фигуру с минимальным периметром";
const string FIND_MAX_AREA = "Показать фигуру с максимальной площадью";
const string SHOW_SHAPES_INFO = "Показать информацию о фигурах";
const string EXIT = "Завершить программу";

const string FIRST = "1 - ";
const string SECOND = "2 - ";
const string THIRD = "3 - ";
const string FOURTH = "4 - ";
const string FIFTH = "5 - ";
const string SIXTH = "6 - ";
const string SEVENTH = "7 - ";
const string EIGTH = "8 - ";
const string NINETH = "9 - ";
const string TENTH = "10 - ";
const string BORDER = "-------------------------------------";


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string answerLine, line;
	bool isFinished = false;
	int answer = 0;
	CShapeController controller(cout);
	while (true)
	{
		if (isFinished) break;
		cout << FIRST << ADD_NEW_SHAPE << endl;
		cout << SECOND << FIND_MIN_PERIMETER << endl;
		cout << THIRD << FIND_MAX_AREA << endl;
		cout << FOURTH << SHOW_SHAPES_INFO << endl;
		cout << FIFTH << EXIT << endl;
		cout << BORDER << endl;

		getline(cin, answerLine);
		if (answerLine.empty() || (answerLine.find_first_not_of("0123456789.") != answerLine.npos))
		{
			break;
		}

		answer = stoi(answerLine);

		switch (answer)
		{
		case 1:
			cout << "Введите название и параметры фигуры: ";
			getline(cin, line);
			controller.ReadShape(line);
			break;
		case 2:
			controller.GetMinPerimeterInfo();
			break;
		case 3:
			controller.GetMaxSquareInfo();
			break;
		case 4:
			controller.WriteInfos();
			break;
		default:
			isFinished = true;
			break;
		}
	}
}
