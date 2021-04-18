#pragma once
#include "ISolidShape.h"
#include <sstream>
#include <iomanip>
#include <cstdint>
#include "CPoint.h"
class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3);
	double GetArea() const override;
	double GetPerimeter() const override;
	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void SetVertex1(CPoint vertex);
	void SetVertex2(CPoint vertex);
	void SetVertex3(CPoint vertex);
	void SetFillColor(uint32_t newColor);
	void SetOutlineColor(uint32_t newColor);
	double GetSide12() const;
	double GetSide23() const;
	double GetSide31() const;
	string ToString() const override;
private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	uint32_t m_outlineColor = 0xFF000000;
	uint32_t m_fillColor = 0xFF000000;
};

