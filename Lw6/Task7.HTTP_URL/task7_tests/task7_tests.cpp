#define BOOST_TEST_MODULE urlParsingTest
#include <boost/test/included/unit_test.hpp>
#include <Windows.h>
#include "../Task7.HTTP_URL/CHttpUrl.h"
#include "../Task7.HTTP_URL/CUrlParsingException.h"

using namespace std;

BOOST_AUTO_TEST_CASE(empty_url_is_not_valid)
{
	cout << "---------------------------ChttpUrl(string url)--------------------------" << endl;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Пустая строка невалидный url - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl(""), CUrlParsingException);
}

BOOST_AUTO_TEST_CASE(url_with_wrong_protocol)
{
	cout << "Если протокол не http/https - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl("ftp://vk.com"), CUrlParsingException);
}

BOOST_AUTO_TEST_CASE(url_witout_protocol)
{
	cout << "Если протокол не указан, то будет HTTP" << endl;
	CHttpUrl url("vk.com");
	BOOST_CHECK(url.GetProtocolStr() == "http");
}


BOOST_AUTO_TEST_CASE(urls_with_incorrect_port)
{
	cout << "HTTP. Если порт меньше минимально допустимого - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl("http://vk.com:0"), CUrlParsingException);
	cout << "HTTPS. Если порт меньше минимально допустимого - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl("https://vk.com:0"), CUrlParsingException);
	cout << "HTTP. Если порт больше больше максимально допустимого - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl("http://vk.com:70000"), CUrlParsingException);
	cout << "HTTPS. Если порт больше больше максимально допустимого - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl("https://vk.com:70000"), CUrlParsingException);
	cout << "HTTP. Если порт содержит буквы - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl("http://vk.com:212word"), CUrlParsingException);
	cout << "HTTPS. Если порт содержит буквы - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl("https://vk.com:212word"), CUrlParsingException);
}


BOOST_AUTO_TEST_CASE(initializing_string_without_port)
{
	cout << "Если url без порта и протокол http - порт будет 80" << endl;
	const string httpStr = "http://vk.com";
	CHttpUrl httpUrl(httpStr);
	BOOST_CHECK(httpUrl.GetPort() == 80);
	cout << "Если url без порта и протокол https - порт будет 443" << endl;
	const string httpsStr = "https://vk.com";
	CHttpUrl httpsUrl(httpsStr);
	BOOST_CHECK(httpsUrl.GetPort() == 443);
}


BOOST_AUTO_TEST_CASE(initializing_string_without_document)
{
	const string httpStr = "http://vk.com";
	const string httpsStr = "https://vk.com";
	CHttpUrl httpUrl(httpStr);
	CHttpUrl httpsUrl(httpsStr);
	cout << "HTTP. Если url без документа, то он добавит /" << endl;
	BOOST_CHECK(httpUrl.GetUrl() == httpStr + "/");
	cout << httpUrl.GetDocument();
	BOOST_CHECK(httpUrl.GetDocument() == "/");
	BOOST_CHECK(httpUrl.GetPort() == 80);
	BOOST_CHECK(httpUrl.GetDomain() == "vk.com");
	BOOST_CHECK(httpUrl.GetProtocolStr() == "http");

	cout << "HTTPS. Если url без документа, то он добавит /" << endl;
	BOOST_CHECK(httpsUrl.GetUrl() == httpsStr + "/");
	BOOST_CHECK(httpsUrl.GetDocument() == "/");
	BOOST_CHECK(httpsUrl.GetPort() == 443);
	BOOST_CHECK(httpsUrl.GetDomain() == "vk.com");
	BOOST_CHECK(httpsUrl.GetProtocolStr() == "https");
}

