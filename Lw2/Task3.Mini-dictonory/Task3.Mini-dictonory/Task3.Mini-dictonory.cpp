#include <Windows.h>
#include <optional>
#include <fstream>
#include <ostream>
#include <istream>
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

	return nullopt;
};

int main(int argc, char* argv[])
{
	SetRuEnc();
	auto args = ParseArgs(argc, argv);

	Dictionary dictionary;
	if (args)
	{
		dictionary = ReadDictinory(args.value());
	}

	string line;
	bool hasNewTranslation = false;
	while (getline(cin, line))
	{
		if (line.empty())
		{
			cout << endl;
			continue;
		}
		if (line == "...")
		{
			if (hasNewTranslation)
			{
				string outputFileName = args ? args.value() : "";
				SaveUpdatedDictionaryUI(cin, cout, dictionary, outputFileName);
			}
			break;
		}

		string translation = Translate(dictionary, line);
		if (!translation.empty())
		{
			cout << translation << endl;
		}
		else
		{
			WriteTranslationUI(cin, cout, line, hasNewTranslation, dictionary);
		}
	}
}