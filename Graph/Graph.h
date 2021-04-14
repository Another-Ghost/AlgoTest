#pragma once
#include <iostream>
#include <vector>
#include<queue>
using namespace std;

//bellman-ford 
//一些情况下，求有边数限制的最短路径只能用bf
//其他情况spfa各方面要优于bf

//bellman-ford要求负环不存在于所求路径中即可， 或限制负环循环次数
//spfa算法要求图中一定不存在负环
namespace bellman_ford {

	const int N = 500, M = 10010;

	int n, m, k;
	int dist[N], backup[N];

	struct Edge
	{
		int a, b, w;
	}edges[M];

	int bellman_ford()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0;

		for (int i = 0; i < k; ++i)
		{
			memcpy(backup, dist, sizeof(dist)); //每次遍历前备份一下
			for (int j = 0; j < m; ++j)
			{
				int a = edges[j].a;
				int b = edges[j].b;
				int w = edges[j].w;
				dist[b] = min(dist[b], backup[a] + w);
			}
		}

		if (dist[n] > 0x3f3f3f3f / 2)
			return -1;
	}

	int main()
	{
		cin >> n >> m >> k;
		for (int i = 0; i < m; ++i)
		{
			int a, b, w;
			cin >> a >> b >> w;
			edges[i] = { a, b, w };
		}

		int t = bellman_ford();

		if (t == -1)
		{
			puts("impossible");
		}
		else
			cout << t;

		return 0;
	}

}

//Dijksta 

//稠密图用邻接矩阵来存，稀疏图用邻接表来存
//有向图和无向图的最短路径相同，所以只考虑有向图即可

//在最短路问题里，如果所有自环是正的，自环肯定不会出现在最短路径里；重边的话只保留长度最短的边即可
namespace Dijkstra
{
	const int N = 510;
	int n, m;
	int g[N][N]; //邻接矩阵
	int dist[N]; //当前的最短距离
	bool st[N]; //每个点的最短路径是否已经确定了

	int dijkstra()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0; //初始化
		
		for (int i = 0; i < n; ++i)
		{
			int t = -1;
			for (int j = 1; j <= n; ++j) 
				if (!st[j] && (t == -1 || dist[t] > dist[j])) //1为起点（不是0）
					t = j;
			st[t] = true;

			for (int j = 1; j <= n; ++j)
				dist[j] = min(dist[j], dist[t] + g[t][j]);
		}

		if (dist[n] == 0x3f3f3f3f)
			return -1;
		else
			return dist[n];
	}


	int main()
	{
		cin >> n >> m;

		memset(g, 0x3f, sizeof g);

		while (m--)
		{
			int a, b, c;
			cin >> a >> b >> c;
			g[a][b] = min(g[a][b], c);
		}

		int t = dijkstra();

		cout << t;

		return 0;

	}
}

//Dijksta堆优化版
//适用于稀疏图

namespace Dijkstra_heap
{


	typedef pair<int, int> PII;

	const int N = 100010;
	int n, m;
	int h[N], w[N], e[N], ne[N], idx; //邻接表

	int dist[N]; //当前的最短距离
	bool st[N]; //每个点的最短路径是否已经确定了

	int dijkstra()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0; //初始化

		priority_queue<PII, vector<PII>, greater<PII>> heap; 
		heap.push({ 0, 1 });
		while (heap.size())
		{
			auto t = heap.top();
			heap.pop();

			int ver = t.second, distance = t.first;
			if (st[ver])
				continue;

			for (int i = h[ver]; i != -1; i = ne[i]) //遍历当前顶点的边表
				//复杂度降到m*logm
			{
				int j = e[i];

				if (dist[j] > distance + w[i])
				{
					dist[j] = distance + w[i];
					heap.push({dist[j], j});
				}
			}
		}

		if (dist[n] == 0x3f3f3f3f)
			return -1;
	
		return dist[n];
	}

	void addEdge(int a, int b, int c) 
	{
		e[idx] = b; //出点
		w[idx] = c; //权重
		ne[idx] = h[a]; //保存这个编号的边前一条临接边
		h[a] = idx++; //永远保存最后加入的一条临接边

	}

	int main()
	{
		cin >> n >> m;

		memset(h, -1, sizeof h);

		while (m--)
		{
			int a, b, c;
			cin >> a >> b >> c;
			addEdge(a, b, c);
		}

		int t = dijkstra();

		cout << t;

		return 0;

	}
}