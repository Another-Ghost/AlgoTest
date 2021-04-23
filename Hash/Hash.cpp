#include "Hash.h"
#include <iostream>
#include <unordered_set>

//´æ´¢½á¹¹

//leetcode 3
int lengthOfLongestSubstring(string s)
{
	if (s.size() == 0)
		return 0;
	unordered_set<char> lookup;
	int maxStr = 0;
	int left = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		while (lookup.find(s[i]) != lookup.end())
		{
			lookup.erase(s[left]);
			left++;
		}
		maxStr = max(maxStr, i - left + 1);
		lookup.insert(s[i]);
	}
	return maxStr; 
}


int FindTheMinimalPrimeNumberLargerThan(int n)
{
	for (int i = n; ; ++i)
	{
		bool flag = true;
		for (int j = 2; j * j <= i; ++j)
		{
			if (i % j == 0)
			{
				flag = false;
				break;
			}
		}

		if (flag)
		{
			return i;
		}
	}
	return 2;
}