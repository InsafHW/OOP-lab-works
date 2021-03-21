#include "Dictinory.h"

char ToLowerChar(char ch)
{
	if (ch >= 'A' && ch <= 'Z') ch += 'z' - 'Z';
	if (ch >= 'А' && ch <= 'Я') ch += 'я' - 'Я';
	return ch;
}

void ToLowerString(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ToLowerChar);
}

Dictinory ReadDictinory(const std::string& fileName)
{
	Dictinory dictinory;
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Failed to open '" << &file << "' for reading\n";
		return dictinory;
	}
	std::string line;
	while (getline(file, line))
	{
		int spaceIdx = line.find(" ");
		std::string engWord = line.substr(0, spaceIdx);
		ToLowerString(engWord);
		line = line.substr(spaceIdx + 1);

		std::string rusWord;
		for (unsigned i = 0; i < line.length(); i++)
		{
			if (line[i] == ',' || line[i] == ' ')
			{
				if (!rusWord.empty())
				{
					ToLowerString(rusWord);
					dictinory[engWord].push_back(rusWord);
				}
				rusWord = "";
				continue;
			}
			rusWord += line[i];
		}
		if (!rusWord.empty())
		{
			ToLowerString(rusWord);
			dictinory[engWord].push_back(rusWord);
		}
	}
	return dictinory;
}

void SaveDictionory(const std::string& fileName, std::string& transl)
{
	std::ofstream out(fileName, std::ios::app);
	transl.erase(transl.length() - 1);
	out << "\n";
	out << transl;
}

void Translate(std::string line, bool& addedWordInDictinory, std::string& newWordsToSave, std::string outputFileName, Dictinory dictinory)
{
	if (line.empty())
	{
		std::cout << std::endl;
		return;
	}
	if (line == "...")
	{
		if (addedWordInDictinory)
		{
			std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
			char ch;
			ch = std::cin.get();
			if (ch == 'Y' || ch == 'y')
			{
				SaveDictionory(outputFileName, newWordsToSave);
				std::cout << "Изменения сохранены. До свидания.";
			}
			else
			{
				std::cout << "Изменения не сохранены.";
			}
		}
		return;
	}
	std::string lineCopy = line;
	ToLowerString(line);
	if (dictinory.find(line) != dictinory.end())
	{
		auto translation = dictinory[line];
		for (unsigned i = 0; i < translation.size(); i++)
		{
			if (i != 0)
			{
				std::cout << ", ";
			}
			std::cout << translation[i];
		}
		std::cout << std::endl;
	}
	else
	{
		std::string translation;
		bool hasTranslation = false;
		std::cout << "Неизвестное слово \"" << lineCopy << "\". Введите перевод или пустую строку для отказа.\n";
		while (true)
		{
			char ch = std::cin.get();
			if (translation.length() > 1 && ch == '\n')
			{
				hasTranslation = true;
				break;
			}
			translation += ch;
			if (translation == "\n")
			{
				std::cout << "Слово \"" << line << "\" проигнорировано.\n";
				break;
			}
		}
		if (hasTranslation)
		{
			std::string translationCopy = translation;
			ToLowerString(translation);
			newWordsToSave += line + " " + translation + "\n";
			addedWordInDictinory = true;
			dictinory[line].push_back(translation);
			std::cout << "Слово \"" << lineCopy << "\" сохранено в словаре как \"" << translationCopy << "\"\n";
		}
	}
}