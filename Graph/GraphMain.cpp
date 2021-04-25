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

int main()
{
	vector<vector<int>> flights = { {0,1,1}, {1,2,1}, {0,2,5}, {2,3,1} };

	findCheapestPrice(4, flights, 0, 3, 1);
}

