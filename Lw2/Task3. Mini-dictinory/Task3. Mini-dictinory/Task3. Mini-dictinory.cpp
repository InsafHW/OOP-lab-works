#include <Windows.h>
#include <optional>
#include <fstream>
#include "Dictinory.h"

using namespace std;

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
	std::cout << "Invalid params count. Usage Mini-dictonory.exe <dictinoryFile>\n";
	return nullopt;
};

void SaveNewTranslationsInFileUI(string outputFileName, string newTranslations)
{
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	char ch;
	ch = cin.get();
	if (ch == 'Y' || ch == 'y')
	{
		SaveDictionoryIntoFile(outputFileName, newTranslations);
		cout << "Изменения сохранены в файле \"" << outputFileName << "\". До свидания.";
	}
	else
	{
		cout << "Изменения не сохранены.";
	}
}

void WriteTranslationUI(string unknowWord, bool& hasBeenTranslated, string& translation)
{
	cout << "Неизвестное слово \"" << unknowWord << "\". Введите перевод или пустую строку для отказа.\n";
	while (true)
	{
		char ch = cin.get();
		if (translation.length() > 1 && ch == '\n')
		{
			hasBeenTranslated = true;
			break;
		}
		translation += ch;
		if (translation == "\n")
		{
			cout << "Слово \"" << unknowWord << "\" проигнорировано.\n";
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	SetRuEnc();
	auto args = ParseArgs(argc, argv);
	string newTranslations;

	Dictionary dictionary;
	if (args)
	{
		dictionary = ReadDictinory(args.value());
	}

	string line;
	bool addedWordInDictinory = false;
	while (getline(cin, line))
	{
		if (line.empty())
		{
			cout << endl;
			continue;
		}
		if (line == "...")
		{
			if (addedWordInDictinory)
			{
				string outputFileName = args ? args.value() : "dictionary.txt";
				SaveNewTranslationsInFileUI(outputFileName, newTranslations);
			}
			break;
		}
		string loweredLine = ToLowerString(line);
		string translation = Translate(dictionary, loweredLine);
		if (!translation.empty())
		{
			cout << translation << endl;
		}
		else
		{
			string translation;
			bool hasTranslation = false;
			WriteTranslationUI(line, hasTranslation, translation);
			if (hasTranslation)
			{
				string loweredTranslation = ToLowerString(translation);
				newTranslations += loweredLine + " " + loweredTranslation + "\n";
				addedWordInDictinory = true;
				AddWordInDictonary(dictionary, loweredLine, loweredTranslation);
				cout << "Слово \"" << line << "\" сохранено в словаре как \"" << translation << "\"\n";
			}
		}
	}
}