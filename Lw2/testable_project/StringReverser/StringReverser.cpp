#include <iostream>
#include <string>
#include "Reverse.h"

using namespace std;

int main()
{
    string line;

	while (getline(cin, line))
	{
		cout << Reverse(line) << endl;
	}
	cout << Reverse("");
}
