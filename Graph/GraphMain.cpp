#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> Edge;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
	vector<vector<Edge>> g(n);
	for (const auto& f : flights)
		g[f[0]].emplace_back(f[2], f[1]);

	vector<int> dist(n, INT_MAX / 2);
	vector<int> cnt(n);
	vector<bool> st(n);
	dist[src] = 0;

	priority_queue<Edge, vector<Edge>, greater<Edge>> heap;
	heap.push({ 0, src });
	while (heap.size())
	{
		auto t = heap.top();
		heap.pop();
		int a = t.second, distance = t.first;
		//if (st[a])
		//	continue;
		//st[a] = true;
		for (const auto& e : g[a])
		{
			int b = e.second, w = e.first;
			if (cnt[a] <= K)
			{
				dist[b] = distance + w;
				heap.push({ dist[b], b });
				cnt[b] = cnt[a] + 1;
			}
		}
	}

	return dist[dst] == INT_MAX / 2 ? -1 : dist[dst];
}

class Solution743 {
public:
	typedef pair<int, int> PII;
	int N;
	vector<int> h, w, e, ne;
	int idx = 0;

	vector<int> dist;
	vector<bool> st;

	void AddEdge(int a, int b, int weight)
	{
		e[idx] = b;
		w[idx] = weight;
		ne[idx] = h[a];
		h[a] = idx++;
	}

	int Dijkstra(int v)
	{
		priority_queue<PII, vector<PII>, greater<PII>> heap;	//小顶堆
		dist[v] = 0;
		heap.push({ 0, v });


		while (heap.size())
		{
			auto t = heap.top();
			heap.pop();

			int ver = t.second, distance = t.first;
			if (st[ver])
				continue;
			st[ver] = true;
			for (int i = h[ver]; i != -1; i = ne[i]) //i index， j入点
			{
				int j = e[i];

				if (dist[j] > distance + w[i])
				{
					dist[j] = distance + w[i];
					heap.push({ dist[j], j });
				}
			}
		}

		int ans = 0;
		for (int i = 1; i < N; ++i)
		{
			if (dist[i] != INT_MAX / 2)
			{
				ans = max(ans, dist[i]);
			}
			else
			{
				return -1;
			}
		}

		return ans;
	}

	int networkDelayTime(vector<vector<int>>& times, int n, int k) {
		N = n + 1;
		int M = pow(n + 1, 2);
		h.resize(N, -1);
		e.resize(M);
		w.resize(M);
		ne.resize(M);
		dist.resize(N, INT_MAX / 2);
		st.resize(N);

		for (auto& edge : times)
		{
			AddEdge(edge[0], edge[1], edge[2]);
		}

		//int ans = Dijkstra(k);
		//cout << ans <<endl;
		//return ans;
		return Dijkstra(k);
	}
};

const int N = 20;

int col[N], dg[N * 2], udg[N * 2];

int n1;

char g[N][N];

vector<vector<string>> ans;

void DFS(int u)
{
	if (u == n1)
	{
		vector<string> grid;
		for (int i = 0; i < n1; ++i)
		{
			string row;
			for (int j = 0; j < n1; ++i)
			{
				row += g[i][j];
			}
			grid.emplace_back(row);
		}
		ans.emplace_back(grid);
		return;
	}

	for (int i = 0; i < n1; ++i)  //u: y, i: x
	{
		if (!col[i] && !dg[u + i] && !udg[n1 - u + i])    //b1 = y - x, b2 = y + x; 截距b1存在小于0的情况，所以变换成 y - x + n
		{
			g[u][i] = 'Q';
			col[i] = dg[u + i] = udg[n1 - u + i] = true;
			DFS(u + 1);
			col[i] = dg[u + i] = udg[n1 - u + i] = false;
			g[u][i] = '.';
		}
	}
}




class Solution51 {





public:
	vector<vector<string>> solveNQueens(int n) {
		n1 = n;
		//ans.resize()

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				g[i][j] = '.';
			}
		}
		DFS(0);
		return ans;
	}
};

int main()
{
	//vector<vector<int>> flights = { {0,1,1}, {1,2,1}, {0,2,5}, {2,3,1} };
	//findCheapestPrice(4, flights, 0, 3, 1);

	vector<vector<int>> times = { {2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
	Solution51 solution;
	solution.solveNQueens(9);


}

