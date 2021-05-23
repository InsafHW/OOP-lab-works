#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <math.h>
#define _USE_MATH_DEFINES

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius);
	CCircle(CPoint center, double radius, uint32_t outlineColor);
	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);
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
	uint32_t m_outlineColor = 0xFF0000;
	uint32_t m_fillColor = 0xFF0000;
	const double PI = 3.14;
};


