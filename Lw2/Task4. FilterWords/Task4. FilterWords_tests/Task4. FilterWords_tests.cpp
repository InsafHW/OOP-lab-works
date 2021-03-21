#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Task4. FilterWords/Filter.h"

std::set<std::string> filter = { "hell", "fool" };

SCENARIO("Filter empty string gives empty string")
{
	REQUIRE(Filter("", filter).empty());
}

SCENARIO("Filter with word that is prohibited")
{
	REQUIRE(Filter("hell", filter).empty());
}

SCENARIO("Filter with one prohibited and the rest are not")
{
	REQUIRE(Filter("what the hell is it", filter) == "what the is it");
}

SCENARIO("Filter Lines")
{
	std::ostringstream output;
	WHEN("Input stream is empty")
	{
		std::istringstream input("");
		THEN("output stream is also empty")
		{
			FilterLines(input, output, filter);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}

	WHEN("Input stream has prohibited word it's erased")
	{
		std::istringstream input("Here goes a prohibited word hell");
		THEN("output stream is also empty")
		{
			FilterLines(input, output, filter);
			CHECK(output.str() == "Here goes a prohibited word");
			CHECK(input.eof());
		}
	}

	WHEN("Input stream contains several lines with prohibited words")
	{
		std::istringstream input("1 line with hell\n2 line with fool and it's erased");
		THEN("output stream has no prohibited words")
		{
			FilterLines(input, output, filter);
			CHECK(output.str() == "1 line with\n2 line with and it's erased");
			CHECK(input.eof());
		}
	}
}