#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//Tencent 4/18 5/5
/*
2 2 6
1 1
1 1

2 2 5
1 1
1 1
*/

//图的广度搜索（层序遍历） 
//状态队列（我乱起的） 
enum Direction
{
	eEast,
	eWest,
	eNorth,
	eSouth,
	eStart
};

struct State
{
	int t;
	int i;
	int j;
	Direction from;
	int score;
	State(int t_, int i_, int j_, Direction from_, int score_) :t(t_), i(i_), j(j_), from(from_), score(score_) {}
};


void WhacAMole()
{
	int n, m, t;
	cin >> n >> m >> t;

	vector<vector<int>> mp(n, (vector<int>)(m));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> mp[i][j];
		}
	}

	int ans = 0;

	queue<State> q;
	//根据题意每次必须移动一格且不能原路返回，所以默认mp大小至少是2 x 2
	//且默认起点在（0，0），所以先把（0,1），（1,0）入队
	q.push(State(1, 1, 0, eNorth, (1 % mp[1][0] == 0)));
	q.push(State(1, 0, 1, eEast, (1 % mp[0][1] == 0)));
	while (!q.empty())
	{
		State cur = q.front();
		q.pop();

		if (cur.i == n - 1 && cur.j == m - 1 && cur.t == t)	//默认终点位置是（n-1, m -1), 且必须t时刻正好走到终点才可以
		{
			ans = max(ans, cur.score);
		}

		int t_new = cur.t + 1;
		if (t_new > t)
			continue;

		if (cur.i > 0 && cur.from != eNorth)	//是否可向上走
		{
			int i_new = cur.i - 1;
			int j_new = cur.j;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)	//如果当前位置在剩余时间内到达不了终点则略过	
			{
				q.push(State(t_new, i_new, j_new, eSouth, cur.score + (t_new % mp[i_new][j_new] == 0))); //t_new % mp[i_new][j_new]为0说明代表当前位置计时已到
			}
		}

		if (cur.i < n - 1 && cur.from != eSouth)
		{
			int i_new = cur.i + 1;
			int j_new = cur.j;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)
			{
				q.push(State(t_new, i_new, j_new, eNorth, cur.score + (t_new % mp[i_new][j_new] == 0)));
			}
		}

		if (cur.j > 0 && cur.from != eEast)
		{
			int i_new = cur.i;
			int j_new = cur.j - 1;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)
			{
				q.push(State(t_new, i_new, j_new, eWest, cur.score + (t_new % mp[i_new][j_new] == 0)));
			}
		}

		if (cur.j < m - 1 && cur.from != eWest)
		{
			int i_new = cur.i;
			int j_new = cur.j + 1;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)
			{
				q.push(State(t_new, i_new, j_new, eEast, cur.score + (t_new % mp[i_new][j_new] == 0)));
			}
		}
	}

	cout << ans << endl;
}

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
class Solution9_9_Tencent_2_1
{
	static constexpr int dirs[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

	int main() {
		//int a;
		//cin >> a;
		int times;
		cin >> times;

		while (times--)
		{
			int N;
			cin >> N;

			int S;
			cin >> S;

			int dest_x, dest_y;
			cin >> dest_x >> dest_y;

			vector<vector<int>> grid(N, vector<int>(N, 0));

			queue<pair<int, int>> q;

			for (int i = 0; i < S; ++i)
			{
				int x, y;
				cin >> x;
				cin >> y;
				grid[x - 1][y - 1] = 1;
			}

			vector<vector<int>> visited(N, vector<int>(N));

			q.push({ 0, 0 });
			visited[0][0] = true;

			for (int step = 1; q.size() > 0; ++step)
			{
				int cnt = q.size();
				for (int _ = 0; _ < cnt; ++_)
				{
					auto cur_pos = q.front();
					q.pop();
					for (int i = 0; i < 4; ++i)
					{
						int new_x = cur_pos.first + dirs[i][0];
						int new_y = cur_pos.second + dirs[i][1];
						if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < N )
						{
							if (new_x == dest_x && new_y == dest_y)
							{
								cout << step << endl;
								return;
							}
							if (grid[new_x][new_y] != !visited[new_x][new_y])
							{
								q.push({ new_x, new_y });
								visited[new_x][new_y] = true;
							}

						}
					}

				}
			}

			cout << -1 << endl;

		}
	}
};