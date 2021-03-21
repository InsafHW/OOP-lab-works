#include "Decode.h"
#include <map>

std::map<std::string, char> translation = {
	{"&quot;", '\"'},
	{"&apos;", '\''},
	{"&lt;", '<'},
	{"&gt;", '>'},
	{"&amp;", '&'},
};


// убрать лишнюю проверку? while Заменить на for
std::string Decode(std::string const& text)
{
	std::string decodedText;
	for (unsigned i = 0; i < text.length(); i++)
	{
		if (text[i] == '&')
		{
			std::string temp;
			while (i < text.length())
			{
				temp += text[i];
				if (text[i] == ';')
				{
					break;
				}
				i++;
			}
			if (translation[temp])
			{
				decodedText += translation[temp];
			}
			else
			{
				decodedText += temp;
			}
		}
		else
		{
			decodedText += text[i];
		}
	}
	return decodedText;
}

void DecodeLines(std::istream& input, std::ostream& output)
{
	std::string line;
	bool isFirstLine = true;
	while (std::getline(input, line))
	{
		if (!isFirstLine)
		{
			output << "\n";
		}
		output << Decode(line);
		isFirstLine = false;
	}
}
