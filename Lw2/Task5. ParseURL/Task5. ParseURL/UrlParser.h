#pragma once
#include <string>
#include <regex>
#include <iostream>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

using namespace std;
bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document);
