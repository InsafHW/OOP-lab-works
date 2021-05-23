#include <iostream>
#include <string>
#include "CHttpUrl.h"
#include <Windows.h>

using namespace std;

const string URL = "URL: ";
const string PROTOCOL = "PROTOCOL: ";
const string DOMAIN_ = "DOMAIN: ";
const string PORT = "PORT: ";
const string DOCUMENT = "DOCUMENT: ";


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string line;
	cout << "Enter url: ";
	while (getline(cin, line))
	{
		if (line.empty()) break;
		try
		{
			CHttpUrl url(line);
			cout << endl << URL << url.GetUrl() << endl;
			cout << PROTOCOL << url.GetProtocolStr() << endl;
			cout << DOMAIN_ << url.GetDomain() << endl;
			cout << PORT << url.GetPort() << endl;
			cout << DOCUMENT << url.GetDocument() << endl << endl;
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
		cout << "Enter url: ";
	}

	cout << "Exiting..." << endl;
}
