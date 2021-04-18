#include "Dictinory.h"

const string RUSSIAN_ALPHABET = "�������������������������������������Ũ��������������������������";
const string FAILED_OPEN = "�� ������� �������";
const string FOR_READING = "��� ������";
const string NEW_WORDS_HAVE_BEEN_ADDED = "� ������� ���� ������� ���������.";
const string PRESS_Y_TO_SAVE = "������� � ��� � ��� ���������� ����� �������.";
const string WRITE_FILE_NAME_TO_SAVE_DICTONORY = "������� �������� ����� ��� ���������� �������: ";
const string CHANGES_HAVE_BEEN_SAVED_IN_FILE = "��������� ��������� � �����";
const string GOODBYE = "�� ��������.";
const string CHANGES_HAVE_NOT_BEEN_SAVED = "��������� �� ���������.";
const string UNKNOWN_WORD = "����������� �����";
const string WRTITE_TRANSLATION_OR_EMPTY_STRING = "������� ������� ��� ������ ������ ��� ������.";
const string WORD = "�����";
const string IGNORED = "���������������.";
const string SAVED_IN_DCTONORY_AS = "��������� � ������� ���";

char ToLowerChar(char ch)
{
	if (ch >= 'A' && ch <= 'Z') ch += 'z' - 'Z';
	if (ch >= '�' && ch <= '�') ch += '�' - '�';
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
	if (ch == '�' || ch == '�')
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