BOOST_AUTO_TEST_CASE(initializng_string_domain_document_protocol)
{
	cout << "---------------------------CHttpUrl(string domain, string document, Protocol protocol = Protocol::HTTP);--------------------------" << endl;

	cout << "Инициализация с пустым доменом - выбросит ошибку" << endl;
	BOOST_CHECK_THROW(CHttpUrl url("", "news"), CUrlParsingException);
	cout << "Инициализация с доменом и документом. Протокол будет HTTP по дефолту" << endl;
	BOOST_CHECK_NO_THROW(CHttpUrl url("vk.com", "news"));
	CHttpUrl url("vk.com", "news");
	BOOST_CHECK(url.GetUrl() == "http://vk.com/news");
	BOOST_CHECK(url.GetDocument() == "/news");
	BOOST_CHECK(url.GetDomain() == "vk.com");
	BOOST_CHECK(url.GetProtocolStr() == "http");
	BOOST_CHECK(url.GetPort() == 80);

	cout << "Инициализация с доменом и документом, и протоколом HTTP" << endl;
	BOOST_CHECK_NO_THROW(CHttpUrl urlHttp("vk.com", "news", Protocol::HTTP));
	CHttpUrl urlHttp("vk.com", "news", Protocol::HTTP);
	BOOST_CHECK(urlHttp.GetUrl() == "http://vk.com/news");
	BOOST_CHECK(urlHttp.GetDocument() == "/news");
	BOOST_CHECK(urlHttp.GetDomain() == "vk.com");
	BOOST_CHECK(urlHttp.GetProtocolStr() == "http");
	BOOST_CHECK(urlHttp.GetPort() == 80);

	cout << "Инициализация с доменом и документом, и протоколом HTTPS" << endl;
	BOOST_CHECK_NO_THROW(CHttpUrl urlHttp("vk.com", "news", Protocol::HTTPS));
	CHttpUrl urlHttps("vk.com", "news", Protocol::HTTPS);
	BOOST_CHECK(urlHttps.GetUrl() == "https://vk.com/news");
	BOOST_CHECK(urlHttps.GetDocument() == "/news");
	BOOST_CHECK(urlHttps.GetDomain() == "vk.com");
	BOOST_CHECK(urlHttps.GetProtocolStr() == "https");
	BOOST_CHECK(urlHttps.GetPort() == 443);

	cout << "Если документ пустой, то добавит /" << endl;
	CHttpUrl url1("vk.com", "");
	BOOST_CHECK(url1.GetDocument() == "/");
	BOOST_CHECK(url1.GetDomain() == "vk.com");
	BOOST_CHECK(url1.GetPort() == 80);
	BOOST_CHECK(url1.GetProtocolStr() == "http");
	BOOST_CHECK(url1.GetUrl() == "http://vk.com/");
}

BOOST_AUTO_TEST_CASE(initializng_string_domain_document_protocol_port)
{
	cout << "---------------------------CHttpUrl(string domain, string document, Protocol protocol, unsigned short port);--------------------------" << endl;
	cout << "Инициализация с пустым доменом - выбросит ошибку" << endl;
	BOOST_CHECK_THROW(CHttpUrl url("", "news", Protocol::HTTP, 32), CUrlParsingException);
	BOOST_CHECK_THROW(CHttpUrl url("", "news", Protocol::HTTPS, 32), CUrlParsingException);
	cout << "Инициализция с недопустимым портом - выбросит исключение" << endl;
	BOOST_CHECK_THROW(CHttpUrl url("vk.com", "news", Protocol::HTTP, 0), CUrlParsingException);
	BOOST_CHECK_THROW(CHttpUrl url("vk.com", "news", Protocol::HTTPS, 0), CUrlParsingException);
	BOOST_CHECK_THROW(CHttpUrl url("vk.com", "news", Protocol::HTTP, 65900), CUrlParsingException);
	BOOST_CHECK_THROW(CHttpUrl url("vk.com", "news", Protocol::HTTPS, 65900), CUrlParsingException);

	cout << "Инициализация с HTTP" << endl;
	CHttpUrl httpUrl("vk.com", "news", Protocol::HTTP, 564);
	BOOST_CHECK(httpUrl.GetDocument() == "/news");
	BOOST_CHECK(httpUrl.GetDomain() == "vk.com");
	BOOST_CHECK(httpUrl.GetPort() == 564);
	BOOST_CHECK(httpUrl.GetProtocolStr() == "http");
	BOOST_CHECK(httpUrl.GetUrl() == "http://vk.com:564/news");
	cout << "Инициализация с HTTPS" << endl;
	CHttpUrl httpsUrl("vk.com", "news", Protocol::HTTPS, 564);
	BOOST_CHECK(httpsUrl.GetDocument() == "/news");
	BOOST_CHECK(httpsUrl.GetDomain() == "vk.com");
	BOOST_CHECK(httpsUrl.GetPort() == 564);
	BOOST_CHECK(httpsUrl.GetProtocolStr() == "https");
	BOOST_CHECK(httpsUrl.GetUrl() == "https://vk.com:564/news");

	cout << "Если документ пустой, то добавит /" << endl;
	CHttpUrl url1("vk.com", "", Protocol::HTTP, 382);
	BOOST_CHECK(url1.GetDocument() == "/");
	BOOST_CHECK(url1.GetDomain() == "vk.com");
	BOOST_CHECK(url1.GetPort() == 382);
	BOOST_CHECK(url1.GetProtocolStr() == "http");
	BOOST_CHECK(url1.GetUrl() == "http://vk.com:382/");
}

