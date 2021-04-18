#pragma once
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <sstream>


using namespace std;

optional<vector<double>> ReadNumbers(const string& fileName);
string ShowNumbers(vector<double>& numbers);
void CalculateNumbers(vector<double>& numbers);
string MakeCalculation(const string& str);