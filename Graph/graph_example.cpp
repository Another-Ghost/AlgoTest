#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     *
     * ������һ����ά���飬�ڶ�ά����Ϊ3 ������[[1, 2, 4]], �����������ֻ�ܴ�1�ڵ㴫�䵽2�ڵ㣬�����ʱΪ4�룬ֻ�ܵ����䡣������������������һ������ڵ���ܸ���������һ������ڼ����ڵ���Ϊ��㡣���Ϊһ��INT���͵�ֵ��
     * @param network int����vector<vector<>> ��ά��������
     * @param N int���� INT���ͱ���������ڵ�����
     * @param K int���� INT���ͱ�����������ʼ�ڵ�
     * @return int����
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
		vector<int> dist(n + 1, INT_MAX / 2);    //һ��ҪΪn + 1
		vector<bool> st(n + 1);

		for (auto& edge : times)
		{
			AddEdge(edge[0], edge[1], edge[2]);
		}

		priority_queue<PII, vector<PII>, greater<PII>> heap;	//С����
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
			for (int i = h[ver]; i != -1; i = ne[i]) //i index�� j���
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
		for (int i = 1; i < n + 1; ++i) //��1��ʼ����n + 1����
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
