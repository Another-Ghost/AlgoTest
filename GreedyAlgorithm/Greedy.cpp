#include "Greedy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

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

//Tencent 4/4 3/5
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

//Tencent 4/4 4/5
//Unfinished
struct Phone
{
	int a;
	int b;
	float left_time;
	Phone(int a_, int b_):a(a_), b(b_)
	{
		left_time = a/(b*1.0f);
	}

	bool operator < (const Phone& other) const
	{
		if (left_time < other.left_time)
			return true;
		
		return false;
	}
};


void SharedCharge()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, w;
		cin >> n >> w;
		vector<Phone> phones;
		for (int i = 0; i < n; ++i)
		{
			int a, b;
			cin >> a >> b;
			phones.push_back(Phone(a, b));
		}

		int sum_b = 0;
		for (int i = 0; i < phones.size(); ++i)
		{
			sum_b += phones[i].b;
		}
		if (w > sum_b)
		{
			cout << '-1' << endl;
			continue;
		}

		sort(phones.begin(), phones.end());
		int time_maintain = 0;
		float sum_b_cur = 0.0f;
		for (int i = 0; i < phones.size(); ++i)
		{
			sum_b_cur += phones[i].b;
			time_maintain += phones[i].left_time;
			phones[i].left_time = 0.0f;
			if (sum_b_cur < w)
			{
				for (int j = i + 1; j < phones.size(); ++j)
				{
					phones[j].left_time -= phones[i].left_time;
				}
			}
			else
			{

			}
		}
	}
}

//miHoYo / 2/5
struct Game
{
	int t;
	int w;

	bool operator < (const Game& other)
	{
		if (w < other.w)
			return true;
		
		return false;
	}
};

void GloryCLub()
{

	int n;
	cin >> n;

	//unordered_map<int, int> games;
	//vector<int> times(n);
	//vector<int> points(n);
	//for (int i = 0; i <= n; ++i)
	//{
	//	int temp;
	//	cin >> temp;
	//	times.push_back(temp);
	//}
	//for (int i = 0; i <= n; ++i)
	//{
	//	int temp;
	//	cin >> temp;
	//	points.push_back(temp);
	//}

	//for (int i = 0; i <= n; ++i)
	//{
	//	games.emplace(times[i], points[i]);
	//}

	vector<Game> games(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> games[i].t;
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> games[i].w;
	}

	sort(games.begin(), games.end());

	unordered_set<int> times;

	int sum = 0;
	for (int i = n-1; i >= 0; --i)
	{
		if (times.count(games[i].t))
			sum -= games[i].w;
		else
		{
			times.insert(games[i].t);
			sum += games[i].w;
		}
	}

	cout << sum << endl;
}


//Tencent 4/18 2/5
//测试数据通过，但不知为何提交后通过率为0
void GameClub()
{
	int T;
	cin >> T;

	while (T--)
	{
		int n;
		cin >> n;
		vector<Game> games(n);
		for (int i = 0; i < n; ++i)
		{
			int tmp;
			cin >> tmp;
			games[i].t = tmp;
		}

		for (int i = 0; i < n; ++i)
		{
			int tmp;
			cin >> tmp;
			games[i].w = tmp;
		}

		sort(games.begin(), games.end());

		unordered_set<int> times;
		int res = 0;
		for (int i = n - 1; i >= 0; --i)
		{
			if (!times.count(games[i].t))
			{
				times.emplace(games[i].t);
				res += games[i].w;
			}
			else
			{
				res -= games[i].w;
			}

		}

		cout << res;
	}
}





