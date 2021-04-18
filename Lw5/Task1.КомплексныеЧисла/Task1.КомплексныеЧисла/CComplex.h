#pragma once
#include <cmath>
#include <float.h>
#include <math.h>
#include <iostream>
#include <ostream>
#include <istream>
#include <string>

using namespace std;

class CComplex
{
public:
	CComplex(double real, double image);
	double Re() const;
	double Im() const;
	double GetMagnitude() const;
	double GetArgument() const;

	CComplex const operator +(CComplex const& complex2) const;
	CComplex const operator -(CComplex const& complex2) const;
	CComplex const operator *(CComplex const& complex2) const;
	CComplex const operator *(double scalar) const;
	CComplex const operator /(CComplex const& complex2) const;
	CComplex const operator /(double scalar) const;
	CComplex const operator -() const;
	CComplex const operator +() const;
	CComplex& operator +=(CComplex const& complex);
	CComplex& operator -=(CComplex const& complex);
	CComplex& operator *=(CComplex const& complex);
	CComplex& operator *=(double scalar);
	CComplex& operator /=(CComplex const& complex);
	CComplex& operator /=(double scalar);
	bool operator ==(CComplex const& other) const;
	bool operator ==(double scalar) const;
	bool operator !=(CComplex const& other) const;
	bool operator !=(double scalar) const;

private:
	double m_real = 0;
	double m_image = 0;
};

CComplex const operator *(double scalar, CComplex const& complex);
bool operator ==(double scalar, CComplex const& complex);
bool operator !=(double scalar, CComplex const& complex);
ostream& operator<<(ostream& stream, CComplex const& complex);
istream& operator >>(istream& stream, CComplex& complex);