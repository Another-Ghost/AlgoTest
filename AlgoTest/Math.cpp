#include "Math.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//MiHoYo 3/37 3
//¾ùºâµÄÊý
//cout << BalenceNumbers(11, 121) << endl;

int BalenceNumbers(int L, int R)
{
	int count = 0;
	for (int i = L; i <= R; ++i)
	{
		string si = to_string(i);
		int sum0 = 0;
		int sum1 = 0;
		for (int j = si.length() - 1; j >= 0; --j)
		{
			int value = si[j] - '0';

			if (j % 2 == 0)
				sum0 += value;
			else
				sum1 += value;
		}
		if (sum0 == sum1) {
			++count;
			cout << i << endl;
		}
		
	}
	return count;
}

