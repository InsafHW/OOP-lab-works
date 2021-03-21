#include <iostream>
#include <string>
#include <map>
#include <Windows.h>
#include <optional>
#include <fstream>
#include "Dictinory.h"

using namespace std;

typedef map<string, vector<string>> Dictinory;

void SetRuEnc()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

optional<string> ParseArgs(int argc, char* argv[])
{
	if (argc == 2)
	{
		return argv[1];
	}
	std::cout << "Invalid param count. Usage Mini-dictonory.exe <dictinoryFile>\n";
	return nullopt;
};

int main(int argc, char* argv[])
{
	SetRuEnc();
	auto args = ParseArgs(argc, argv);
	string toSaveDict;

	Dictinory dictinory;
	if (args)
	{
		dictinory = ReadDictinory(args.value());
	}

	string line;
	bool addedWordInDictinory = false;
	while (getline(cin, line))
	{
		//Translate(line, addedWordInDictinory, toSaveDict, args ? args.value() : "dictonory.txt", dictinory);
		if (line.empty())
		{
			cout << endl;
			continue;
		}
		if (line == "...")
		{
			if (addedWordInDictinory)
			{
				cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
				char ch;
				ch = cin.get();
				if (ch == 'Y' || ch == 'y')
				{
					if (args)
					{
						SaveDictionory(args.value(), toSaveDict);
					}
					else
					{
						SaveDictionory("dictinory.txt", toSaveDict);
					}
					cout << "Изменения сохранены. До свидания.";
				}
				else
				{
					cout << "Изменения не сохранены.";
				}
			}
			break;
		}
		string lineCopy = line;
		ToLowerString(line);
		if (dictinory.find(line) != dictinory.end())
		{
			auto translation = dictinory[line];
			for (unsigned i = 0; i < translation.size(); i++)
			{
				if (i != 0)
				{
					cout << ", ";
				}
				cout << translation[i];
			}
			cout << endl;
		}
		else
		{
			string translation;
			bool hasTranslation = false;
			cout << "Неизвестное слово \"" << lineCopy << "\". Введите перевод или пустую строку для отказа.\n";
			while (true)
			{
				char ch = cin.get();
				if (translation.length() > 1 && ch == '\n')
				{
					hasTranslation = true;
					break;
				}
				translation += ch;
				if (translation == "\n")
				{
					cout << "Слово \"" << line << "\" проигнорировано.\n";
					break;
				}
			}
			if (hasTranslation)
			{
				string translationCopy = translation;
				ToLowerString(translation);
				toSaveDict += line + " " + translation + "\n";
				addedWordInDictinory = true;
				dictinory[line].push_back(translation);
				cout << "Слово \"" << line << "\" сохранено в словаре как \"" << translationCopy << "\"\n";
			}
		}
	}
}