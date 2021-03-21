#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

TEST_CASE("Some test")
{
	REQUIRE(2 + 2 == 4);
}