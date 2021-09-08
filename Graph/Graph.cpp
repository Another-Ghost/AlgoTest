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
		e[idx] = b; //����
		w[idx] = c;
		ne[idx] = h[a]; //e,w, ne ������ͨ��h�����idx����
		h[a] = idx++;   //ͷ�巨
	}

	int main(int n)
	{
		h.resize(n);
		w.resize(n);
		e.resize(n);
		ne.resize(n);
	}
};

//����ͼ���ڽӾ������棬ϡ��ͼ���ڽӱ����� 
//����ͼ������ͼ�����·����ͬ������ֻ��������ͼ����

//�����·�������������Ի������ģ��Ի��϶�������������·����رߵĻ�ֻ����������̵ı߼���

//Dijksta 

namespace Dijkstra_
{

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

namespace Dijkstra_heap_
{
	typedef pair<int, int> PII;	// {dist, ������}

	const int N = 100010;
	int n, m;
	int h[N], w[N], e[N], ne[N], idx; //�ڽӱ�	head, weight, edge, next_edge

	int dist[N]; //��ǰ����̾���
	bool st[N]; //ÿ��������·���Ƿ��Ѿ�ȷ���� state



	int dijkstra_heap()
	{
		memset(dist, 0x3f, sizeof dist);
		dist[1] = 0; //��ʼ��

		priority_queue<PII, vector<PII>, greater<PII>> heap;	//������Ƚϵ�С����
		heap.push({ 0, 1 });
		while (heap.size())
		{
			auto t = heap.top();	//t: top
			heap.pop();

			int ver = t.second, distance = t.first;
			if (st[ver])
				continue;
			st[ver] = true;

			for (int i = h[ver]; i != -1; i = ne[i]) //������ǰ����ı߱� //i: index�� j: ���
				//���ӶȽ���m*logm
			{
				int j = e[i];

				if (dist[j] > distance + w[i])
				{
					dist[j] = distance + w[i];
					heap.push({ dist[j], j }); //���¹����dist��Ǳ����Ϊ��Сֵ������뵽������
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

		int t = dijkstra_heap();

		cout << t;

		return 0;

	}
}

//bellman-ford 
//һЩ����£����б������Ƶ����·��ֻ����bf
//�������spfa������Ҫ����bf

//bellman-fordҪ�󸺻�������������·���м��ɣ� �����Ƹ���ѭ������
//spfa�㷨Ҫ��ͼ��һ�������ڸ���
namespace Bellman_ford_ 
{

	const int N = 500, M = 10010;

	int n, m, k; //�������ܳ���k
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
			memcpy(backup, dist, sizeof(dist)); //��Ϊ�����������Ƶģ�ÿ�α���ǰ����һ�£���ֹ���������õ��α����е�ǰ���ֵ���º����ֵ��
			for (int j = 0; j < m; ++j)
			{
				int a = edges[j].a;
				int b = edges[j].b;
				int w = edges[j].w;
				dist[b] = min(dist[b], backup[a] + w);
			}
		}

		if (dist[n] > 0x3f3f3f3f / 2) //��Ϊ���ڸ�Ȩ�ߣ����Բ�����0x3f3f3f3f
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
//�����Ż���Bellman-Ford�㷨
//ʱ�临�Ӷ� ƽ�������O(m) ��������O(nm) n , ��ʾ������ ��ʾ����
namespace Spfa_
{

	const int N = 100010;
	int n, m;
	int h[N], w[N], e[N], ne[N], idx; //�ڽӱ�

	int dist[N]; //��ǰ����̾���
	bool st[N]; 

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
		st[1] = true; //����ǵ�ǰ���Ƿ��ڶ��е��У���ֹ�����д洢�ظ��ĵ�

		while (q.size())
		{
			int t = q.front();
			q.pop();

			st[t] = false;

			for (int i = h[t]; i != -1; i = ne[i]) //���������ٱ�
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
		//�����ʼ��dist
		for (int i = 1; i <= n; i++) //���ֻ����һ���㣬����©�иõ㵽���˵ĸ���
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

//��ȫ������֮������·����ʱ�临�Ӷ���O(n^3)
namespace Floyd_
{
	//���ڽӾ�������̾������

	//ͼ�п����и�Ȩ���������и�Ȩ��·

	//���ڶ�̬�滮 d[k, i, j] = d[k-1, i, k] + d[k-1, k, j];
	//��i�������ֻ����k��Щ�м�㵽��j�����·��

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

//����С������
//ʱ�临�Ӷ���O(n^2+m), ��ʾ������ ��ʾ����
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

//ʱ�临�Ӷ���O(mlogm)
namespace Kruskal_
{
	//ʱ��ƿ��Ϊ�����㷨�� �����������㷨����С��Kruskal���ֺܺ�
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

//�����ѵ����·��ǰ���Ǳߵ�Ȩ����ͬ��
void BFS()
{

}