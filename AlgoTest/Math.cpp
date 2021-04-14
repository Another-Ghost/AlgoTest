#include "Math.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

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


/*
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
