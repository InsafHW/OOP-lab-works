#include "Car.h"

Car::Car(bool isEngineTurned, int currentSpeed, Gear currentGear)
{
	m_isEngineTurned = isEngineTurned;
	m_currentSpeed = currentSpeed;
	m_currentGear = currentGear;

	if (currentSpeed == 0)
	{
		m_currentDirection = Direction::Stop;
	}

	switch (currentGear)
	{
	case Gear::Back:
		m_currentDirection = Direction::Back;
		if (currentSpeed < MIN_BACK_GEAR_SPEED)
		{
			m_currentSpeed = MIN_BACK_GEAR_SPEED;
		}
		else if (currentSpeed > MAX_BACK_GEAR_SPEED)
		{
			m_currentSpeed = MAX_BACK_GEAR_SPEED;
		}
		else
		{
			m_currentSpeed = currentSpeed;
		}
		break;
	case Gear::Neutral:

	default:
		break;
	}

	if (currentGer == Gear::Back)
	{
		if (currentSpeed < MIN_BACK_GEAR_SPEED)
		{
			m_currentSpeed = MIN_BACK_GEAR_SPEED;
		}
	}
}

bool Car::TurnOnEngine()
{
	if (m_isEngineTurned) return true;

	if (m_currentGear != Gear::Neutral || m_currentSpeed != 0)
	{
		return false;
	}

	m_isEngineTurned = true;
	m_currentDirection = Direction::Stop;
	m_currentSpeed = 0;
	m_currentGear = Gear::Neutral;

	return true;
}

bool Car::TurnOffEngine()
{
	if (!m_isEngineTurned) return true;

	if (m_currentGear != Gear::Neutral || m_currentSpeed != 0)
	{
		return false;
	}

	m_isEngineTurned = false;
	return true;
}

bool Car::SetGear(Gear gear)
{
	switch (gear)
	{

	case Gear::Back:
		if (m_currentSpeed != 0 || !m_isEngineTurned)
		{
			return false;
		}
		m_currentDirection = Direction::Back;
		m_currentGear = Gear::Back;
		return true;

	case Gear::Neutral:
		if (!m_isEngineTurned)
		{
			return false;
		}

		m_currentGear = Gear::Neutral;
		return true;
	case Gear::First:
		if (!m_isEngineTurned)
		{
			return false;
		}

		return true;
	case Gear::Second:
		break;
	case Gear::Third:
		break;
	case Gear::Fourth:
		break;
	case Gear::Fifth:
		break;
	default:
		break;
	}
	return false;
}

bool Car::SetSpeed(int speed)
{
	return false;
}
