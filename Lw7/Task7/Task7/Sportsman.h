#pragma once
#include <string>

using namespace std;

class Sportsman
{
public:
	Sportsman() = default;
	Sportsman(string FIO, double height, double weight);
	double GetHeight() const;
	double GetWeight() const;
	string GetFIO() const;
private:
	string m_FIO;
	double m_height;
	double m_weight;
};

