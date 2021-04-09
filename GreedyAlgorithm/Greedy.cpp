#include "Greedy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
//ByteDance 3/27 3
//题目描述
//小明的手中有n根铁棒, 他想从中找出三根, 用它们合成一个“优美指数最高的三角形”。
//设一个三角形的三边为a, b, c, 定义三角形的优美指数为 | a - b | +| a - c | +| b - c | 。另
//外需注意, 由于小明不喜欢等腰三角形, 因此等腰三角形的优美指数总是0。
//输入描述
//输入文件第一行为整数n, 接下来n行, 每行一个整数, 表示铁棒长度, 铁棒长度在64位长整型范围内。
//输出描述
//输出可以得到的优美指数最大的三角形的优美指数。如果不能合成三角行，则输出为0.

//算法目前存在问题，改用对最大最小边差值进行排序后遍历的方法
void MaxGraceIndex()
{
	int n;
	cin >> n;
	
	if (n < 3)
	{
		cout << "error" << endl;
		return;
	}

	vector<int> edges(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> edges[i];
	}

	sort(edges.begin(), edges.end());

	int i=0;
	while (i <= edges.size()-2-i) //i <= size-2-i
	{
		int j = 0;
		int res_max = 0;
		while (j < edges.size() - 2)
		{
			if (!IsNotIsoscelesTriangle(edges[j], edges[j + 1], edges[n - 1 - i])&&IsTriangle(edges[j], edges[j + 1], edges[n-1-i]))
			{
				res_max = 2*(edges[n-i-1]-edges[j]);
				break;
			}
			++j;
		}

		int k=edges.size()-1;
		while (k > 1)
		{
			if (!IsNotIsoscelesTriangle(edges[i], edges[k-1], edges[k]) && IsTriangle(edges[i], edges[k - 1], edges[k]))
			{
				res_max = max(res_max, 2 * (edges[k] - edges[i]));
				break;
			}
			--k;
		}

		if (res_max != 0)
		{
			cout << res_max;
			return;
		}
		++i;
	}
	cout << "Not found" << endl;
	return;
}

bool IsTriangle(int a, int b, int c)
{
	if (a + b <= c || a + c <= b || b + c <= a)
		return false;
	return true;
}

bool IsNotIsoscelesTriangle(int a, int b, int c)
{
	if (a == b || a == c || b == c)
		return true;
	return false;
}

void WireRope()
{
	int T;
	cin >> T;
	while (T-- > 0)
	{
		int n;
		cin >> n;
		vector<int> trainees;
		for (int i = 0; i < n; ++i)
		{
			int temp;
			cin >> temp;
			trainees.push_back(temp);
		}

		sort(trainees.begin(), trainees.end());
		int sum = 0;
		int n_left = trainees.size();
		while (n_left > 3)
		{
			int time_min = trainees[0] + 2 * trainees[1] + trainees[n_left - 1];
			time_min = min(time_min, 2 * trainees[0] + trainees[n_left - 2] + trainees[n_left - 1]);
			sum += time_min;
			n_left -= 2;
		}
		if (n_left == 3)
			sum += trainees[0] + trainees[1] + trainees[2];
		else if (n_left == 2)
			sum += trainees[1];
		else if(n_left==1)
			sum += trainees[0];

		cout << sum << endl;
	}



}




