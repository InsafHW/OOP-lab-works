#pragma once
class CPoint
{
private:
	double x;
	double y;
public:
	CPoint(double x, double y);
	void SetX(double x);
	void SetY(double y);
	double GetX() const;
	double GetY() const;
	bool operator ==(CPoint const& other) const;
};

