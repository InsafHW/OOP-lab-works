#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Task5. ParseURL//UrlParser.h"

SCENARIO("Пустая строка - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Пустая строка - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("", pr, port, host, document) == false);
}

SCENARIO("Только цифры - невалидный url")

{
	setlocale(LC_ALL, "ru");
	cout << "Только цифры - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("32532523523", pr, port, host, document) == false);
}

SCENARIO("Только буквы - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Только буквы - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("gewghwrherhwth", pr, port, host, document) == false);
}

SCENARIO("Только символы - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Только символы - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("*&/!@", pr, port, host, document) == false);
}

SCENARIO("Если есть :, но порт не указан - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Если есть :, но порт не указан - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("http://www.mysite.com:/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == false);
}

SCENARIO("Если порт меньше 1 - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Если порт меньше 1 - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == false);
}

SCENARIO("Если порт больше 65535 - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Если порт больше 65535 - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("http://www.mysite.com:655356/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == false);
}

SCENARIO("Если хост - пустой, то - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Если хост - пустой, то - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("http://:23/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == false);
}

SCENARIO("Если протокол отличен от http | https | ftp - невалидный url")
{
	setlocale(LC_ALL, "ru");
	cout << "Если протокол отличен от http | https | ftp - невалидный url" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("hrte://www.mysite.com:655356/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == false);
}

SCENARIO("Если порт не указан и протокол = http, то порт - 80")
{
	setlocale(LC_ALL, "ru");
	cout << "Если порт не указан и протокол = http, то порт - 80" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == true);
	REQUIRE(port == 80);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Если порт не указан и протокол = https, то порт - 443")
{
	setlocale(LC_ALL, "ru");
	cout << "Если порт не указан и протокол = https, то порт - 443" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("https://www.mysite.com/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == true);
	REQUIRE(port == 443);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Если порт не указан и протокол = ftp, то порт - 21")
{
	setlocale(LC_ALL, "ru");
	cout << "Если порт не указан и протокол = 21, то порт - 21" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title", pr, port, host, document) == true);
	REQUIRE(port == 21);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
}

SCENARIO("Если не указан документ, то он будет пустой строкой")
{
	setlocale(LC_ALL, "ru");
	cout << "Если не указан документ, то он будет пустой строкой" << endl;
	Protocol pr;
	int port;
	string host, document;
	REQUIRE(ParseURL("ftp://www.mysite.com", pr, port, host, document) == true);
	REQUIRE(port == 21);
	REQUIRE(host == "www.mysite.com");
	REQUIRE(document == "");
}