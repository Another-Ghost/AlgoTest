#pragma once




//bellman-ford 
//һЩ����£����б������Ƶ����·��ֻ����bf
//�������spfa������Ҫ����bf

//bellman-fordҪ�󸺻�������������·���м��ɣ� �����Ƹ���ѭ������
//spfa�㷨Ҫ��ͼ��һ�������ڸ���
namespace bellman_ford {
#include <iostream>

	using namespace std;
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
			memcpy(backup, dist, sizeof(dist)); //ÿ�α���ǰ����һ��
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

//����ͼ���ڽӾ������棬ϡ��ͼ���ڽӱ�����
//����ͼ������ͼ�����·����ͬ������ֻ��������ͼ����

//�����·�������������Ի������ģ��Ի��϶�������������·����رߵĻ�ֻ����������̵ı߼���
namespace Dijkstra
{
#include <iostream>
#include <cstring>
	using namespace std;

	const int N = 510;
	int n, m;
	int g[N][N]; //�ڽӾ���
	int dist[N]; //��ǰ����̾���
	bool st[N]; //ÿ��������·���Ƿ��Ѿ�ȷ����

	int dijkstra()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0; //��ʼ��
		
		for (int i = 0; i < n; ++i)
		{
			int t = -1;
			for (int j = 1; j <= n; ++j) 
				if (!st[j] && (t == -1 || dist[t] > dist[j])) //1Ϊ��㣨����0��
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

//Dijksta���Ż���
//������ϡ��ͼ

namespace Spfa
{
#include <vector>
#include<queue>

	typedef pair<int, int> PII;

	const int N = 100010;
	int n, m;
	int h[N], w[N], e[N], ne[N], idx; //�ڽӱ�

	int dist[N]; //��ǰ����̾���
	bool st[N]; //ÿ��������·���Ƿ��Ѿ�ȷ����

	int dijkstra()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0; //��ʼ��

		priority_queue<PII, vector<PII>, greater<PII>> heap; 
		heap.push({ 0, 1 });
		while (heap.size())
		{
			auto t = heap.top();
			heap.pop();

			int ver = t.second, distance = t.first;
			if (st[ver])
				continue;

			for (int i = h[ver]; i != -1; i = ne[i]) //������ǰ����ı߱�
				//���ӶȽ���m*logm
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
		e[idx] = b; //����
		w[idx] = c; //Ȩ��
		ne[idx] = h[a]; //���������ŵı�ǰһ���ٽӱ�
		h[a] = idx++; //��Զ�����������һ���ٽӱ�

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

//spfa
namespace Dijkstra_heap
{


	const int N = 100010;
	int n, m;
	int h[N], w[N], e[N], ne[N], idx; //�ڽӱ�

	int dist[N]; //��ǰ����̾���
	bool st[N]; //ÿ��������·���Ƿ��Ѿ�ȷ����

	void addEdge(int a, int b, int c)
	{
		e[idx] = b; //����
		w[idx] = c; //Ȩ��
		ne[idx] = h[a]; //���������ŵı�ǰһ���ٽӱ�
		h[a] = idx++; //��Զ�����������һ���ٽӱ�

	}

	int spfa()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0;

		queue<int> q;
		q.push(1);
		st[1] = true; //�˴�st�������ǵ�ǰ���Ƿ��ڶ��е��У���ֹ�洢�ظ��ĵ�
		
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

namespace Floyd
{
//���ڽӾ�������̾������

//ͼ�п����и�Ȩ���������и�Ȩ��·

//���ڶ�̬�滮 d[k, i, j] = d[k-1, i, k] + d[k-1, k, j];
//��i�������ֻ����k��Щ�м�㵽��j�����·��

#include <iostream>
using namespace std;

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
				if (i == j)
					d[i][j] = 0;
				else
					d[i][j] = INF;
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

namespace Prim
{
#include <iostream>
#include <cstring>

	using namespace std;

	const int N = 510;
	const int INF = 0x3f3f3f3f;

	int n, m;
	int g[N][N];
	int dist[N];
	bool st[N];

	int prim()
	{
		memset(dist, 0x3f, sizeof dist);

		int res = 0; //��СȨ�غ�
		for (int i = 0; i < n; ++i)
		{
			int t = -1;
			for (int j = 1; j <= n; ++j)
				if (!st[j] && (t == -1 || dist[t] > dist[j]))
					t = j;
			if (i && dist[t] == INF)
				return INF; //����ͨ

			if (i)
				res += dist[t]; //���ۼ��ٸ��£�����������ڸ�Ȩ�Ի��������

			for (int j = 1; j <= n; ++j)
				dist[j] = min(dist[j], g[t][j]); //Dijksta��dist[t] + g[t][j]

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
			g[a][b] = g[b][a] min(g[a][b], c);
		}

		int t = prim();

		if (t = INF)
			puts("impossible")
		else
			cout << t;
	}
}

namespace Kruskal
{
	//ʱ��ƿ��Ϊ�����㷨�� �����������㷨����С��Kruskal���ֺܺ�

	#include <iostream>
#include <algorithm>
	
	using namespace std;
	 
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