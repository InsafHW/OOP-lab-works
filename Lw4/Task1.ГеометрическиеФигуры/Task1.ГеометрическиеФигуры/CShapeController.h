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
const string MISSING_REQUIRED_LINE_PARAMS = "Ќе введены об€зательные параметры фигуры типа line: началоX(double) началоY(double) конецX(double конецY(double) ?цветќбводки(hex)";
const string MISSING_REQUIRED_TRIANGLE_PARAMS = "Ќе введены об€зательные параметры фигуры типа triangle: верш1X(double) верш1Y(double) верш2X(double) верш2Y(double) верш3X(double) верш3Y(double) цветќбводки(hex) ?цвет«аливки(hex)";
const string MISSING_REQUIRED_RECTANGLE_PARAMS = "Ќе введены об€зательные параметры фигуры типа rectangle: rectangle левый¬ерхний”голX(double) левый¬ерхний”голY(double) ширина(double) высота(double) ?цветќбводки(hex) ?цвет«аливки(hex)";
const string MISSING_REQUIRED_CIRCLE_PARAMS = "Ќе введены об€зательные параметры фигуры типа circle: центрX(double) центрY(double) радиус(double) ?цветќбводки(hex) ?цвет«аливки(hex)";

const string THERE_IS_NO_THAT_TYPE_OF_FIGURE = "Ќет фигуры с таким типом!";
const string FIGURE_WITH_MAX_AREA = "‘игура с максимальной площадью: ";
const string FIGURE_WITH_MIN_PERIMETR = "‘игура с минимальным периметром: ";
const string INVALID_PARAMETR = "Ќеккоректный ввод";
const string USAGE_RECTANGLE_TYPE = "rectangle левый¬ерхний”голX(double) левый¬ерхний”голY(double) ширина(double) высота(double) цветќбводки(hex) цвет«аливки(hex)";
const string USAGE_LINE_TYPE = "line началоX(double) началоY(double) конецX(double конецY(double) цветќбводки(hex)";
const string USAGE_TRIANGLE_TYPE = "triangle верш1X(double) верш1Y(double) верш2X(double) верш2Y(double) верш3X(double) верш3Y(double) цветќбводки(hex) цвет«аливки(hex)";
const string USAGE_CIRCLE_TYPE = "circle центрX(double) центрY(double) радиус(double) цветќбводки(hex) цвет«аливки(hex)";
const string THERE_IS_NO_SHAPES = "Ќет фигур";

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

