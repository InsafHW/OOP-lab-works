#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Task1/Matrix.h"


SCENARIO("ReadNumbers test")
{
	REQUIRE(ReadNumbers("1.000 2.000 3.2") == std::vector<double>{1.000, 2.000, 3.200});
}

SCENARIO("Empty input gives empty string")
{
	std::vector<double> numbers;
	REQUIRE(CalculateNumbers(numbers) == numbers);
}