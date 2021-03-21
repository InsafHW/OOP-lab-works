#include "Encode.h"

std::string Encode(std::string const& text)
{
	std::string encodedText;
	for (unsigned i = 0; i < text.length(); i++)
	{
		switch (text[i])
		{
		case '\"':
			encodedText += "&quot;";
			break;
		case '\'':
			encodedText += "&apos;";
			break;
		case '>':
			encodedText += "&gt;";
			break;
		case '<':
			encodedText += "&lt;";
			break;
		case '&':
			encodedText += "&amp;";
			break;
		default:
			encodedText += text[i];
			break;
		}
	}
	return encodedText;
}
