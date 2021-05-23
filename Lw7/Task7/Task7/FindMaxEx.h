#pragma once
#include <vector>

using namespace std;

template<typename T, typename Less>
bool FindMaxEx(vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty()) return false;

	int idxOfMax = 0;

	if (arr.size() > 1)
	{
		for (unsigned i = 0; i < arr.size(); i++)
		{
			if (!less(arr[i], arr[idxOfMax]))
			{
				idxOfMax = i;
			}
		}
	}

	maxValue = arr[idxOfMax];
	return true;
}