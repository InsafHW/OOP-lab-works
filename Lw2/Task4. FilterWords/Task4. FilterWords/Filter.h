#pragma once
#include <string>
#include <set>
#include <fstream>
#include <iostream>

std::set<std::string> ReadFilterWords(const std::string& fileName);
std::string Filter(const std::string& str, const std::set<std::string> &filter);
void FilterLines(std::istream& input, std::ostream& output, const std::set<std::string> &filter);