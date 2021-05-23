#pragma once
#include <string>
#include <cmath>
#include <iomanip>  

using namespace std;

class IShape
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};

