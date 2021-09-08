#include "Graph.h"
#include <iostream>
//#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;


class Solution
{


	//const int N = 100;
	vector<int> h, w, e, ne;
	int idx;


	void AddEdge(int a, int b, int c)
	{
		e[idx] = b; //出边
		w[idx] = c;
		ne[idx] = h[a]; //e,w, ne 都可以通过h保存的idx查找
		h[a] = idx++;   //头插法
	}

	int main(int n)
	{
		h.resize(n);
		w.resize(n);
		e.resize(n);
		ne.resize(n);
	}
};

//稠密图用邻接矩阵来存，稀疏图用邻接表来存 
//有向图和无向图的最短路径相同，所以只考虑有向图即可

//在最短路问题里，如果所有自环是正的，自环肯定不会出现在最短路径里；重边的话只保留长度最短的边即可

//Dijksta 

namespace Dijkstra_
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

namespace Dijkstra_heap_
{
	typedef pair<int, int> PII;	// {dist, 顶点编号}

	const int N = 100010;
	int n, m;
	int h[N], w[N], e[N], ne[N], idx; //邻接表	head, weight, edge, next_edge

	int dist[N]; //当前的最短距离
	bool st[N]; //每个点的最短路径是否已经确定了 state



	int dijkstra_heap()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0; //初始化

		priority_queue<PII, vector<PII>, greater<PII>> heap;	//按距离比较的小根堆
		heap.push({ 0, 1 });
		while (heap.size())
		{
			auto t = heap.top();	//t: top
			heap.pop();

			int ver = t.second, distance = t.first;
			if (st[ver])
				continue;
			st[ver] = true;

			for (int i = h[ver]; i != -1; i = ne[i]) //遍历当前顶点的边表 //i: index， j: 入点
				//复杂度降到m*logm
			{
				int j = e[i];

				if (dist[j] > distance + w[i])
				{
					dist[j] = distance + w[i];
					heap.push({ dist[j], j }); //更新过后的dist有潜力成为最小值，需加入到队列中
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

		int t = dijkstra_heap();

		cout << t;

		return 0;

	}
}

//bellman-ford 
//一些情况下，求有边数限制的最短路径只能用bf
//其他情况spfa各方面要优于bf

//bellman-ford要求负环不存在于所求路径中即可， 或限制负环循环次数
//spfa算法要求图中一定不存在负环
namespace Bellman_ford_ 
{

	const int N = 500, M = 10010;

	int n, m, k; //边数不能超过k
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
			memcpy(backup, dist, sizeof(dist)); //因为边数是有限制的，每次遍历前备份一下，防止串联（即用当次遍历中的前面的值更新后面的值）
			for (int j = 0; j < m; ++j)
			{
				int a = edges[j].a;
				int b = edges[j].b;
				int w = edges[j].w;
				dist[b] = min(dist[b], backup[a] + w);
			}
		}

		if (dist[n] > 0x3f3f3f3f / 2) //因为存在负权边，所以不能用0x3f3f3f3f
			return -1;
		else
			return dist[n];
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

//spfa
//队列优化的Bellman-Ford算法
//时间复杂度 平均情况下O(m) ，最坏情况下O(nm) n , 表示点数， 表示边数
namespace Spfa_
{

	const int N = 100010;
	int n, m;
	int h[N], w[N], e[N], ne[N], idx; //邻接表

	int dist[N]; //当前的最短距离
	bool st[N]; 

	void addEdge(int a, int b, int c)
	{
		e[idx] = b; //出点
		w[idx] = c; //权重
		ne[idx] = h[a]; //保存这个编号的边前一条临接边
		h[a] = idx++; //永远保存最后加入的一条临接边

	}

	int spfa()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0;

		queue<int> q;
		q.push(1);
		st[1] = true; //存的是当前点是否在队列当中，防止队列中存储重复的点

		while (q.size())
		{
			int t = q.front();
			q.pop();

			st[t] = false;

			for (int i = h[t]; i != -1; i = ne[i]) //更新所有临边
			{
				int j = e[i];
				if (dist[j] > dist[t] + w[i])
				{
					dist[j] = dist[t] + w[i];
					if (!st[j])
					{
						q.push(j);
						st[j] = true;
					}
				}
			}
		}

		if (dist[n] == 0x3f3f3f3f)
			return -1;
		return dist[n];

	}

	int cnt[N];

	void add(int a, int b, int c)
	{
		e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
	}

	bool SpfaNegativeLoop()
	{
		queue<int> q;
		//无需初始化dist
		for (int i = 1; i <= n; i++) //如果只加入一个点，可能漏判该点到不了的负环
		{
			st[i] = true;
			q.push(i);
		}

		while (q.size())
		{
			int t = q.front();
			q.pop();

			st[t] = false;

			for (int i = h[t]; i != -1; i = ne[i])
			{
				int j = e[i];
				if (dist[j] > dist[t] + w[i])
				{
					dist[j] = dist[t] + w[i];
					cnt[j] = cnt[t] + 1;

					if (cnt[j] >= n) return true;
					if (!st[j])
					{
						q.push(j);
						st[j] = true;
					}
				}
			}
		}

		return false;
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

		int t = spfa();

		cout << t;

		return 0;

	}
}

//求全部顶点之间的最短路径，时间复杂度是O(n^3)
namespace Floyd_
{
	//把邻接矩阵变成最短距离矩阵

