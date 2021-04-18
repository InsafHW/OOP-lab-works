#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius);
	double GetArea() const override;
	double GetPerimeter() const override;
	string ToString() const override;
	uint32_t GetOutlineColor() const;
	uint32_t GetFillColor() const;
	CPoint GetCenter() const;
	double GetRadius() const;
	void SetCenter(CPoint center);
	void SetRadius(double radius);
	void SetOutlineColor(uint32_t newColor);
	void SetFillColor(uint32_t newColor);
private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor = 0xFF000000;
	uint32_t m_fillColor = 0xFF000000;
	const double PI = 3.14;
};

