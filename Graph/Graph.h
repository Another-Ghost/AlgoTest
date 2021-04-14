#pragma once
#include <iostream>
#include <vector>
#include<queue>
using namespace std;

//bellman-ford 
//һЩ����£����б������Ƶ����·��ֻ����bf
//�������spfa������Ҫ����bf

//bellman-fordҪ�󸺻�������������·���м��ɣ� �����Ƹ���ѭ������
//spfa�㷨Ҫ��ͼ��һ�������ڸ���
namespace bellman_ford {

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

namespace Dijkstra_heap
{


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