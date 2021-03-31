#include "UrlParser.h"

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	string copyUrl = url;
	transform(copyUrl.begin(), copyUrl.end(), copyUrl.begin(), tolower);

	// начинается с http || https || ftp ://буквы и . / [:цифры]/буквы символы || / буквы символы или без дока vk.com
	regex regularUrlParse("^(http|https|ftp):\\/\\/[a-z.]+(:[\\d]{1,5}\\/[a-z]+\\S*|\\/[a-z]+\\S*|[a-z]*)");

	if (!regex_match(copyUrl, regularUrlParse))
	{
		return false;
	}

	int hostIdx = copyUrl.find("://");
	string protocolStr = copyUrl.substr(0, hostIdx);

	if (protocolStr == "http") protocol = Protocol::HTTP;
	if (protocolStr == "https") protocol = Protocol::HTTPS;
	if (protocolStr == "ftp") protocol = Protocol::FTP;

	copyUrl = copyUrl.substr(hostIdx + 3);
	int portIdx = copyUrl.find(":");

	if (portIdx != -1)
	{
		// искать порт
		host = copyUrl.substr(0, portIdx);
		copyUrl = copyUrl.substr(portIdx + 1);
		int documentIdx = copyUrl.find("/");
		int portNumber = stoi(copyUrl.substr(0, documentIdx));

		if (portNumber < 1 || portNumber > 65535)
		{
			return false;
		}

		port = portNumber;
	}
	else
	{
		int hostIdx = copyUrl.find("/");
		host = copyUrl.substr(0, hostIdx);
		switch (protocol)
		{
		case Protocol::HTTP:
			port = 80;
			break;
		case Protocol::HTTPS:
			port = 443;
			break;
		case Protocol::FTP:
			port = 21;
			break;
		}
	}

	int documentIdx = copyUrl.find("/");
	if (documentIdx != -1)
	{
		document = copyUrl.substr(documentIdx + 1);
	}
	else
	{
		document = "";
	}

	return true;
}