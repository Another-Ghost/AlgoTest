#include "Stack.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>

using namespace std;

//Tencent 4/4 2/5
void EliminateForHappy()
{
	int n;
	cin >> n;
	vector<int> nums;

	string s;
	cin >> s;
	for (int i = 0; i < s.size(); ++i)
	{

		nums.push_back(s[i] - '0');
	}

	stack<int> st;
	//st.push(nums[0]);
	for (int i = 0; i < n; ++i)
	{
		if (!st.empty()) //当栈空时调用top()将出错
		{
			if (nums[i] + st.top() == 10)
			{
				st.pop();
			}
			else
			{
				st.push(nums[i]);
			}
		}
		else
			st.push(nums[i]);
	}

	cout << st.size()<<endl;
}

void EliminateForHappy_List()
{
	int n;
	cin >> n;
	list<int> nums;

	string s;
	cin >> s;
	for (int i = 0; i < s.size(); ++i)
	{

		nums.push_back(s[i] - '0');
	}

	//list<int>::iterator itor;
	//for (itor = nums.begin(); itor != nums.end();)
	//{
	//	auto itor_pre = itor;
	//	++itor;
	//	if (itor!=nums.end() && *itor_pre + *itor == 10)
	//	{
	//		itor = nums.erase(itor_pre, ++itor); //第二个参数end需为要删除的最后一个元素的后一个位置
	//		if(itor!=nums.begin())
	//			--itor;
	//	}
	//}

	list<int>::iterator itor = nums.begin();
	auto itor_pre = itor++;
	
	while (itor != nums.end())
	{
		if (*itor_pre + *itor == 10)
		{
			itor = nums.erase(itor_pre, ++itor);
			if (itor != nums.begin())
			{
				itor_pre = itor;
				--itor_pre;
			}
			else
				break;
		}
		else
		{
			if (itor != nums.end())
			{
				itor_pre = itor;
				++itor;
			}
		}
	}

	//list<int>::iterator itor;
	//for (itor = nums.begin(); itor != nums.end();)
	//{
	//	auto itor_pre = itor;
	//	++itor;
	//	if (itor != nums.end() && *itor_pre + *itor == 10)
	//	{
	//		itor = nums.erase(itor_pre, ++itor);
	//		if (itor != nums.begin())
	//			--itor;
	//	}
	//}

	cout << nums.size() << endl;
}


