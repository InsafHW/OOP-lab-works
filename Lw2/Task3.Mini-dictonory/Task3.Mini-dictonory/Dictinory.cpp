#include "Dictinory.h"

const string RUSSIAN_ALPHABET = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const string FAILED_OPEN = "Не удалось открыть";
const string FOR_READING = "для чтения";
const string NEW_WORDS_HAVE_BEEN_ADDED = "В словарь были внесены изменения.";
const string PRESS_Y_TO_SAVE = "Введите Д или д для сохранения перед выходом.";
const string WRITE_FILE_NAME_TO_SAVE_DICTONORY = "Введите название файла для сохранения словаря: ";
const string CHANGES_HAVE_BEEN_SAVED_IN_FILE = "Изменения сохранены в файле";
const string GOODBYE = "До свидания.";
const string CHANGES_HAVE_NOT_BEEN_SAVED = "Изменения не сохранены.";
const string UNKNOWN_WORD = "Неизвестное слово";
const string WRTITE_TRANSLATION_OR_EMPTY_STRING = "Введите перевод или пустую строку для отказа.";
const string WORD = "Слово";
const string IGNORED = "проигнорировано.";
const string SAVED_IN_DCTONORY_AS = "сохранено в словаре как";

char ToLowerChar(char ch)
{
	if (ch >= 'A' && ch <= 'Z') ch += 'z' - 'Z';
	if (ch >= 'А' && ch <= 'Я') ch += 'я' - 'Я';
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
		cout << FAILED_OPEN << " \"" << fileName << "\" " << FOR_READING << endl;
		return dictionary;
	}
	string line;
	while (getline(file, line))
	{
		int rusLetterIdx = line.find_first_of(RUSSIAN_ALPHABET);
		string engWord = line.substr(0, rusLetterIdx - 1);
		string rusWord = line.substr(rusLetterIdx);

		if (!rusWord.empty())
		{
			dictionary[ToLowerString(engWord)] = ToLowerString(rusWord);
		}
	}
	return dictionary;
}

string Translate(Dictionary& dictionary, string lineToTranslate)
{
	string translatedLine;
	string lowereLineToTranslate = ToLowerString(lineToTranslate);
	if (dictionary.find(lowereLineToTranslate) != dictionary.end())
	{
		translatedLine = dictionary[lowereLineToTranslate];

	}

	return translatedLine;
}

void AddInDictonary(Dictionary& dictionary, string lineToAdd, string lineTranslation)
{
	if (lineToAdd.empty() || lineTranslation.empty()) return;
	dictionary[ToLowerString(lineToAdd)] = ToLowerString(lineTranslation);
}

void SaveDictionoryIntoFile(string outputFileName, Dictionary& dict)
{
	ofstream out(outputFileName);
	for (auto itr = dict.begin(); itr != dict.end(); itr++)
	{
		if (itr != dict.begin()) out << endl;
		out << itr->first << " " << itr->second;
	}

}

void SaveUpdatedDictionaryUI(istream& input, ostream& output, Dictionary& dict, string outputFileName)
{
	output << NEW_WORDS_HAVE_BEEN_ADDED << " " << PRESS_Y_TO_SAVE << endl;
	char ch;
	ch = input.get();
	if (ch == 'Д' || ch == 'д')
	{
		if (outputFileName.empty())
		{
			output << WRITE_FILE_NAME_TO_SAVE_DICTONORY;
			input >> outputFileName;
			output << endl;
		}
		SaveDictionoryIntoFile(outputFileName, dict);
		output << CHANGES_HAVE_BEEN_SAVED_IN_FILE << " \"" << outputFileName << "\". " << GOODBYE;
	}
	else
	{
		output << CHANGES_HAVE_NOT_BEEN_SAVED;
	}
}

void WriteTranslationUI(istream& input, ostream& output, string unknownWord, bool& hasBeenTranslated, Dictionary& dict)
{
	string translation;
	output << UNKNOWN_WORD << " \"" << unknownWord << "\". " << WRTITE_TRANSLATION_OR_EMPTY_STRING << endl;
	while (true)
	{
		char ch = input.get();
		if (translation.length() > 1 && ch == '\n')
		{
			hasBeenTranslated = true;
			break;
		}
		translation += ch;
		if (translation == "\n")
		{
			output << WORD << " \"" << unknownWord << "\" " << IGNORED << endl;
			break;
		}
	}
	if (!translation.empty() && translation != "\n")
	{
		AddInDictonary(dict, ToLowerString(unknownWord), ToLowerString(translation));
		output << WORD << " \"" << unknownWord << "\" " << SAVED_IN_DCTONORY_AS << " \"" << translation << "\"" << endl;
	}
}
