#include "UrlParser.h"

const int MAX_PORT = 65535;
const int MIN_PORT = 1;
const int HTTP_PORT = 80;
const int HTTPS_PORT = 443;
const int FTP_PORT = 21;

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	string copyUrl = url;
	transform(copyUrl.begin(), copyUrl.end(), copyUrl.begin(), tolower);

	regex regularUrlParse("(http|https|ftp)://([a-z.]+):?([^/ :]*)(/?[^ #:?]*)?([^ #:]*)#?([^ :]*)");
	if (!regex_match(copyUrl, regularUrlParse))
	{
		return false;
	}

	int hostStartIdx = copyUrl.find("://");
	string protocolString = copyUrl.substr(0, hostStartIdx);
	copyUrl = copyUrl.substr(hostStartIdx + 3);

	if (protocolString == "http") protocol = Protocol::HTTP;
	if (protocolString == "https") protocol = Protocol::HTTPS;
	if (protocolString == "ftp") protocol = Protocol::FTP;

	int portStartIdx = copyUrl.find(":");
	if (portStartIdx != -1)
	{
		host = copyUrl.substr(0, portStartIdx);
		int documentStartIdx = copyUrl.find("/");
		if (documentStartIdx - portStartIdx <= 1)
		{
			return false;
		}

		string portString = copyUrl.substr(portStartIdx + 1, documentStartIdx - portStartIdx - 1);
		if (portString.find_first_not_of("0123456789") != -1)
		{
			return false;
		}

		int portNumber = stoi(portString);
		if (portNumber < MIN_PORT || portNumber > MAX_PORT)
		{
			return false;
		}

		port = portNumber;
		document = copyUrl.substr(documentStartIdx + 1);
	}
	else
	{
		switch (protocol)
		{
		case Protocol::HTTP:
			port = HTTP_PORT;
			break;
		case Protocol::HTTPS:
			port = HTTPS_PORT;
			break;
		case Protocol::FTP:
			port = FTP_PORT;
			break;
		}
		int documentStartIdx = copyUrl.find("/");
		host = copyUrl.substr(0, documentStartIdx);
		document = documentStartIdx != -1 ? copyUrl.substr(documentStartIdx + 1) : "";
	}
	return true;
}