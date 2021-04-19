#include "Math.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

//MiHoYo 3/37 3
//�������
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


//���鼯��
//1.���������Ϻϲ�
//2.ѯ������Ԫ���Ƿ���һ�����ϵ���

//����ԭ�� ÿ��������һ������ʾ�������ı�ž����������ϵı�š�ÿ���ڵ�洢���ĸ��ڵ㣬p[x]��ʾx�ĸ��ڵ�

//����1�� ����ж������� if(p[x] == x)
//����2�� �����x�ļ��ϱ�ţ�while(p[x]!=x) x = p[x]
//����3�� ��κϲ��������ϣ�px��x�ļ��ϱ�ţ�py��y�ļ��ϱ�š�p[x] = y

//�Ż���·��ѹ�� �����Ⱥϲ���

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


//leetcode 203 ���鼯����ͨ����
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
		p[i] = i; //���鼯��ʼ�����ؼ�����

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
						//continue; //��continue���ܵ��½ڵ�ֻ�ϲ���һ�������se����û�кϲ����������������set
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
int BinarySearch(vector<int>& nums, int l, int r, int num) //��ѯ����ʱ��С����˵㷵�����ֵ�������Ҷ˵㷵���Ҳ�ֵ������������ز�ѯֵ�Ҳ��һ��ֵ
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
			break; //��дbreak
		}
	}

	for (int i = n - 1; i >= 0; --i) //0д����n
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
			else if (sum < 0) //��дelse�����������else�жϷ�Χ����
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

