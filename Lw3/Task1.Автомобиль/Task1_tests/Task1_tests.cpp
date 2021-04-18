#include <iostream>
#include <Windows.h>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"

#include "../Task1.Автомобиль/Car.h"


using namespace std;

// Тест включения двигателя
SCENARIO("Если двигатель уже включен, то вернется true")
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Если двигатель уже включен, то вернется true" << endl;
	Car car(true, 25, Gear::Fourth);
	REQUIRE(car.TurnOnEngine() == true);
}

SCENARIO("Если машина не на нетральной передаче, включить двигатель нельзя")
{
	cout << "Если машина не на нетральной передаче, включить двигатель нельзя." << endl;
	Car car1(false, 32, Gear::Back);
	Car car2(false, 32, Gear::First);
	Car car3(false, 32, Gear::Second);
	Car car4(false, 32, Gear::Third);
	Car car5(false, 32, Gear::Fourth);
	Car car6(false, 32, Gear::Fifth);

	REQUIRE(car1.TurnOnEngine() == false);
	REQUIRE(car2.TurnOnEngine() == false);
	REQUIRE(car3.TurnOnEngine() == false);
	REQUIRE(car4.TurnOnEngine() == false);
	REQUIRE(car5.TurnOnEngine() == false);
	REQUIRE(car6.TurnOnEngine() == false);
}