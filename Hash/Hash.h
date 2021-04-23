#pragma once
#include <string>

using namespace std;

//开放寻址法
//数组的长度要开到题目数据范围的2~3倍
//和上cheshuo一样的道理，蹲坑法
//删除操作可以通过找到之后打一个标记来实现
namespace OpenAddressing
{
	const int N = 20003, null = 0x3f3f3f3f;
	int h[N];

	void Insert(int x)
	{
		int k = Search(x);
		h[k] = x;
	}


	int Search(int x)	//如果x在哈希表中存在的话就返回x所在位置，否则返回他应该存储的位置
	{
		int k = (x % N + N) % N;
		while (h[k] != null && h[k]!= x)
		{
			k++;
			if (k == N)
				k = 0;
		}
		return k;
	}

	bool Find(int x)
	{
		int k = Search(x);
		if (h[k] != null)
			return true;
		else
			return false;
	}

	void Init()
	{
		memset(h, -1, sizeof h);
	}
}


//拉链法
const int N = 10003; //质数，远离2的阶乘

int h[N], val[N], ne[N], idx;

//x的范围为-10e9 ~ 10e9
void Insert(int x)
{
	int k = (x % N + N) % N; //让余数变成正数
	//C++里负数模上一个数是负数，与数学中定义不同

	val[idx] = x, ne[idx] = h[k], h[k] = idx++;	//让新点的next指针指向h[k]保存的指针, h[k]的更新成当前点的指针（头插法）
	
}

bool Find(int x)
{
	int k = (x % N + N) % N;
	for (int i = h[k]; i != -1; i = ne[i])
	{
		if (val[i] == x)
			return true;
	}

	return false;
}

void Init()
{
	memset(h, -1, sizeof h);//空指针用-1来表示
}


int lengthOfLongestSubstring(string s);
