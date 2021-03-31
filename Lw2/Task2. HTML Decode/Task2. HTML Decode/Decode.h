#pragma once
#include <string>
#include <iostream>

std::string Decode(std::string const& text);
void DecodeLines(std::istream& input, std::ostream& output);