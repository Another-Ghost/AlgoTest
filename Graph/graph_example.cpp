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

//ͼ�Ĺ����������������� 
//״̬���У�������ģ� 
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
	//��������ÿ�α����ƶ�һ���Ҳ���ԭ·���أ�����Ĭ��mp��С������2 x 2
	//��Ĭ������ڣ�0��0���������Ȱѣ�0,1������1,0�����
	q.push(State(1, 1, 0, eNorth, (1 % mp[1][0] == 0)));
	q.push(State(1, 0, 1, eEast, (1 % mp[0][1] == 0)));
	while (!q.empty())
	{
		State cur = q.front();
		q.pop();

		if (cur.i == n - 1 && cur.j == m - 1 && cur.t == t)	//Ĭ���յ�λ���ǣ�n-1, m -1), �ұ���tʱ�������ߵ��յ�ſ���
		{
			ans = max(ans, cur.score);
		}

		int t_new = cur.t + 1;
		if (t_new > t)
			continue;

		if (cur.i > 0 && cur.from != eNorth)	//�Ƿ��������
		{
			int i_new = cur.i - 1;
			int j_new = cur.j;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)	//�����ǰλ����ʣ��ʱ���ڵ��ﲻ���յ����Թ�	
			{
				q.push(State(t_new, i_new, j_new, eSouth, cur.score + (t_new % mp[i_new][j_new] == 0))); //t_new % mp[i_new][j_new]Ϊ0˵������ǰλ�ü�ʱ�ѵ�
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