BOOST_AUTO_TEST_CASE(get_url)
{
	cout << "---------------------------GetUrl()--------------------------" << endl;
	cout << "Если порт стандартный, то он не включится в url" << endl;
	CHttpUrl url1("vk.com", "news", Protocol::HTTP);
	BOOST_CHECK(url1.GetUrl() == "http://vk.com/news");
	CHttpUrl url2("vk.com", "news", Protocol::HTTPS);
	BOOST_CHECK(url2.GetUrl() == "https://vk.com/news");
	cout << "Если порт не стандр., он включается в строковое представление" << endl;
	CHttpUrl url3("vk.com", "news", Protocol::HTTPS, 448);
	BOOST_CHECK(url3.GetUrl() == "https://vk.com:448/news");
}

BOOST_AUTO_TEST_CASE(get_domain)
{
	cout << "---------------------------GetDomain()--------------------------" << endl;
	cout << "Возвращает доменное имя" << endl;
	CHttpUrl url1("vk.com", "news", Protocol::HTTP);
	BOOST_CHECK(url1.GetDomain() == "vk.com");
}

BOOST_AUTO_TEST_CASE(get_document)
{
	cout << "---------------------------GetDocument()--------------------------" << endl;
	cout << "Если документ пустой, вернет /" << endl;
	CHttpUrl url1("vk.com", "", Protocol::HTTP);
	BOOST_CHECK(url1.GetDocument() == "/");
	cout << "Если документ не пустой, вернет документ" << endl;
	CHttpUrl url2("vk.com", "feed", Protocol::HTTP);
	cout << url2.GetDocument();
	BOOST_CHECK(url2.GetDocument() == "/feed");
}

BOOST_AUTO_TEST_CASE(get_protocol)
{
	cout << "---------------------------GetProtocol()--------------------------" << endl;
	cout << "Если протокол http, вернет http" << endl;
	CHttpUrl url1("vk.com", "", Protocol::HTTP);
	BOOST_CHECK(url1.GetProtocolStr() == "http");
	cout << "Если протокол https, вернет https" << endl;
	CHttpUrl url2("vk.com", "feed", Protocol::HTTPS);
	BOOST_CHECK(url2.GetProtocolStr() == "https");
}

BOOST_AUTO_TEST_CASE(get_port)
{
	cout << "---------------------------GetPort()--------------------------" << endl;
	cout << "Если порт не указан и протокол HTTP - вернет 80" << endl;
	CHttpUrl url1("vk.com", "", Protocol::HTTP);
	BOOST_CHECK(url1.GetPort() == 80);
	cout << "Если порт не указан и протокол HTTPS - вернет 443" << endl;
	CHttpUrl url2("vk.com", "", Protocol::HTTPS);
	BOOST_CHECK(url2.GetPort() == 443);
	cout << "Если порт не станд. вернет порт" << endl;
	CHttpUrl url3("vk.com", "", Protocol::HTTPS, 434);
	BOOST_CHECK(url3.GetPort() == 434);
}