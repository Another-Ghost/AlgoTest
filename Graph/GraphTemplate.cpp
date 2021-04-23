#include "GraphTemplate.h"
#include <iostream>
#include <vector>

using namespace std;

//ʱ�临�Ӷ�O(N^2)��NΪ���������������ڳ���ͼ
//ע��һ����Ŀ�����±���1Ϊ��㣬ע�������鳤�Ⱥͱ�����ʼֵ
//LeetCode 743
namespace Dijkstra
{
	int dijkstra(vector<vector<int>>& g, int start, int end)
	{
		int n = g.size();
		vector<int> dist(n, INT_MAX / 2); //g�еı�ǲ����ڵıߵ����ֵ���ܴ��� INT_MAX / 2
		vector<bool> st(n); //Ϊtrue˵���õ����ڵ�ǰ��ȷ�����·���ĵ�ļ���
		dist[start] = 0; //�ĸ���Ϊ�����Ȱ��ĸ�����Ϊ0	
		for (int i = 0; i < n; ++i)
		{
			int t = -1; //���±�
			for (int j = 0; j < n; ++j)
			{
				if (!st[j] && (t == -1 || dist[t] > dist[j]))	//�ҵ���ǰ����start����ĵ�
					t = j;
			}
			st[t] = true; //���õ���� ��ǰ��ȷ�����·���ĵ� �ļ���

			for (int j = 0; j < n; ++j)
				dist[j] = min(dist[j], dist[t] + g[t][j]);	//�øõ�t���������㵽start�ľ���
		}

		return (dist[end] != INT_MAX / 2) ? dist[end] : -1;
	}
}




