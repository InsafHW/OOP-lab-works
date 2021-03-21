#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

typedef std::map<std::string, std::vector<std::string>> Dictinory;

char ToLowerChar(char ch);
void ToLowerString(std::string& str);
Dictinory ReadDictinory(const std::string& fileName);
void SaveDictionory(const std::string& fileName, std::string& transl);
void Translate(std::string line, bool& addedWordInDictinory, std::string& newWordsToSave, std::string outputFileName, Dictinory dictinory);