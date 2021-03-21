#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../StringReverser/Reverse.h"

SCENARIO("Reverse of empty string gives empty string")
{
	REQUIRE(Reverse("").empty());
}

SCENARIO("Reverse of single character string gives the same character")
{
	REQUIRE(Reverse("a") == "a");
}


SCENARIO("Reverse of string with length more than 1 character")
{
	REQUIRE(Reverse("1234") == "4321");
}

SCENARIO("ReverseLines")
{
	std::ostringstream output;
	WHEN("Input stream is empty")
	{
		std::istringstream input("");
		THEN("output stream is also empty")
		{
			ReverseLines(input, output);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}

	WHEN("Input stream has one line")
	{
		std::istringstream input("1 line");
		THEN("output stream contains reversed line")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1");
			CHECK(input.eof());
		}
	}

	WHEN("Input stream contains several")
	{
		std::istringstream input("1 line\n2 line");
		THEN("output stream contains reversed line")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1\nenil 2");
			CHECK(input.eof());
		}
	}

	WHEN("Input stream contains several EOL in the end")
	{
		std::istringstream input("1 line\n2 line\n");
		THEN("output stream contains EOL as well")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1\nenil 2\n");
			CHECK(input.eof());
		}
	}
}