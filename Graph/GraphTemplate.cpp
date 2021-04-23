#include "GraphTemplate.h"
#include <iostream>
#include <vector>

using namespace std;

//时间复杂度O(N^2)（N为顶点数），适用于稠密图
//注意一般题目顶点下标以1为起点，注意变更数组长度和遍历起始值
//LeetCode 743
namespace Dijkstra
{
	int dijkstra(vector<vector<int>>& g, int start, int end)
	{
		int n = g.size();
		vector<int> dist(n, INT_MAX / 2); //g中的标记不存在的边的最大值不能大于 INT_MAX / 2
		vector<bool> st(n); //为true说明该点已在当前已确定最短路径的点的集合
		dist[start] = 0; //哪个点为起点就先把哪个点置为0	
		for (int i = 0; i < n; ++i)
		{
			int t = -1; //点下标
			for (int j = 0; j < n; ++j)
			{
				if (!st[j] && (t == -1 || dist[t] > dist[j]))	//找到当前距离start最近的点
					t = j;
			}
			st[t] = true; //将该点加入 当前已确定最短路径的点 的集合

			for (int j = 0; j < n; ++j)
				dist[j] = min(dist[j], dist[t] + g[t][j]);	//用该点t更新其他点到start的距离
		}

		return (dist[end] != INT_MAX / 2) ? dist[end] : -1;
	}
}




