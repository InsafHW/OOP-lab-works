#include "CTriangle.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3)
	:m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{ }

double CTriangle::GetPerimeter() const
{
	double side12 = GetSide12();
	double side23 = GetSide23();
	double side31 = GetSide31();
	return side12 + side23 + side31;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::SetVertex1(CPoint vertex)
{
	m_vertex1.SetX(vertex.GetX());
	m_vertex1.SetY(vertex.GetY());
}

void CTriangle::SetVertex2(CPoint vertex)
{
	m_vertex2.SetX(vertex.GetX());
	m_vertex2.SetY(vertex.GetY());
}

void CTriangle::SetVertex3(CPoint vertex)
{
	m_vertex3.SetX(vertex.GetX());
	m_vertex3.SetY(vertex.GetY());
}

void CTriangle::SetFillColor(uint32_t newColor)
{
	m_fillColor = newColor;
}

void CTriangle::SetOutlineColor(uint32_t newColor)
{
	m_outlineColor = newColor;
}


double CTriangle::GetArea() const
{
	double half_perimeter = GetPerimeter() / 2;
	return sqrt(half_perimeter * (half_perimeter - GetSide12()) * (half_perimeter - GetSide23()) * (half_perimeter - GetSide31()));
}

double CTriangle::GetSide12() const
{
	return sqrt(pow(m_vertex2.GetX() - m_vertex1.GetX(), 2) + pow(m_vertex2.GetY() - m_vertex1.GetY(), 2));
}

double CTriangle::GetSide23() const
{
	return sqrt(pow(m_vertex3.GetX() - m_vertex2.GetX(), 2) + pow(m_vertex3.GetY() - m_vertex2.GetY(), 2));
}

double CTriangle::GetSide31() const
{
	return sqrt(pow(m_vertex3.GetX() - m_vertex1.GetX(), 2) + pow(m_vertex3.GetY() - m_vertex1.GetY(), 2));
}

string CTriangle::ToString() const
{
	ostringstream outputStream;
	outputStream << "Фигура: треугольник;" << endl;
	outputStream << "Координаты вершины 1: (" << to_string(m_vertex1.GetX()) << " ; " << to_string(m_vertex1.GetY()) << ");" << endl;
	outputStream << "Координаты вершины 2: (" << to_string(m_vertex2.GetX()) << " ; " << to_string(m_vertex2.GetY()) << ");" << endl;
	outputStream << "Координаты вершины 3: (" << to_string(m_vertex3.GetX()) << " ; " << to_string(m_vertex3.GetY()) << ");" << endl;
	outputStream << "Площадь: " << to_string(GetArea()) << ";" << endl;
	outputStream << "Периметр: " << to_string(GetPerimeter()) << ";" << endl;
	outputStream << "Цвет обводки: " << setfill('0') << setw(8) << hex << m_outlineColor << ";" << endl;
	outputStream << "Цвет заливки: " << setfill('0') << setw(8) << hex << m_fillColor << ";" << endl;

	return outputStream.str();
}
