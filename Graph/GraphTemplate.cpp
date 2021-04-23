#include "GraphTemplate.h"
#include <iostream>
#include <vector>

using namespace std;

namespace Dijkstra
{
	int dijkstra(vector<vector<int>>& g, int start, int end)
	{
		int n = g.size();
		vector<int> dist(n, 0x3f3f3f3f); //保存所有点到0号点的最短距离
		vector<bool> st(n);
		dist[start] = 0;	
		for (int i = 0; i < n; ++i)
		{
			int t = -1;
			for (int j = 0; j < n; ++j)
			{
				if (!st[j] && (t == -1 || dist[t] > dist[j]))
					t = j;
				st[t] = true;
			}
			
			for (int j = 0; j < n; ++j)
				dist[j] = min(dist[j], dist[t] + g[t][j]);
		}

		if (dist[end] == 0x3f3f3f3f)
			return -1;
		else
			return dist[end];
	}

	
}




