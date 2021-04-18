#pragma once
#include <istream>
#include <vector>
#include <string>
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

using namespace std;


class CShapeController
{
public:
	void ReadShapes(istream& input);
	string WriteInfos() const;
private:
	vector<CLineSegment> lines;
	vector<CTriangle> triangles;
	vector<CRectangle> rectangles;
	vector<CCircle> cirlces;
};

