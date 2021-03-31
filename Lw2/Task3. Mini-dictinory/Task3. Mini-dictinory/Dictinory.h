#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef map<string, vector<string>> Dictionary;

char ToLowerChar(char ch);
string ToLowerString(string str);
Dictionary ReadDictinory(string fileName);
string Translate(Dictionary& dictionary, string line);
void AddWordInDictonary(Dictionary& dictionary, string newWordToAdd, string newWordTransaltion);
void SaveDictionoryIntoFile(string outputFileName, string newWordsToSave);