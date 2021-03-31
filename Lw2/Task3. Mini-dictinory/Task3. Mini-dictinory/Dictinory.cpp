#include "Dictinory.h"

char ToLowerChar(char ch)
{
	if (ch >= 'A' && ch <= 'Z') ch += 'z' - 'Z';
	if (ch >= 'À' && ch <= 'ß') ch += 'ÿ' - 'ß';
	return ch;
}

string ToLowerString(string str)
{
	transform(str.begin(), str.end(), str.begin(), ToLowerChar);
	return str;
}

Dictionary ReadDictinory(string fileName)
{
	Dictionary dictionary;
	ifstream file(fileName);
	if (!file.is_open())
	{
		cout << "Failed to open '" << &file << "' for reading\n";
		return dictionary;
	}
	string line;
	while (getline(file, line))
	{
		int rusLetterIdx = line.find_first_of("àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß");
		string engWord = line.substr(0, rusLetterIdx - 1);
		engWord = ToLowerString(engWord);
		line = line.substr(rusLetterIdx);
		string rusWord;
		for (unsigned i = 0; i < line.length(); i++)
		{
			if (line[i] == ',')
			{
				if (!rusWord.empty())
				{
					rusWord = ToLowerString(rusWord);
					dictionary[engWord].push_back(rusWord);
					// ÷òîáû óáðàòü ïðîáåë x,_y
					i++;
				}
				rusWord = "";
				continue;
			}
			rusWord += line[i];
		}
		if (!rusWord.empty())
		{
			rusWord = ToLowerString(rusWord);
			dictionary[engWord].push_back(rusWord);
		}
	}
	return dictionary;
}

string Translate(Dictionary& dictionary, string line)
{
	string translationStr;
	if (dictionary.find(line) != dictionary.end())
	{
		auto translation = dictionary[line];
		for (unsigned i = 0; i < translation.size(); i++)
		{
			if (i != 0)
			{
				translationStr += ", ";
			}
			translationStr += translation[i];
		}
		translationStr += "\n";
	}
	if (!translationStr.empty())
	{
		translationStr.erase(translationStr.length() - 1, 1);
	}
	return translationStr;
}

void AddWordInDictonary(Dictionary& dictionary, string newWordToAdd, string newWordTransaltion)
{
	dictionary[newWordToAdd].push_back(newWordTransaltion);
}

void SaveDictionoryIntoFile(string outputFileName, string newWordsToSave)
{
	ofstream out(outputFileName, ios::app);
	newWordsToSave.erase(newWordsToSave.length() - 1);
	out << "\n";
	out << newWordsToSave;
}