#include <iostream>
#include "FindMaxEx.h"
#include <vector>
#include "Sportsman.h"

int main()
{
	vector<Sportsman> people;
	people.push_back(Sportsman("Ivan Egorov", 170, 56));
	people.push_back(Sportsman("Andrey Okunev", 162, 76));
	people.push_back(Sportsman("Denis Aktuganov", 180, 100));
	people.push_back(Sportsman("Danila Lipatnikov", 175, 112));
	people.push_back(Sportsman("Leha Sadovin", 150, 59));

	Sportsman max;

	FindMaxEx(people, max, [](Sportsman s1, Sportsman s2) {return s1.GetHeight() < s2.GetHeight(); });
	cout << "Sprotsman with max heigth: " << max.GetFIO() << endl;
	FindMaxEx(people, max, [](Sportsman s1, Sportsman s2) {return s1.GetWeight() < s2.GetWeight(); });
	cout << "Sportsman with max weigth: " << max.GetFIO() << endl;
}
