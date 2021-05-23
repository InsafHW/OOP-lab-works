#include "Sportsman.h"

Sportsman::Sportsman(string FIO, double height, double weight)
	:m_FIO(FIO),
	m_height(height),
	m_weight(weight)
{
}

double Sportsman::GetHeight() const
{
	return m_height;
}

double Sportsman::GetWeight() const
{
	return m_weight;
}

string Sportsman::GetFIO() const
{
	return m_FIO;
}
