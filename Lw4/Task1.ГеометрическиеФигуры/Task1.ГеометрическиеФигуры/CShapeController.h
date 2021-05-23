#pragma once
#include <istream>
#include <vector>
#include <string>
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include <iostream>
#include <algorithm>
#include "CCircle.h"

using namespace std;

const int HEX_COLOR_LENGTH = 6;
const string MISSING_REQUIRED_LINE_PARAMS = "�� ������� ������������ ��������� ������ ���� line: ������X(double) ������Y(double) �����X(double �����Y(double) ?�����������(hex)";
const string MISSING_REQUIRED_TRIANGLE_PARAMS = "�� ������� ������������ ��������� ������ ���� triangle: ����1X(double) ����1Y(double) ����2X(double) ����2Y(double) ����3X(double) ����3Y(double) �����������(hex) ?�����������(hex)";
const string MISSING_REQUIRED_RECTANGLE_PARAMS = "�� ������� ������������ ��������� ������ ���� rectangle: rectangle ����������������X(double) ����������������Y(double) ������(double) ������(double) ?�����������(hex) ?�����������(hex)";
const string MISSING_REQUIRED_CIRCLE_PARAMS = "�� ������� ������������ ��������� ������ ���� circle: �����X(double) �����Y(double) ������(double) ?�����������(hex) ?�����������(hex)";

const string THERE_IS_NO_THAT_TYPE_OF_FIGURE = "��� ������ � ����� �����!";
const string FIGURE_WITH_MAX_AREA = "������ � ������������ ��������: ";
const string FIGURE_WITH_MIN_PERIMETR = "������ � ����������� ����������: ";
const string INVALID_PARAMETR = "������������ ����";
const string USAGE_RECTANGLE_TYPE = "rectangle ����������������X(double) ����������������Y(double) ������(double) ������(double) �����������(hex) �����������(hex)";
const string USAGE_LINE_TYPE = "line ������X(double) ������Y(double) �����X(double �����Y(double) �����������(hex)";
const string USAGE_TRIANGLE_TYPE = "triangle ����1X(double) ����1Y(double) ����2X(double) ����2Y(double) ����3X(double) ����3Y(double) �����������(hex) �����������(hex)";
const string USAGE_CIRCLE_TYPE = "circle �����X(double) �����Y(double) ������(double) �����������(hex) �����������(hex)";
const string THERE_IS_NO_SHAPES = "��� �����";

class CShapeController
{
public:
	CShapeController(ostream& output);
	IShape* GetLastShape() const;
	bool ReadShape(string line);
	void WriteInfos() const;
	void GetMaxSquareInfo() const;
	void GetMinPerimeterInfo() const;
private:
	bool ParseLine(istream& input);
	bool ParseTriangle(istream& input);
	bool ParseRectangle(istream& input);
	bool ParseCircle(istream& input);
	bool is_number(const string& s) const;
	bool is_valid_hex(const string& s) const;

	vector<IShape*> m_shapes;
	ostream& m_output;
};

