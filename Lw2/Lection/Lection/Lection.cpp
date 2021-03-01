#include <iostream>
#include <string>
#include <string_view>
#include <map>

using namespace std;

bool IsEven(int value)
{
	return (value % 2) == 0;
}


int main()
{
	int numbers[] = { 1, 3, 9, 10, 17, 12, 21 };

	auto it = find_if(cbegin(numbers), cend(numbers), IsEven);

	if (it != cend(numbers))
	{
		cout << "First even number in array is " << *it << endl;
	}
}
