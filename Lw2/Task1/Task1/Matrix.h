#pragma once
#include <string>
#include <optional>
#include <vector>

std::vector<double> ReadNumbers(const std::string& str);
void ShowNumbers(std::vector<double>& numbers);
void CalculateNumbers(std::vector<double>& numbers);