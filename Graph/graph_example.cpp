#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 输入是一个二维数组，第二维长度为3 ，例如[[1, 2, 4]], 代表这个网络只能从1节点传输到2节点，传输耗时为4秒，只能单向传输。另外两个参数，其中一个代表节点的总个数，另外一个代表第几个节点作为起点。输出为一个INT类型的值。
     * @param network int整型vector<vector<>> 二维整型数组
     * @param N int整型 INT类型标量，代表节点数量
     * @param K int整型 INT类型变量，代表起始节点
     * @return int整型
     */
	int min_sum = INT_MAX;

    


    void DFS(vector<vector<int>>& table, vector<bool>& visited, int& n, int& sum, int v)
    {
        if (n == table.size())
        {
            min_sum = min(sum, min_sum);
        }

        if (visited[v] == false)
        {
            return;
        }
        visited[v] = true;
        ++n;

        for (int i = 0; i < table[v].size(); ++i)
        {
            if (table[v][i] > 0)
            {
                sum += table[v][i];
                DFS(table, visited, n, sum, v);
                sum -= table[v][i];
            }
        }

        visited[v] = false;
        --n;
    }

    int CalDelayTime(vector<vector<int> >& network, int N, int K) {
        // write code here
        vector<vector<int>> table(N + 1);
        for (auto& v : table)
        {
            v.resize(N + 1);
        }
        for (const auto& net : network)
        {
            table[net[0]][net[1]] = net[2];
            table[net[1]][net[0]] = net[2];
        }


        vector<bool> visited(N);
        int n = 0;
        int sum = 0;
        DFS(table, visited, n, sum, K);

        return min_sum == INT_MAX ? -1 : min_sum;
    }
};


class Solution743 {
public:
	typedef pair<int, int> PII;
	vector<int> h, w, e, ne;
	int idx = 0;



	void AddEdge(int a, int b, int weight)
	{
		e[idx] = b;
		w[idx] = weight;
		ne[idx] = h[a];
		h[a] = idx++;
	}

	//Dijkstra
	int networkDelayTime(vector<vector<int>>& times, int n, int k) {
		int M = pow(n + 1, 2);
		h.resize(n + 1, -1);
		e.resize(M);
		w.resize(M);
		ne.resize(M);
		vector<int> dist(n + 1, INT_MAX / 2);    //一定要为n + 1
		vector<bool> st(n + 1);

		for (auto& edge : times)
		{
			AddEdge(edge[0], edge[1], edge[2]);
		}

		priority_queue<PII, vector<PII>, greater<PII>> heap;	//小顶堆
		dist[k] = 0;
		heap.push({ 0, k });


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
		for (int i = 1; i < n + 1; ++i) //以1开始，以n + 1结束
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
};

// 9/9 Tencent
