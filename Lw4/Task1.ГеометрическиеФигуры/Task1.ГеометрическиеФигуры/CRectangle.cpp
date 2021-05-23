#include "CRectangle.h"

CRectangle::CRectangle(CPoint leftTop, double width, double height)
	:m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{ }

CRectangle::CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
{ }

CRectangle::CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{ }

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_height + m_width) * 2;
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

string CRectangle::ToString() const
{
	ostringstream outputStream;
	outputStream << "Фигура: прямоугольник;" << endl;
	outputStream << "Координаты левого верхнего угла: (" << to_string(m_leftTop.GetX()) << " ; " << to_string(m_leftTop.GetY()) << ");" << endl;
	outputStream << "Высота: " << to_string(m_height) << ";" << endl;
	outputStream << "Ширина: " << to_string(m_width) << ";" << endl;
	outputStream << "Координаты нижнего правого угла: (" << to_string(m_leftTop.GetX() + m_width) << " ; " << to_string(m_leftTop.GetY() + m_height) << ");" << endl;
	outputStream << "Площадь: " << to_string(GetArea()) << ";" << endl;
	outputStream << "Периметр: " << to_string(GetPerimeter()) << ";" << endl;
	outputStream << "Цвет обводки: " << setfill('0') << setw(8) << hex << m_outlineColor << ";" << endl;
	outputStream << "Цвет заливки: " << setfill('0') << setw(8) << hex << m_fillColor << ";" << endl;

	return outputStream.str();
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::SetLeftTop(CPoint leftTop)
{
	m_leftTop.SetX(leftTop.GetX());
	m_leftTop.SetY(leftTop.GetY());
}

void CRectangle::SetWidth(double width)
{
	m_width = width;
}

void CRectangle::SetHeight(double height)
{
	m_height = height;
}

void CRectangle::SetOutlineColor(uint32_t newColor)
{
	m_outlineColor = newColor;
}

void CRectangle::SetFillColor(uint32_t newColor)
{
	m_fillColor = newColor;
}
