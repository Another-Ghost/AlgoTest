#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> PDV;

typedef pair<int, int> PWV;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
	vector<vector<PWV>> g(n);
	for (const auto& t : times)
	{
		g[t[0]].emplace_back(t[2], t[1]);
	}

	vector<int> dist(n, INT_MAX / 2);
	vector<bool> st(n);
	dist[k] = 0;

	priority_queue<PDV, vector<PDV>, greater<PDV>> heap;
	heap.push({ 0, k });

	while (!heap.empty())
	{
		auto t = heap.top();
		heap.pop();

		int ver = t.second, distance = t.first;
		if (st[ver])
			continue;
		st[ver] = true;


		for (const auto& edge : g[ver])
		{
			int j = edge.second, w = edge.first;
			if (dist[j] > distance + w)
			{
				dist[j] = distance + w;
				heap.push({ dist[j], j });
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		//cout<< dist[i] << ' ';
		if (dist[i] != INT_MAX / 2)
			ans = max(ans, dist[i]);    //结果为最短路径中的最大值
		else
		{
			return -1;
		}
	}

	return ans;
}

int main()
{
   
}

