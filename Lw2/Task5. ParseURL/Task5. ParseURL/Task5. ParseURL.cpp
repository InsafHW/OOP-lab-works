#include <iostream>
#include "UrlParser.h"

const string HOST = "HOST: ";
const string PORT = "PORT: ";
const string DOC = "DOC: ";
const string INVALID_URL = "Invalid url";

int main()
{
	Protocol protocol;
	int port;
	string host, document;
	string url;

	while (getline(cin, url))
	{
		if (ParseURL(url, protocol, port, host, document))
		{
			cout << url << endl;
			cout << HOST << host << endl;
			cout << PORT << port << endl;
			cout << DOC << document << endl;
		}
		else
		{
			cout << INVALID_URL << endl;
		}
	}
	return 0;
}