#include "CShapeController.h"
#include "CPoint.h"
#include "CLineSegment.h"

using namespace std;

CShapeController::CShapeController(ostream& output)
	:m_output(output)
{ }

IShape* CShapeController::GetLastShape() const
{
	if (m_shapes.size() > 0)
	{
		return m_shapes.back();
	}
	return nullptr;
}

bool CShapeController::ParseLine(istream& input)
{
	string startXStr, startYStr, endXStr, endYStr, outlineColorStr;
	input >> startXStr >> startYStr >> endXStr >> endYStr >> outlineColorStr;

	if (startXStr.empty() || startYStr.empty() || endXStr.empty() || endYStr.empty())
	{
		m_output << MISSING_REQUIRED_LINE_PARAMS << endl;
		return false;
	}

	bool isStartXStrNumber = is_number(startXStr);
	bool isStartYStrNumber = is_number(startYStr);
	bool isEndXStrNumber = is_number(endXStr);
	bool isEndYStrNumber = is_number(endYStr);
	bool isInvalidHex = (!outlineColorStr.empty() && !is_valid_hex(outlineColorStr));

	if (!isStartXStrNumber) m_output << "startX должен быть double; ";
	if (!isStartYStrNumber) m_output << "startY должен быть double; ";
	if (!isEndXStrNumber) m_output << "endX должен быть double; ";
	if (!isEndYStrNumber) m_output << "endY должен быть double; ";
	if (isInvalidHex) m_output << "цвет обводки должены быть hex";

	if (!isStartXStrNumber || !isStartYStrNumber || !isEndXStrNumber || !isEndYStrNumber || isInvalidHex)
	{
		m_output << endl << INVALID_PARAMETR << ": " << USAGE_LINE_TYPE << endl;
		return false;
	}

	CPoint start = { stod(startXStr), stod(startYStr) };
	CPoint end = { stod(endXStr), stod(endYStr) };

	if (!outlineColorStr.empty())
	{
		uint32_t outlineColor = stoul(outlineColorStr, nullptr, 16);
		m_shapes.push_back(new CLineSegment(start, end, outlineColor));
	}
	else
	{
		m_shapes.push_back(new CLineSegment(start, end));
	}

	return true;
}

bool CShapeController::ParseTriangle(istream& input)
{
	string v1XStr, v1YStr, v2XStr, v2YStr, v3XStr, v3YStr, outlineColorStr, fillColorStr;
	input >> v1XStr >> v1YStr >> v2XStr >> v2YStr >> v3XStr >> v3YStr >> outlineColorStr >> fillColorStr;

	if (v1XStr.empty() || v1YStr.empty() || v2XStr.empty() || v2YStr.empty() || v3XStr.empty() || v3YStr.empty())
	{

		m_output << MISSING_REQUIRED_TRIANGLE_PARAMS << endl;
		return false;
	}

	bool isV1XStrNumber = is_number(v1XStr);
	bool isV1YStrNumber = is_number(v1YStr);
	bool isV2XStrNumber = is_number(v2XStr);
	bool isV2YStrNumber = is_number(v2YStr);
	bool isV3XStrNumber = is_number(v3XStr);
	bool isV3YStrNumber = is_number(v3YStr);
	bool isOutlineColorInvalid = !outlineColorStr.empty() && !is_valid_hex(outlineColorStr);
	bool isFillColorInvalied = !fillColorStr.empty() && !is_valid_hex(fillColorStr);

	if (!isV1XStrNumber) m_output << "верш1X должен быть double; ";
	if (!isV1YStrNumber) m_output << "верш1Y должен быть double; ";
	if (!isV2XStrNumber) m_output << "верш2X должен быть double; ";
	if (!isV2YStrNumber) m_output << "верш2Y должен быть double; ";
	if (!isV3XStrNumber) m_output << "верш3X должен быть double; ";
	if (!isV3YStrNumber) m_output << "верш3Y должен быть double; ";
	if (isOutlineColorInvalid) m_output << "цвет обводки должен быть hex; ";
	if (isFillColorInvalied) m_output << "цыет заливки должен быть hex; ";

	if (!isV1XStrNumber || !isV1YStrNumber || !isV2XStrNumber || !isV2YStrNumber || !isV3XStrNumber || !isV3YStrNumber || isOutlineColorInvalid || isFillColorInvalied)
	{
		m_output << endl << INVALID_PARAMETR << ": " << USAGE_TRIANGLE_TYPE << endl;
		return false;
	}

	CPoint v1 = { stod(v1XStr), stod(v1YStr) };
	CPoint v2 = { stod(v2XStr), stod(v2YStr) };
	CPoint v3 = { stod(v3XStr), stod(v3YStr) };

	if (!outlineColorStr.empty() && !fillColorStr.empty())
	{
		uint32_t outlineColor = stoul(outlineColorStr, nullptr, 16);
		uint32_t fillColor = stoul(fillColorStr, nullptr, 16);
		m_shapes.push_back(new CTriangle(v1, v2, v3, outlineColor, fillColor));
	}
	else if (!outlineColorStr.empty() && fillColorStr.empty())
	{
		uint32_t outlineColor = stoul(outlineColorStr, nullptr, 16);
		m_shapes.push_back(new CTriangle(v1, v2, v3, outlineColor));

	}
	else if (outlineColorStr.empty() && fillColorStr.empty())
	{
		m_shapes.push_back(new CTriangle(v1, v2, v3));
	}

	return true;
}

