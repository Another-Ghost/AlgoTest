#include "GraphTemplate.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//朴素版，时间复杂度O(N^2)（N为顶点数），适用于稠密图
//注意一般题目顶点下标以1为起点，注意变更数组长度和遍历起始值
//LeetCode 743
namespace dijkstra
{
	int Dijkstra(vector<vector<int>>& g, int start, int end)
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

//堆优化版，时间复杂度mlogm, 约等于mlogn，（因为m一定小于等于n^2，logm < logn^2 = 2logn）
//且n > 4时，2logn一定小于n，所以当n > 4时，堆优化版本时间一定低于朴素版
namespace dijkstra_heap{
	const int N = 300;
	
	typedef pair<int, int> PII;	// {dist, 顶点编号}

	typedef pair<int, int> Edge; //代表边 {权重，顶点编号}

	//struct Edge
	//{
	//	int w; // 权重
	//	int b; // a->b

	//	
	//	Edge(int w_, int b_) : v(w_), w(b_) {}
	//};

	
	//void Add(int a, int b, int w)
	//{
	//	g[a].emplace_back(w, b);
	//}

	int Dijkstra(vector<vector<int>>& edges, int n, int start, int end)
	{
		vector<vector<Edge>> g(n);	//邻接表
		for (const auto& e : edges)
		{
			g[e[0]].emplace_back(e[2], e[1]);
		}


		vector<int> dist(n, INT_MAX / 2); //g中的标记不存在的边的最大值不能大于 INT_MAX / 2
		vector<bool> st(n); //为true说明该点已在当前已确定最短路径的点的集合

		dist[start] = 0; //初始化

		priority_queue<PII, vector<PII>, greater<PII>> heap; //按距离比较的小根堆（pair的greater模板函数会以pair的first元素进行比较）
		heap.push({ 0, start });
		while (!heap.empty())
		{
			auto t = heap.top();
			heap.pop();

			int ver = t.second, distance = t.first;
			if (st[ver])
				continue;
			st[ver] = true;

			for (const auto& e : g[ver]) //遍历当前顶点的边表，总次数为m
			{
				int b = e.second, w = e.first;
				if (dist[b] > distance + w)
				{
					dist[b] = distance + w;
					heap.push({ dist[b], b }); //更新过后的dist有潜力成为最小值，需加入到队列中
					//此步时间复杂度为O(logm) (因为会有重复顶点的边，否者为log（n）)，所以整体复杂度为O（mlog（m））
				}
			}
		}

		return dist[end] == INT_MAX / 2 ? -1 : dist[end];
	}
	
}


//存在负权边情况下，求有边数限制的最短路径只能用bf
//其他情况spfa各方面要优于bf
//要求负环不存在于所求路径中即可，或限制负环循环次数
namespace bellman_ford
{
	struct Edge
	{
		int a, b, w;
	};

	int BellmanFord(vector<vector<int>> edges, int n, int start, int end, int k) //第一个参数相当于vector<Edge>， 边数不能超过k
	{
		vector<int> dist(n, INT_MAX / 2);
		vector<int> backup(n);
		dist[start] = 0;
		
		for (int i = 0; i < k; ++i)
		{
			backup.assign(dist.begin(), dist.end()); //因为边数是有限制的，每次遍历前备份一下，防止串联（即用当次遍历中的前面的值更新后面的值）
			for (int j = 0; j < edges.size(); ++j) //暴力遍历n次所有边，所以复杂度为n*m
			{
				int a = edges[j][0];
				int b = edges[j][1];
				int w = edges[j][2];
				dist[b] = min(dist[b], backup[a] + w); //此处用backup数组更新
			}
		}
		
		return dist[end] > INT_MAX / 4 ? -1 : dist[end]; //因为存在负权边，所以不能用INT_MAX / 2
	}
}

//原始的spfa算法要求图中一定不存在负环（因为如果存在负环，则队列永不为空）
namespace spfa
{
	typedef pair<int, int> Edge;

	int Spfa(vector<vector<int>>& edges, int n, int start, int end)
	{
		vector<vector<Edge>> g(n);	//邻接表
		for (const auto& e : edges)
		{
			g[e[0]].emplace_back(e[2], e[1]);	
		}

		vector<int> dist(n, INT_MAX / 2);
		vector<bool> st(n);  //存的是当前点是否在队列当中，防止队列中存储重复的点

		queue<int> q;
		q.push(start);
		st[start] = true;

		while (!q.empty())
		{
			int t = q.front();
			q.pop();
			st[t] = false;

			for (const auto& e : g[t]) //更新所有临边
			{
				int b = e.second, w = e.first;
				if (dist[b] > dist[t] + w) //当dist[a]减小时dist[b]才会变小，所以只把变小顶点的加入队列
				{
					dist[b] = dist[t] + w;
					if (!st[b])
					{
						q.push(b);
						st[b] = true;
					}
				}
			}
		}

		return dist[end] == INT_MAX / 2 ? -1 : dist[end];
	}

	bool SpfaNegativeLoop(vector<vector<int>>& edges, int n)
	{
		vector<vector<Edge>> g(n);
		for (const auto& e : edges)
		{
			g[e[0]].emplace_back(e[2], e[1]);
			
		}

		vector<int> dist(n); //因为是判断有没有负环，无需初始化为无穷值
		vector<bool> st(n);
		vector<int> cnt(n);

		queue<int> q;
		for (int i = 0; i < n; ++i) //如果只加入一个点，可能漏判该点到不了的负环
		{
			st[i] = true;
			q.push(i);
		}
	
		while (!q.empty())
		{
			int t = q.front();
			q.pop();
			st[t] = false;

			for (const auto& e : g[t])
			{
				int b = e.second, w = e.first;
				if (dist[b] > dist[t] + w)
				{
					dist[b] = dist[t] + w;
					cnt[b] = cnt[t] + 1; //核心

					if (cnt[b] > n)
						return true;

					if (!st[b])
					{
						q.push(b);
						st[b] = true;
					}
				}
			}
		}

		return false;
	}

}