#pragma
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef map<string, string> Dictionary;

char ToLowerChar(char ch);
string ToLowerString(string str);
Dictionary ReadDictinory(string fileName);
string Translate(Dictionary& dictionary, string lineToTranslate);
void AddInDictonary(Dictionary& dictionary, string lineToAdd, string lineTranslation);
void SaveDictionoryIntoFile(string outputFileName, Dictionary& dict);
void SaveUpdatedDictionaryUI(istream& input, ostream& output, Dictionary& dict, string outputFileName = "");
void WriteTranslationUI(istream& input, ostream& output, string unknownWord, bool& hasBeenTranslated, Dictionary& dict);