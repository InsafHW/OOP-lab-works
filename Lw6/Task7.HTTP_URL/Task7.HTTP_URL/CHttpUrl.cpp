#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string url)
{
	transform(url.begin(), url.end(), url.begin(), tolower);
	std::regex regularUrlParse(urlRegexRule, std::regex_constants::icase);
	std::smatch matches;
	if (!regex_match(url, matches, regularUrlParse))
	{
		throw CUrlParsingException(INVALID_URL);
	}

	try
	{
		int x = matches[0].str().find("http");
		if (x == -1)
		{
			m_url = "http://" + matches[0].str() + (matches[5].str().empty() ? "/" : "");
		}
		else
		{
			m_url = matches[0].str() + (matches[5].str().empty() ? "/" : "");
		}
		m_protocol = TryToParseProtocol(matches[2].str());
		if (matches[3].str().empty()) throw CUrlParsingException(EMPTY_DOMAIN);
		m_domain = matches[3].str();
		m_port = matches[4].str().empty() ? GetDefaultPort() : TryToParsePort(matches[4].str());
		m_document = matches[5].str();
	}
	catch (const CUrlParsingException& e)
	{
		throw e;
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	std::regex regularDomainParse(domainRegexRule);
	if (!regex_match(domain, regularDomainParse))
	{
		throw CUrlParsingException(INVALID_DOMAIN);
	}

	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	m_port = protocol == Protocol::HTTP ? HTTP_DEFAULT_PORT : HTTPS_DEFAULT_PORT;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, int port)
{
	std::regex regularDomainParse(domainRegexRule);
	if (!regex_match(domain, regularDomainParse))
	{
		throw CUrlParsingException(INVALID_DOMAIN);
	}

	m_domain = domain;
	m_document = document;
	m_protocol = protocol;
	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw CUrlParsingException(INVALID_PORT_RANGE);
	}
	m_port = port;
}

std::string CHttpUrl::GetUrl() const
{
	if (!m_url.empty()) return m_url;
	std::string url;
	url = m_protocol == Protocol::HTTP ? "http" : "https";
	url += "://";
	url += m_domain;
	url += ((m_port != HTTP_DEFAULT_PORT && m_port != HTTPS_DEFAULT_PORT) ? ":" + std::to_string(m_port) : "");
	url += "/" + m_document;

	return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document.empty() ? "/" : (m_document[0] == '/' ? m_document : "/" + m_document);
}

std::string CHttpUrl::GetProtocolStr() const
{
	return m_protocol == Protocol::HTTP ? "http" : "https";
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

unsigned short CHttpUrl::TryToParsePort(std::string port) const
{
	try
	{
		int tempIntPort = stoi(port.substr(1));
		if (tempIntPort < MIN_PORT || tempIntPort > MAX_PORT)
		{
			throw CUrlParsingException(INVALID_PORT_RANGE);
		}

		auto temp = static_cast<unsigned short>(tempIntPort);
		return temp;
	}
	catch (const std::exception& e)
	{
		throw CUrlParsingException(INVALID_PORT_CONTENT);
	}
}

Protocol CHttpUrl::TryToParseProtocol(std::string protocol) const
{
	if (protocol.empty() || protocol == "http") return Protocol::HTTP;
	if (protocol == "https") return Protocol::HTTPS;
	throw CUrlParsingException(INVALID_PROTOCOL_CONTENT);
}

unsigned short CHttpUrl::GetDefaultPort() const
{
	if (m_protocol == Protocol::HTTP) return HTTP_DEFAULT_PORT;
	if (m_protocol == Protocol::HTTPS) return HTTPS_DEFAULT_PORT;
	throw CUrlParsingException(INVALID_PROTOCOL_ACCORD);
}