bool CShapeController::ParseRectangle(istream& input)
{
	string topLeftXStr, topLeftYStr, widthStr, heightStr, outlineColorStr, fillColorStr;
	input >> topLeftXStr >> topLeftYStr >> widthStr >> heightStr >> outlineColorStr >> fillColorStr;

	if (topLeftXStr.empty() || topLeftYStr.empty() || widthStr.empty() || heightStr.empty())
	{
		m_output << MISSING_REQUIRED_RECTANGLE_PARAMS << endl;
		return false;
	}

	bool isTopLeftXStrNumber = is_number(topLeftXStr);
	bool isTopLeftYStrNumber = is_number(topLeftYStr);
	bool isWidthInvalid = !is_number(widthStr) || (is_number(widthStr) && stod(widthStr) <= 0);
	bool isHeightInvalid = !is_number(heightStr) || (is_number(heightStr) && stod(heightStr) <= 0);
	bool isOutlineColorInvalid = !outlineColorStr.empty() && !is_valid_hex(outlineColorStr);
	bool isFillColorInvalid = !fillColorStr.empty() && !is_valid_hex(fillColorStr);

	if (!isTopLeftXStrNumber) m_output << "левый¬ерхний”голX должен быть double; ";
	if (!isTopLeftYStrNumber) m_output << "левый¬ерхний”голY должен быть double; ";
	if (isWidthInvalid) m_output << "ширина должна быть double > 0; ";
	if (isHeightInvalid) m_output << "высота должна быть double > 0; ";
	if (isOutlineColorInvalid) m_output << "цвет обводки должен быть hex; ";
	if (isFillColorInvalid) m_output << "цвет заливки должен быть hex; ";

	if (!isTopLeftXStrNumber || !isTopLeftYStrNumber || isWidthInvalid || isHeightInvalid || isOutlineColorInvalid || isFillColorInvalid)
	{
		m_output << endl << INVALID_PARAMETR << ": " << USAGE_RECTANGLE_TYPE << endl;
		return false;
	}

	CPoint topLeft = { stod(topLeftXStr), stod(topLeftYStr) };
	long double width = stod(widthStr);
	long double height = stod(heightStr);

	if (!outlineColorStr.empty() && !fillColorStr.empty())
	{
		uint32_t outlineColor = stoul(outlineColorStr, nullptr, 16);
		uint32_t fillColor = stoul(fillColorStr, nullptr, 16);
		m_shapes.push_back(new CRectangle(topLeft, width, height, outlineColor, fillColor));
	}
	else if (!outlineColorStr.empty() && fillColorStr.empty())
	{
		uint32_t outlineColor = stoul(outlineColorStr, nullptr, 16);
		m_shapes.push_back(new CRectangle(topLeft, width, height, outlineColor));

	}
	else if (outlineColorStr.empty() && fillColorStr.empty())
	{
		m_shapes.push_back(new CRectangle(topLeft, width, height));
	}

	return true;
}

