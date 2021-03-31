#include "Greedy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
//ByteDance 3/27 3
//��Ŀ����
//С����������n������, ��������ҳ�����, �����Ǻϳ�һ��������ָ����ߵ������Ρ���
//��һ�������ε�����Ϊa, b, c, ���������ε�����ָ��Ϊ | a - b | +| a - c | +| b - c | ����
//����ע��, ����С����ϲ������������, ��˵��������ε�����ָ������0��
//��������
//�����ļ���һ��Ϊ����n, ������n��, ÿ��һ������, ��ʾ��������, ����������64λ�����ͷ�Χ�ڡ�
//�������
//������Եõ�������ָ�����������ε�����ָ����������ܺϳ������У������Ϊ0.

//�㷨Ŀǰ�������⣬���ö������С�߲�ֵ�������������ķ���
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




