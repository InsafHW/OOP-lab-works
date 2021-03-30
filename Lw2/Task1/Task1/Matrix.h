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

std::optional<std::vector<double>> ReadNumbers(const std::string& fileName);
std::string ShowNumbers(std::vector<double>& numbers);
void CalculateNumbers(std::vector<double>& numbers);
std::string MakeCalculation(const std::string& str);