#pragma once
#include "CUrlParsingException.h"
#include <string>
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS
};

const std::string urlRegexRule = "^((https?)://)?([0-9a-zA-Z�.-]*)(:[0-9]+)?(/[a-zA-Z�.-?&]*)*/?$";
const std::string domainRegexRule = "(.+).([a-z]+)";

const int MIN_PORT = 1;
const int MAX_PORT = 65536;
const int HTTP_DEFAULT_PORT = 80;
const int HTTPS_DEFAULT_PORT = 443;
const std::string INVALID_URL = "������������ url. ������ ���� ��������(http/https)?://�����:����(" + std::to_string(MIN_PORT) + "-" + std::to_string(MAX_PORT) + ")?/��������?";
const std::string EMPTY_DOMAIN = "�� ������ �����";
const std::string INVALID_DOMAIN = "������������ �����. ������ ���� [a-z, 0-9].[a-z]";
const std::string INVALID_PORT_RANGE = "������������ ����, ������ ���� � ��������" + std::to_string(MIN_PORT) + " - " + std::to_string(MAX_PORT);
const std::string INVALID_PORT_CONTENT = "������������ ����. ������ ��������� ������ �����.";
const std::string INVALID_PROTOCOL_CONTENT = "�� ������������ ���������� ���������� http/https";
const std::string INVALID_PROTOCOL_ACCORD = "��� ����������� ������� �����.";

class CHttpUrl
{
public:
	CHttpUrl(std::string url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = Protocol::HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, int port);
	std::string GetUrl() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	std::string GetProtocolStr() const;
	unsigned short GetPort() const;
private:
	unsigned short TryToParsePort(std::string port) const;
	Protocol TryToParseProtocol(std::string protocol) const;
	unsigned short GetDefaultPort() const;

	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};