	//图中可以有负权，但不能有负权回路

	//基于动态规划 d[k, i, j] = d[k-1, i, k] + d[k-1, k, j];
	//从i点出发，只经过k这些中间点到达j的最短路径

	const int N = 210;
	const int INF = 1e9;
	int n, m, Q;
	int d[N][N];

	void floyd()
	{
		for (int k = 1; k <= n; ++k)
		{
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
				{
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
		}
	}

	int main()
	{
		cin >> n >> m >> Q;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; i <= n; ++j)
				if (i == j)
					d[i][j] = 0;
				else
					d[i][j] = INF;

		while (m--)
		{
			int a, b, w;
			cin >> a >> b >> w;
			d[a][b] = min(d[a][b], w);
		}

		floyd();

		while (Q--)
		{
			int a, b;
			cin >> a >> b;
			if (d[a][b] > INF / 2)
				puts("impossible");
			else
				cout << d[a][b];
		}

		return 0;
	}

}

//求最小生成树
//时间复杂度是O(n^2+m), 表示点数， 表示边数
namespace Prim_
{

	const int N = 510;
	const int INF = 0x3f3f3f3f;

	int n, m;
	int g[N][N];
	int dist[N];
	bool st[N];

	int prim()
	{
		memset(dist, 0x3f, sizeof dist);

		int res = 0; //最小权重和
		for (int i = 0; i < n; ++i)
		{
			int t = -1;
			for (int j = 1; j <= n; ++j)
				if (!st[j] && (t == -1 || dist[t] > dist[j]))
					t = j;
			if (i && dist[t] == INF)
				return INF; //不联通

			if (i)
				res += dist[t]; //先累加再更新，否则如果存在负权自环会出问题

			for (int j = 1; j <= n; ++j)
				dist[j] = min(dist[j], g[t][j]); //Dijksta是dist[t] + g[t][j]

			st[t] = true;
		}

		return res;
	}

	int main()
	{
		memset(g, 0x3f, sizeof g);

		while (m--)
		{
			int a, b, c;
			cin >> a >> b >> c;
			g[a][b] = min(g[a][b], c);
		}

		int t = prim();

		if (t = INF)
			puts("impossible");
		else
			cout << t;

		return 0;
	}
}

//时间复杂度是O(mlogm)
namespace Kruskal_
{
	//时间瓶颈为排序算法， 但由于排序算法常数小，Kruskal表现很好
	const int N = 200010;
	int n, m;
	int p[N];
	struct Edge
	{
		int a, b, w;
		bool operator < (const Edge& W) const
		{
			return w < W.w;
		}
	}edges[N];

	int find(int x)
	{
		if (p[x] != x)
			p[x] = find(p[x]);
		return p[x];
	}

	int main()
	{
		cin >> n >> m;
		for (int i = 0; i < m; ++i)
		{
			int a, b, w;
			cin >> a >> b >> w;
			edges[i] = { a, b, w };
		}

		sort(edges, edges + m);
		for (int i = 1; i <= n; ++i)
		{
			p[i] = i;
		}
		int res = 0, cnt = 0;

		for (int i = 0; i < m; ++i)
		{
			int a = edges[i].a, b = edges[i].b, w = edges[i].w;
			a = find(a), b = find(b);
			if (a != b)
			{
				p[find(a)] = find(b);
				res += w;
				++cnt;
			}
		}
		if (cnt < n - 1)
			puts("impossible");
		else
			cout << res;

		return 0;
	}

}

//可以搜到最短路（前提是边的权重相同）
void BFS()
{

}