#include "CPoint.h"

CPoint::CPoint(double x, double y)
{
	this->x = x;
	this->y = y;
}

void CPoint::SetX(double x)
{
	this->x = x;
}

void CPoint::SetY(double y)
{
	this->y = y;
}


double CPoint::GetX() const
{
	return x;
}

double CPoint::GetY() const
{
	return y;
}

bool CPoint::operator==(CPoint const& other) const
{
	return x == other.x && y == other.y;
}
