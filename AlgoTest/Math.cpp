#include "Math.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

//MiHoYo 3/37 3
//均衡的数
//cout << BalenceNumbers(11, 121) << endl;

int BalanceNumbers(int L, int R)
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


//并查集：
//1.将两个集合合并
//2.询问两个元素是否在一个集合当中

//基本原理： 每个集合用一棵树表示。树根的编号就是整个集合的编号。每个节点存储它的父节点，p[x]表示x的父节点

//问题1： 如何判断树根： if(p[x] == x)
//问题2： 如何求x的集合编号：while(p[x]!=x) x = p[x]
//问题3： 如何合并两个集合：px是x的集合编号，py是y的集合编号。p[x] = y

//优化：路径压缩 （按秩合并）

namespace union_find
{
	const int N = 100010;

	int n, m;
	int p[N];

	int find(int x)
	{
		if (p[x] != x)
			p[x] = find(p[x]);
		return p[x];
	}

	
	void Merge(int x, int y)
	{
		p[find(x)] = find(y);
	}

	int main()
	{
		cin >> n, m;
	
		for (int i = 1; i <= n; ++i)
			p[i] = i;

		while (m--)
		{
			char op[2];
			int a, b;
			cin >> op >> a >> b;

			if (op[0] == 'M') 
				p[find(a)] = find(b);
			else
			{
				if (find(a) == find(b))
					puts("Yes");
				else
					puts("No");
			}
		}

		return 0;
	}



}


//leetcode 203 并查集求连通域数
/*
//for (auto t : times)
//{
//	cout << t << endl;
//}
//int m, n;
//cin >> m >> n;
//vector<vector<char>> grid(m, vector<char>(n));
//for (int i = 0; i < m; ++i)
//{
//	for (int j = 0; j < n; ++j)
//		cin >> grid[i][j];
//}


4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

3 3
1 1 1
0 1 0
1 1 1

4 5
1 1 1 1 0
1 1 0 1 0
1 1 0 0 0
0 0 0 0 0
*/

int find(vector<int>& p, int x)
{
	if (p[x] != x)
		p[x] = find(p, p[x]);
	return p[x];
}

void Merge(vector<int>& p, int x, int y)
{
	p[find(p, x)] = find(p, y);
}



int numIslands(vector<vector<char>>& grid) {

	vector<int> p(grid.size() * grid[0].size());

	for (int i = 0; i < p.size(); ++i)
		p[i] = i; //并查集初始化，关键步骤

	unordered_set<int> islands;
	int m = grid.size();
	int n = grid[0].size();
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (grid[i][j] == '1')
			{
				int tmp = i * n + j;
				if (i != 0)
					if (grid[i - 1][j] == '1') {
						Merge(p, tmp, (i - 1) * n + j);
						//continue; //加continue可能导致节点只合并了一个方向的se，并没有合并其他方向的相连得set
					}
				if (i != m - 1)
					if (grid[i + 1][j] == '1')
					{
						Merge(p, tmp, (i + 1) * n + j);
						//continue;
					}
				if (j != 0)
					if (grid[i][j - 1] == '1') 
					{
						Merge(p, tmp, i * n + j - 1);
						//continue;
					}
				if (j != n - 1)
					if (grid[i][j + 1] == '1') 
					{
						Merge(p, tmp, i * n + j + 1);
						//continue;
					}
			}
		}
	}

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (grid[i][j] == '1')
			{
				int num = find(p, i * n + j);
				islands.insert(num);
			}
		}
	}

	return islands.size();
}

//leetcode 15 
int BinarySearch(vector<int>& nums, int l, int r, int num) //查询不到时，小于左端点返回左侧值，大于右端点返回右侧值，其他情况返回查询值右侧第一个值
{
	if (l > r)
		return -1;
	while (l < r)
	{
		int mid = l + r >> 1;
		if (nums[mid] >= num)
			r = mid;
		else
			l = mid + 1;
	}
	return l;
};

vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> ans;
	if (nums.size() < 3)
		return ans;
	int n = nums.size();
	sort(nums.begin(), nums.end());
	if (nums[0] > 0 || nums[n - 1] < 0)
		return ans;

	//auto BinarySearch = [&](int l, int r, int num) -> int
	//{
	//	while (l < r)
	//	{
	//		int mid = l + r >> 1;
	//		if (nums[mid] >= num)
	//			r = mid;
	//		else
	//			l = mid + 1;
	//	}
	//	return l;
	//};

	int negative = 0, positive = n - 1;
	for (int i = 0; i < n; ++i)
	{
		if (nums[i] >= 0)
		{
			negative = i - 1;
			break; //忘写break
		}
	}

	for (int i = n - 1; i >= 0; --i) //0写成了n
	{
		if (nums[i] <= 0)
		{
			positive = i + 1;
			break;
		}
	}

	if (positive - negative >= 4)
	{
		vector<int> match = { 0, 0, 0 };
		ans.push_back(match);
	}
	for (int i = 0; i <= negative; ++i)
	{
		for (int j = n - 1; j >= positive; --j)
		{
			int sum = nums[i] + nums[j];
			int idx_search;
			if (sum > 0)
			{
				idx_search = BinarySearch(nums, i + 1, negative, -sum);
			}
			else if (sum < 0) //忘写else，导致下面的else判断范围错误
			{
				idx_search = BinarySearch(nums, positive, j - 1, -sum);
			}
			else
			{
				idx_search = BinarySearch(nums, negative + 1, positive - 1, 0);
			}

			if (idx_search > i && idx_search < j)
			{
				if (nums[idx_search] == -sum)
				{
					vector<int> match = { nums[i], nums[idx_search], nums[j] };
					ans.emplace_back(match);
				}
			}

		}
	}

	return ans;
}

