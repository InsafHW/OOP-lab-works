#include "CLineSegment.h"

using namespace std;

CLineSegment::CLineSegment(CPoint start, CPoint end)
	:m_startPoint(start)
	, m_endPoint(end)
{ }

CLineSegment::CLineSegment(CPoint start, CPoint end, uint32_t color)
	: m_startPoint(start)
	, m_endPoint(end)
	, m_outlineColor(color)
{ }

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.GetX() - m_endPoint.GetX(), 2) + pow(m_startPoint.GetY() - m_endPoint.GetY(), 2));
}

string CLineSegment::ToString() const
{
	ostringstream outputStream;
	outputStream << "Фигура: отрезок;" << endl;
	outputStream << "Начальные координаты: (" << to_string(m_startPoint.GetX()) << " ; " << to_string(m_startPoint.GetY()) << ");" << endl;
	outputStream << "Конечные координаты: (" << to_string(m_endPoint.GetX()) << " ; " << to_string(m_endPoint.GetY()) << ");" << endl;
	outputStream << "Площадь: " << to_string(GetArea()) << ";" << endl;
	outputStream << "Периметр: " << to_string(GetPerimeter()) << ";" << endl;
	outputStream << "Цвет обводки: " << setfill('0') << setw(8) << hex << m_outlineColor << endl;

	return outputStream.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void CLineSegment::SetStartPoint(CPoint newStartPoint)
{
	m_startPoint.SetX(newStartPoint.GetX());
	m_startPoint.SetY(newStartPoint.GetY());
}

void CLineSegment::SetEndPoint(CPoint newEndPoint)
{
	m_endPoint.SetX(newEndPoint.GetX());
	m_endPoint.SetY(newEndPoint.GetY());
}

void CLineSegment::SetOutlineColor(uint32_t newColor)
{
	m_outlineColor = newColor;
}
