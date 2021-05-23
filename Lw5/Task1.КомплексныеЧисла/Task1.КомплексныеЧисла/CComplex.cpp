#include "CComplex.h"


CComplex::CComplex(double real, double image)
	:m_real(real)
	, m_image(image)
{ }

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(pow(m_real, 2) + pow(m_image, 2));
}

double CComplex::GetArgument() const
{
	return atan(m_image / m_real);
}

CComplex const CComplex::operator+(CComplex const& complex2) const
{
	return CComplex(m_real + complex2.m_real, m_image + complex2.m_image);
}

CComplex const CComplex::operator-(CComplex const& complex2) const
{
	return CComplex(m_real - complex2.m_real, m_image - complex2.m_image);
}

CComplex const CComplex::operator*(CComplex const& complex2) const
{
	return CComplex(m_real * complex2.m_real - m_image * complex2.m_image, m_real * complex2.m_image + complex2.m_real * m_image);
}

CComplex const CComplex::operator*(double scalar) const
{
	return CComplex(m_real * scalar, m_image * scalar);
}

CComplex const CComplex::operator/(CComplex const& complex2) const
{
	double powSum = pow(complex2.m_real, 2) + pow(complex2.m_image, 2);
	if (powSum == 0)
	{
		cout << ERROR_DIVIDE_ZERO << endl;
		return *this;
	}
	double real = (m_real * complex2.m_real + m_image * complex2.m_image) / powSum;
	double image = (m_image * complex2.m_real - m_real * complex2.m_image) / powSum;
	return CComplex(real, image);
}

CComplex const CComplex::operator/(double scalar) const
{
	if (scalar == 0)
	{
		cout << ERROR_DIVIDE_ZERO << endl;
		return *this;
	}
	return CComplex(m_real / scalar, m_image / scalar);
}

CComplex const CComplex::operator-() const
{
	return CComplex(-m_real, -m_image);
}

CComplex const CComplex::operator+() const
{
	return *this;
}

CComplex& CComplex::operator+=(CComplex const& complex)
{
	m_real += complex.m_real;
	m_image += complex.m_image;

	return *this;
}

CComplex& CComplex::operator-=(CComplex const& complex)
{
	m_real -= complex.m_real;
	m_image -= complex.m_image;

	return *this;
}

CComplex& CComplex::operator*=(CComplex const& complex)
{
	double newReal, newImage;
	newReal = m_real * complex.m_real - m_image * complex.m_image;
	newImage = m_real * complex.m_image + complex.m_real * m_image;

	m_real = newReal;
	m_image = newImage;

	return *this;
}

CComplex& CComplex::operator*=(double scalar)
{
	m_real *= scalar;
	m_image *= scalar;

	return *this;
}

CComplex& CComplex::operator/=(CComplex const& complex)
{
	double powSum = pow(complex.m_real, 2) + pow(complex.m_image, 2);
	if (powSum == 0)
	{
		cout << ERROR_DIVIDE_ZERO << endl;
		return *this;
	}

	double newReal, newImage;
	newReal = (m_real * complex.m_real + m_image * complex.m_image) / powSum;
	newImage = (m_image * complex.m_real - m_real * complex.m_image) / powSum;

	m_real = newReal;
	m_image = newImage;

	return *this;
}

CComplex& CComplex::operator/=(double scalar)
{
	if (scalar == 0)
	{
		cout << ERROR_DIVIDE_ZERO << endl;
		return *this;
	}
	m_real /= scalar;
	m_image /= scalar;
	return *this;
}

bool CComplex::operator==(CComplex const& other) const
{
	return (fabs(m_real - other.m_real) < DBL_EPSILON && fabs(m_image - other.m_image) < DBL_EPSILON);
}

bool CComplex::operator==(double scalar) const
{
	return (fabs(m_real - scalar) < DBL_EPSILON && m_image == 0);
}

bool CComplex::operator!=(CComplex const& other) const
{
	return !(*this == other);
}

bool CComplex::operator!=(double scalar) const
{
	return !(*this == scalar);
}

CComplex const operator*(double scalar, CComplex const& complex)
{
	return CComplex(scalar * complex.Re(), scalar * complex.Im());
}

bool operator==(double scalar, CComplex const& complex)
{
	return (fabs(scalar - complex.Re() < DBL_EPSILON) && complex.Im() == 0);
}

bool operator!=(double scalar, CComplex const& complex)
{
	return !(scalar == complex);
}

ostream& operator<<(ostream& stream, CComplex const& complex)
{
	if (complex.Re() == 0 && complex.Im() == 0)
	{
		stream << "0";
	}
	else
	{
		if (complex.Re() != 0)
		{
			stream << complex.Re();
		}
		if (complex.Im() != 0)
		{
			if (complex.Im() > 0 && complex.Re() != 0)
			{
				stream << "+";
			}
			stream << complex.Im() << "i";
		}
	}

	return stream;
}

istream& operator>>(istream& stream, CComplex& complex)
{
	double real = 0, image = 0;
	string line;
	getline(stream, line);

	if (line.empty())
	{
		complex = CComplex(real, image);
		return stream;
	}

	bool isFirstMinus = line[0] == '-';

	if (isFirstMinus)
	{
		line = line.substr(1);
	}

	int minus = line.find("-");
	int plus = line.find("+");
	int i = line.find("i");

	if (minus == -1 && plus == -1 && i == -1)
	{
		// только действительное отрицательное число
		real = stod(line);
		if (isFirstMinus)
		{
			real *= -1;
		}
	}

	if (minus != -1)
	{
		// идет отрицательное мнимое число
		real = stod(line.substr(0, minus));
		if (isFirstMinus)
		{
			real *= -1;
		}
		line = line.substr(minus + 1);
		int i = line.find("i");
		image = stod(line.substr(0, i)) * -1;
	}

	if (plus != -1)
	{
		// идет положительное мнимое число
		real = stod(line.substr(0, plus));
		if (isFirstMinus)
		{
			real *= -1;
		}
		line = line.substr(plus + 1);
		int i = line.find("i");
		image = stod(line.substr(0, i));
	}

	if (minus == -1 && plus == -1 && i != -1)
	{
		image = stod(line);
		if (isFirstMinus)
		{
			image *= -1;
		}
	}

	complex = CComplex(real, image);

	return stream;
}
