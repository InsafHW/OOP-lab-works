#pragma once
#include <stdexcept>
#include <string>

class CUrlParsingException : public std::invalid_argument
{
public:
	CUrlParsingException(const std::string& message)
		:invalid_argument(message)
	{};
};

