#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include <Windows.h>

#include "../Task3. Mini-dictinory/Dictinory.h"

using namespace std;

SCENARIO("Initilize dictonory")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Проверка инициализации словаря: ";

	Dictionary dict = {
		{"cat", vector<string> {"кошка", "кот"}},
		{"dog", vector<string> {"собака"}},
		{"fox", vector<string> {"лиса", "лисочка"}}
	};

	Dictionary readDict = ReadDictinory("test_read_dictonory.txt");

	REQUIRE(dict.size() == readDict.size());

	auto it1 = dict.begin();
	auto it2 = readDict.begin();
	while (true)
	{
		bool end1 = it1 == dict.end();
		bool end2 = it2 == readDict.end();

		if (end1 && end2) break;

		REQUIRE(it1->first == it2->first);
		auto x1 = it1->second;
		auto x2 = it2->second;
		REQUIRE(x1.size() == x2.size());
		for (unsigned i = 0; i < x1.size(); i++)
		{
			REQUIRE(x1[i] == x2[i]);
		}
		it1++;
		it2++;
	}
	cout << "успешно!" << endl;
}

SCENARIO("Saving new words into dictonary in program")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Проверка сохранения новых слов и переводов в программе: ";
	Dictionary dict = {
		{"cat", vector<string> {"кошка"}},
		{"music", vector<string> {"музыка"}}
	};

	AddWordInDictonary(dict, "frog", "лягушка");

	Dictionary newDict = {
		{"cat", vector<string> {"кошка"}},
		{"music", vector<string> {"музыка"}},
		{"frog", vector<string> {"лягушка"}}
	};

	REQUIRE(dict.size() == 3);

	auto it1 = dict.begin();
	auto it2 = newDict.begin();
	while (true)
	{
		bool end1 = it1 == dict.end();
		bool end2 = it2 == newDict.end();

		if (end1 && end2) break;

		REQUIRE(it1->first == it2->first);
		auto x1 = it1->second;
		auto x2 = it2->second;
		REQUIRE(x1.size() == x2.size());
		for (unsigned i = 0; i < x1.size(); i++)
		{
			REQUIRE(x1[i] == x2[i]);
		}
		it1++;
		it2++;
	}
	cout << "успешно!" << endl;
}

SCENARIO("Saving new words into dictonory file")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Проверка сохранения новых слов и переводов в файл: ";

	ifstream oldTranlsationFile("test_read_dictonory.txt");
	string line, oldTranslations, newTranslations;
	while (getline(oldTranlsationFile, line))
	{
		oldTranslations += line + "\n";
	}
	newTranslations += "thunder гром\n";
	newTranslations += "ligtning молния\n";

	SaveDictionoryIntoFile("test_read_dictonory.txt", newTranslations);

	ifstream updatedTranslationFile("test_read_dictonory.txt");
	string updatedTranslations;
	while (getline(updatedTranslationFile, line))
	{
		updatedTranslations += line + "\n";
	}
	REQUIRE(oldTranslations + newTranslations == updatedTranslations);
	cout << "успешно!\n";
}

SCENARIO("Translating")
{
	cout << "Проверка функционала перевода: ";
	Dictionary dict = {
		{"cat", vector<string> {"кошка", "кошак"}},
		{"dog", vector<string> {"собака"}},
		{"car", vector<string> {"машина"}}
	};
	REQUIRE(Translate(dict, "cat") == "кошка, кошак");
	REQUIRE(Translate(dict, "dog") == "собака");
	REQUIRE(Translate(dict, "car") == "машина");
	REQUIRE(Translate(dict, "") == "");
	REQUIRE(Translate(dict, "man") == "");
	cout << "успешно!" << endl;
}