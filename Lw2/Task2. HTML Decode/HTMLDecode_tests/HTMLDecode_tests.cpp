#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Task2. HTML Decode/Decode.h"

SCENARIO("Decode of empty string gives empty string")
{
	REQUIRE(Decode("").empty());
}

SCENARIO("Decode string without encoded words gives the same string")
{
	REQUIRE(Decode("abcd") == "abcd");
}

SCENARIO("Decode of &quot; gives \"")
{
	REQUIRE(Decode("&quot;") == "\"");
}

SCENARIO("Decode of &apos; gives \"")
{
	REQUIRE(Decode("&apos;") == "'");
}

SCENARIO("Decode of &lt; gives <")
{
	REQUIRE(Decode("&lt;") == "<");
}

SCENARIO("Decode of &gt; gives >")
{
	REQUIRE(Decode("&gt;") == ">");
}

SCENARIO("Decode of &amp; gives &")
{
	REQUIRE(Decode("&amp;") == "&");
}

SCENARIO("Decode reserved word with simple word gives uncoded reserved and the rest of the string")
{
	REQUIRE(Decode("M&apos;m &amp; S") == "M\'m & S");
}

SCENARIO("Decode Lines")
{
	std::ostringstream output;
	WHEN("Input stream is empty")
	{
		std::istringstream input("");
		THEN("output stream is also empty")
		{
			DecodeLines(input, output);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}

	WHEN("Input stream has &quot; or &apos; or &lt; or &gt; or &amp; it decodes it")
	{
		std::istringstream input("&quot;&apos;&lt;&gt;&amp;");
		THEN("output stream is decoded")
		{
			DecodeLines(input, output);
			CHECK(output.str() == "\"'<>&");
			CHECK(input.eof());
		}
	}

	WHEN("Input stream has encoded word with simple words it gives decoded reserved and the rest of the string")
	{
		std::istringstream input("I&apos;m a person");
		THEN("encoded words are decoded")
		{
			DecodeLines(input, output);
			CHECK(output.str() == "I'm a person");
			CHECK(input.eof());
		}
	}

	WHEN("Input stream contains several with encoded words")
	{
		std::istringstream input("1 line with &amp;\n2 line with M&amp;M&apos;s");
		THEN("output stream contains reversed line")
		{
			DecodeLines(input, output);
			CHECK(output.str() == "1 line with &\n2 line with M&M's");
			CHECK(input.eof());
		}
	}
}
