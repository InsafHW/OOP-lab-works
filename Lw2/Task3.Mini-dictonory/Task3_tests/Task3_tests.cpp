#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include <Windows.h>

#include "../Task3.Mini-dictonory/Dictinory.h"

using namespace std;

const string DICTFILE = "dictonory.txt";

void WriteInFile(string str, string fileName = DICTFILE)
{
	ofstream dict(fileName);
	dict << str;
	dict.close();
}

// Проверка ReadDictonory
SCENARIO("Если файла не существует, то вернется пустой map")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Если файла не существует, то вернется пустой map" << endl;
	REQUIRE(ReadDictinory("несущфайл.txt").empty());
}

SCENARIO("Если файл пустой, то вернется пустой map")
{
	cout << "Если файл пустой, то вернется пустой map" << endl;
	WriteInFile("");
	REQUIRE(ReadDictinory(DICTFILE).empty());
}

SCENARIO("Если файл не пустой, то вернется map с соотв. переводами")
{
	cout << "Если файл не пустой, то вернется map с соотв. переводами" << endl;
	WriteInFile("dog собака\ncat кошка\nfox лиса");
	Dictionary x = { {"dog", "собака"}, {"cat", "кошка"}, {"fox", "лиса"} };
	auto dict = ReadDictinory(DICTFILE);
	REQUIRE(x == dict);
}

// Проверка перевода
SCENARIO("Если перевести пустую строку, вернется пустая строка")
{
	cout << "Если перевести пустую строку, то вернется пустая строка" << endl;
	Dictionary x = { {"dog", "собака"}, {"cat", "кошка"}, {"fox", "лиса"} };
	REQUIRE(Translate(x, "").empty());
}

SCENARIO("Если слова нет в словаре, то вернется пустая строка")
{
	cout << "Если слова нет в словаре, то вернется пустая строка" << endl;
	Dictionary x = { {"dog", "собака"}, {"cat", "кошка"}, {"fox", "лиса"} };
	REQUIRE(Translate(x, "human").empty());
}

SCENARIO("Если слово есть в словаре, то вернется его перевод")
{
	cout << "Если слово есть в словаре, то вернется его перевод" << endl;
	Dictionary x = { {"dog", "собака"}, {"cat", "кошка"}, {"fox", "лиса"} };
	REQUIRE(Translate(x, "cat") == "кошка");
}

SCENARIO("Если слово есть в словаре, но мы напишем его с отличным регистром, то слово все равно переведется")
{
	cout << "Если слово есть в словаре, но мы напишем его с отличным регистром, то слово все равно переведется" << endl;
	Dictionary x = { {"dog", "собака"}, {"cat", "кошка"}, {"fox", "лиса"} };
	REQUIRE(Translate(x, "DOG") == "собака");
}

// Проверка AddInDictonary

SCENARIO("Если попробуем добавить перевод пустой строке, ничего не поменяется")
{
	cout << "Если попробуем добавить перевод пустой строке, ничего не поменяется" << endl;
	Dictionary x = { {"dog", "собака"}, {"cat", "кошка"}, {"fox", "лиса"} };
	int oldSize = x.size();
	AddInDictonary(x, "", "перевод");
	int newSize = x.size();
	REQUIRE(oldSize == newSize);
}

SCENARIO("Если попробуем добавить пустой перевод строке, ничего не поменяется")
{
	cout << "Если попробуем добавить пустой перевод строке, ничего не поменяется" << endl;
	Dictionary x = { {"dog", "собака"} };
	int oldSize = x.size();
	AddInDictonary(x, "wordToTranslate", "");
	int newSize = x.size();
	REQUIRE(oldSize == newSize);
	REQUIRE(x["dog"] == "собака");
}

SCENARIO("Если добавить непустое слово и непустой перевод, то словарь обновится и добавит эти слова")
{
	cout << "Если добавить непустое слов и непустой перевод, то словарь обновится и добавит эти слова" << endl;
	Dictionary x = { {"dog", "собака"} };
	AddInDictonary(x, "cat", "кошка");
	REQUIRE(x["dog"] == "собака");
	REQUIRE(x["cat"] == "кошка");
}

SCENARIO("Если добавить слово в немаленьком регистре, то оно сохранится в маленьком регистре, для последующего доступа к нему любым регистром")
{
	cout << "Если добавить слово в немаленьком регистре, то оно сохранится в маленьком регистре, для последующего доступа к нему любым регистром" << endl;
	Dictionary x = { {"dog", "собака"} };
	AddInDictonary(x, "CAT", "кошка");
	REQUIRE(x["dog"] == "собака");
	REQUIRE(x["cat"] == "кошка");
}

SCENARIO("Если добавить перевод слова в немаленьком регистре, то оно сохранится в маленьком регистре")
{
	cout << "Если добавить перевод слова в немаленьком регистре, то оно сохранится в маленьком регистре" << endl;
	Dictionary x = { {"dog", "собака"} };
	AddInDictonary(x, "cat", "КОШКА");
	REQUIRE(x["dog"] == "собака");
	REQUIRE(x["cat"] == "кошка");
}

// SaveDictionoryIntoFile

