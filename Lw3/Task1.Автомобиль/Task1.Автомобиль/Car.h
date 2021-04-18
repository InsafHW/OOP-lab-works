#pragma once
const int MIN_BACK_GEAR_SPEED = 0;
const int MAX_BACK_GEAR_SPEED = 20;

const int MIN_FIRST_GEAR_SPEED = 0;
const int MAX_FIRST_GEAR_SPEED = 30;

const int MIN_SECOND_GEAR_SPEED = 20;
const int MAX_SECOND_GEAR_SPEED = 50;

const int MIN_THIRD_GEAR_SPEED = 30;
const int MAX_THIRD_GEAR_SPEED = 60;

const int MIN_FOURTH_GEAR_SPEED = 40;
const int MAX_FOURTH_GEAR_SPEED = 90;

const int MIN_FIFTH_GEAR_SPEED = 50;
const int MAX_FIFTH_GEAR_SPEED = 150;

enum class Direction
{
	Back = -1,
	Stop,
	Forward
};

enum class Gear
{
	Back = -1,
	Neutral,
	First,
	Second,
	Third,
	Fourth,
	Fifth
};

class Car
{
private:
	bool m_isEngineTurned = false;
	Direction m_currentDirection = Direction::Stop;
	int m_currentSpeed = 0;
	Gear m_currentGear = Gear::Neutral;
public:
	Car(bool isEngineTurned, int currentSpeed, Gear currentGer);
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);
};