bool CShapeController::ParseCircle(istream& input)
{
	string centerXStr, centerYStr, radiusStr, outlineColorStr, fillColorStr;
	input >> centerXStr >> centerYStr >> radiusStr >> outlineColorStr >> fillColorStr;

	if (centerXStr.empty() || centerYStr.empty() || radiusStr.empty())
	{
		m_output << MISSING_REQUIRED_CIRCLE_PARAMS << endl;
		return false;
	}

	bool isCenterXStrNumber = is_number(centerXStr);
	bool isCenterYStrNumber = is_number(centerYStr);
	bool isRadiusInvalid = !is_number(radiusStr) || (is_number(radiusStr) && stod(radiusStr) <= 0);
	bool isOutlineColorInvalid = !outlineColorStr.empty() && !is_valid_hex(outlineColorStr);
	bool isFillColorInvalid = !fillColorStr.empty() && !is_valid_hex(fillColorStr);

	if (!isCenterXStrNumber) m_output << "центрX должен быть double; ";
	if (!isCenterYStrNumber) m_output << "центрY должен быть double; ";
	if (isRadiusInvalid) m_output << "радиус должен быть double > 0; ";
	if (isOutlineColorInvalid) m_output << "цвет обводки должен быть hex; ";
	if (isFillColorInvalid) m_output << "цвет заливки должен быть hex; ";

	if (!isCenterXStrNumber || !isCenterYStrNumber || isRadiusInvalid || isOutlineColorInvalid || isFillColorInvalid)
	{
		m_output << INVALID_PARAMETR << ": " << USAGE_CIRCLE_TYPE << endl;
		return false;
	}

	CPoint center = { stod(centerXStr), stod(centerYStr) };
	long double radius = stod(radiusStr);

	if (!outlineColorStr.empty() && !fillColorStr.empty())
	{
		uint32_t outlineColor = stoul(outlineColorStr, nullptr, 16);
		uint32_t fillColor = stoul(fillColorStr, nullptr, 16);
		m_shapes.push_back(new CCircle(center, radius, outlineColor, fillColor));
	}
	else if (!outlineColorStr.empty() && fillColorStr.empty())
	{
		uint32_t outlineColor = stoul(outlineColorStr, nullptr, 16);
		m_shapes.push_back(new CCircle(center, radius, outlineColor));

	}
	else if (outlineColorStr.empty() && fillColorStr.empty())
	{
		m_shapes.push_back(new CCircle(center, radius));
	}

	return true;
}

bool CShapeController::ReadShape(string line)
{
	int spaceIdx = line.find(" ");
	string shapeType = line.substr(0, spaceIdx);
	line = line.substr(spaceIdx + 1);
	stringstream lineToParse;
	lineToParse << line;
	if (shapeType == "line")
	{
		return ParseLine(lineToParse);
	}
	else if (shapeType == "triangle")
	{
		return ParseTriangle(lineToParse);
	}
	else if (shapeType == "rectangle")
	{
		return ParseRectangle(lineToParse);
	}
	else if (shapeType == "circle")
	{
		return ParseCircle(lineToParse);
	}
	else
	{
		m_output << THERE_IS_NO_THAT_TYPE_OF_FIGURE << endl;
		return false;
	}

}

void CShapeController::WriteInfos() const
{
	if (m_shapes.size() == 0)
	{
		m_output << THERE_IS_NO_SHAPES << endl;
		return;
	}
	for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
	{
		m_output << (*it)->ToString() << endl;
	}
}

void CShapeController::GetMaxSquareInfo() const
{
	if (m_shapes.size() == 0)
	{
		m_output << THERE_IS_NO_SHAPES << endl;
		return;
	}
	auto x = max_element(begin(m_shapes), end(m_shapes),
		[](IShape* const s1, IShape* const s2)
		{
			return (*s1).GetArea() < (*s2).GetArea();
		});

	m_output << FIGURE_WITH_MAX_AREA << endl;
	m_output << (*x)->ToString();

}

void CShapeController::GetMinPerimeterInfo() const
{
	if (m_shapes.size() == 0)
	{
		m_output << THERE_IS_NO_SHAPES << endl;
		return;
	}
	auto x = min_element(begin(m_shapes), end(m_shapes),
		[](IShape* const s1, IShape* const s2)
		{
			return (*s1).GetPerimeter() < (*s2).GetPerimeter();
		});

	m_output << FIGURE_WITH_MIN_PERIMETR << endl;
	m_output << (*x)->ToString();

}

bool CShapeController::is_number(const string& s) const
{
	return !s.empty() && (s.find_first_not_of("0123456789.") == s.npos);
}


bool CShapeController::is_valid_hex(const string& s) const
{
	if (s.length() != HEX_COLOR_LENGTH)
	{
		return false;
	}
	for (int i = 0; i < s.length(); i++)
	{
		if (!isxdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}