SCENARIO("Сохранение словаря в файл")
{
	cout << "Сохранение словаря в файл" << endl;
	Dictionary x = { {"dog", "собака"} };
	AddInDictonary(x, "cat", "кошка");
	AddInDictonary(x, "duck", "утка");
	SaveDictionoryIntoFile(DICTFILE, x);
	auto y = ReadDictinory(DICTFILE);
	Dictionary expected = { {"dog", "собака"}, {"cat", "кошка"}, {"duck", "утка"} };
	REQUIRE(y == expected);
}


// Провека UI функциий
// SaveUpdatedDictionaryUI

SCENARIO("UI сохранения словаря в файл. Передано название файла и если мы ввели Y, то сохраняется в соотв. файл")
{
	cout << "UI сохранения словаря в файл. Передано название файла и если мы ввели Y, то сохраняется в соотв. файл" << endl;
	Dictionary x = { {"dog", "собака"} };
	ofstream tempOutput("tempOutput.txt");
	stringstream tempInput;
	tempInput << "д";
	SaveUpdatedDictionaryUI(tempInput, tempOutput, x, "newdict.txt");
	tempOutput.close();
	ifstream inp("tempOutput.txt");

	string resultString;
	string str;
	while (getline(inp, str))
	{
		resultString += str + "\n";
	}
	REQUIRE(resultString == "В словарь были внесены изменения. Введите Д или д для сохранения перед выходом.\nИзменения сохранены в файле \"newdict.txt\". До свидания.\n");
	Dictionary y = ReadDictinory("newdict.txt");
	REQUIRE(x == y);
}

SCENARIO("UI сохранения словаря в файл. Не передано название файла и если мы ввели Y, то попросит ввести название файла и сохраняет в него")
{
	cout << "UI сохранения словаря в файл. Не передано название файла и если мы ввели Y, то попросит ввести название файла и сохраняет в него" << endl;
	Dictionary x = { {"dog", "собака"} };
	ofstream tempOutput("tempOutput.txt");
	stringstream tempInput;
	tempInput << "д" << endl << "newdict.txt";
	SaveUpdatedDictionaryUI(tempInput, tempOutput, x);
	tempOutput.close();
	ifstream inp("tempOutput.txt");

	string resultString;
	string str;
	while (getline(inp, str))
	{
		resultString += str + "\n";
	}
	REQUIRE(resultString == "В словарь были внесены изменения. Введите Д или д для сохранения перед выходом.\nВведите название файла для сохранения словаря: \nИзменения сохранены в файле \"newdict.txt\". До свидания.\n");
	Dictionary y = ReadDictinory("newdict.txt");
	REQUIRE(x == y);
}

SCENARIO("UI сохранения словаря в файл. Если мы ввели N, то ничего не сохранится")
{
	cout << "UI сохранения словаря в файл. Если мы ввели N, то ничего не сохранится" << endl;
	Dictionary x = { {"dog", "собака"} };
	ofstream tempOutput("tempOutput.txt");
	stringstream tempInput;
	tempInput << "н" << endl << "newdict.txt";
	SaveUpdatedDictionaryUI(tempInput, tempOutput, x);
	tempOutput.close();
	ifstream inp("tempOutput.txt");

	string resultString;
	string str;
	while (getline(inp, str))
	{
		resultString += str + "\n";
	}
	REQUIRE(resultString == "В словарь были внесены изменения. Введите Д или д для сохранения перед выходом.\nИзменения не сохранены.\n");
}

//WriteTranslationUI
SCENARIO("UI добавления перевода. Если мы введем пустую строку, то слово не добавится")
{
	cout << "UI добавления перевода. Если мы введем пустую строку, то слово не добавится" << endl;
	ofstream tempOutput("tempOutput.txt");
	Dictionary dict = { {"dog", "собака"} };
	stringstream tempInput;
	tempInput << endl;
	bool x = false;
	WriteTranslationUI(tempInput, tempOutput, "key", x, dict);
	tempOutput.close();
	ifstream inp("tempOutput.txt");

	string resultString;
	string str;
	while (getline(inp, str))
	{
		resultString += str + "\n";
	}

	REQUIRE(resultString == "Неизвестное слово \"key\". Введите перевод или пустую строку для отказа.\nСлово \"key\" проигнорировано.\n");
	REQUIRE(dict.size() == 1);
	REQUIRE(dict["dog"] == "собака");
}

SCENARIO("UI добавления перевода. Если мы введем не пустую строку, то перевод добавится")
{
	cout << "UI добавления перевода. Если мы введем не пустую строку, то перевод добавится" << endl;
	ofstream tempOutput("tempOutput.txt");
	Dictionary dict = { {"dog", "собака"} };
	stringstream tempInput;
	tempInput << "ключ" << endl;
	bool x = false;
	WriteTranslationUI(tempInput, tempOutput, "key", x, dict);
	tempOutput.close();
	ifstream inp("tempOutput.txt");

	string resultString;
	string str;
	while (getline(inp, str))
	{
		resultString += str + "\n";
	}
	REQUIRE(resultString == "Неизвестное слово \"key\". Введите перевод или пустую строку для отказа.\nСлово \"key\" сохранено в словаре как \"ключ\"\n");
	REQUIRE(dict.size() == 2);
	REQUIRE(dict["dog"] == "собака");
	REQUIRE(dict["key"] == "ключ");
}
