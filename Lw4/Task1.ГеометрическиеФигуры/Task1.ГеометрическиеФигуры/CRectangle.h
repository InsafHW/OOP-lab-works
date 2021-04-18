#pragma once
#include "ISolidShape.h"
#include "CPoint.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, double width, double height);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	string ToString() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void SetLeftTop(CPoint leftTop);
	void SetWidth(double width);
	void SetHeight(double height);
	void SetOutlineColor(uint32_t newColor);
	void SetFillColor(uint32_t newColor);
private:
	double m_width;
	double m_height;
	uint32_t m_outlineColor = 0xFF000000;
	uint32_t m_fillColor = 0xFF000000;
	CPoint m_leftTop;
};

