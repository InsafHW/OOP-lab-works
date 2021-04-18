#include "CCircle.h"

CCircle::CCircle(CPoint center, double radius)
	:m_center(center)
	, m_radius(radius)
{ }

double CCircle::GetArea() const
{
	return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * PI * m_radius;
}

string CCircle::ToString() const
{
	ostringstream outputStream;
	outputStream << "Фигура: окружность;" << endl;
	outputStream << "Координаты центра: (" << to_string(m_center.GetX()) << " ; " << to_string(m_center.GetY()) << ");" << endl;
	outputStream << "Радиус: " << to_string(m_radius) << ";" << endl;
	outputStream << "Площадь: " << to_string(GetArea()) << ";" << endl;
	outputStream << "Длина окружности: " << to_string(GetPerimeter()) << ";" << endl;
	outputStream << "Цвет обводки: " << setfill('0') << setw(8) << hex << m_outlineColor << ";" << endl;
	outputStream << "Цвет заливки: " << setfill('0') << setw(8) << hex << m_fillColor << ";" << endl;

	return outputStream.str();
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::SetCenter(CPoint center)
{
	m_center.SetX(center.GetX());
	m_center.SetY(center.GetY());
}

void CCircle::SetRadius(double radius)
{
	m_radius = radius;
}

void CCircle::SetOutlineColor(uint32_t newColor)
{
	m_outlineColor = newColor;
}

void CCircle::SetFillColor(uint32_t newColor)
{
	m_fillColor = newColor;
}
