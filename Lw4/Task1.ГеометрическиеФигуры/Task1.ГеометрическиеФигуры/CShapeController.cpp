#include "CShapeController.h"
#include "CPoint.h"
#include "CLineSegment.h"

using namespace std;


void CShapeController::ReadShapes(istream& input)
{
	string line;
	while (getline(input, line))
	{
		int spaceIdx = line.find(" ");
		string shapeType = line.substr(0, spaceIdx);
		line = line.substr(spaceIdx + 1);

		if (shapeType == "line")
		{
			spaceIdx = line.find(" ");
			double startX = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double startY = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double endX = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double endY = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			// исправить цвет
			uint32_t outlineColor = static_cast<uint32_t>(stoul(line));

			CPoint start = { startX, startY };
			CPoint end = { endX, endY };

			lines.push_back(CLineSegment(start, end, outlineColor));
		}
		else if (shapeType == "triangle")
		{
			spaceIdx = line.find(" ");
			double v1X = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double v1Y = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double v2X = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double v2Y = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double v3X = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double v3Y = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");

			CPoint v1 = { v1X, v1Y };
			CPoint v2 = { v2X, v2Y };
			CPoint v3 = { v3X, v3Y };

			//  исправить цвета
		}
		else if (shapeType == "rectangle")
		{
			spaceIdx = line.find(" ");
			double topleftX = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double topleftY = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double width = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double height = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");

			CPoint topLeft = { topleftX, topleftY };

			// исправить цвета
		}
		else if (shapeType == "circle")
		{
			spaceIdx = line.find(" ");
			double centerX = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double centerY = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");
			double radius = stod(line.substr(0, spaceIdx));
			line = line.substr(spaceIdx + 1);
			spaceIdx = line.find(" ");

			CPoint center = { centerX, centerY };

			// исправить цвета
		}
		else
		{
			throw invalid_argument("There is no such a type!");
		}
	}
}

string CShapeController::WriteInfos() const
{
	stringstream output;

	for (int i = 0; i < lines.size(); i++)
	{

	}

	return string();
}

