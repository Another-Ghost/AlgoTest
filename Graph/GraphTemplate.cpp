#include "GraphTemplate.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//���ذ棬ʱ�临�Ӷ�O(N^2)��NΪ���������������ڳ���ͼ
//ע��һ����Ŀ�����±���1Ϊ��㣬ע�������鳤�Ⱥͱ�����ʼֵ
//LeetCode 743
namespace dijkstra
{
	int Dijkstra(vector<vector<int>>& g, int start, int end)
	{
		int n = g.size();
		vector<int> dist(n, INT_MAX / 2); //g�еı�ǲ����ڵıߵ����ֵ���ܴ��� INT_MAX / 2
		vector<bool> st(n); //Ϊtrue˵���õ����ڵ�ǰ��ȷ�����·���ĵ�ļ���
		dist[start] = 0; //�ĸ���Ϊ�����Ȱ��ĸ�����Ϊ0	
		for (int i = 0; i < n; ++i)
		{
			int t = -1; //���±�
			for (int j = 0; j < n; ++j)
			{
				if (!st[j] && (t == -1 || dist[t] > dist[j]))	//�ҵ���ǰ����start����ĵ�
					t = j;
			}
			st[t] = true; //���õ���� ��ǰ��ȷ�����·���ĵ� �ļ���

			for (int j = 0; j < n; ++j)
				dist[j] = min(dist[j], dist[t] + g[t][j]);	//�øõ�t���������㵽start�ľ���
		}

		return (dist[end] != INT_MAX / 2) ? dist[end] : -1;
	}
}

//���Ż��棬ʱ�临�Ӷ�mlogm, Լ����mlogn������Ϊmһ��С�ڵ���n^2��logm < logn^2 = 2logn��
//��n > 4ʱ��2lognһ��С��n�����Ե�n > 4ʱ�����Ż��汾ʱ��һ���������ذ�
namespace dijkstra_heap{
	const int N = 300;
	
	typedef pair<int, int> PII;	// {dist, ������}

	typedef pair<int, int> Edge; //����� {Ȩ�أ�������}

	//struct Edge
	//{
	//	int w; // Ȩ��
	//	int b; // a->b

	//	
	//	Edge(int w_, int b_) : v(w_), w(b_) {}
	//};

	
	//void Add(int a, int b, int w)
	//{
	//	g[a].emplace_back(w, b);
	//}

	int Dijkstra(vector<vector<int>>& edges, int n, int start, int end)
	{
		vector<vector<Edge>> g(n);	//�ڽӱ�
		for (const auto& e : edges)
		{
			g[e[0]].emplace_back(e[2], e[1]);
		}


		vector<int> dist(n, INT_MAX / 2); //g�еı�ǲ����ڵıߵ����ֵ���ܴ��� INT_MAX / 2
		vector<bool> st(n); //Ϊtrue˵���õ����ڵ�ǰ��ȷ�����·���ĵ�ļ���

		dist[start] = 0; //��ʼ��

		priority_queue<PII, vector<PII>, greater<PII>> heap; //������Ƚϵ�С���ѣ�pair��greaterģ�庯������pair��firstԪ�ؽ��бȽϣ�
		heap.push({ 0, start });
		while (!heap.empty())
		{
			auto t = heap.top();
			heap.pop();

			int ver = t.second, distance = t.first;
			if (st[ver])
				continue;
			st[ver] = true;

			for (const auto& e : g[ver]) //������ǰ����ı߱��ܴ���Ϊm
			{
				int b = e.second, w = e.first;
				if (dist[b] > distance + w)
				{
					dist[b] = distance + w;
					heap.push({ dist[b], b }); //���¹����dist��Ǳ����Ϊ��Сֵ������뵽������
					//�˲�ʱ�临�Ӷ�ΪO(logm) (��Ϊ�����ظ�����ıߣ�����Ϊlog��n��)���������帴�Ӷ�ΪO��mlog��m����
				}
			}
		}

		return dist[end] == INT_MAX / 2 ? -1 : dist[end];
	}
	
}


//���ڸ�Ȩ������£����б������Ƶ����·��ֻ����bf
//�������spfa������Ҫ����bf
//Ҫ�󸺻�������������·���м��ɣ������Ƹ���ѭ������
namespace bellman_ford
{
	struct Edge
	{
		int a, b, w;
	};

	int BellmanFord(vector<vector<int>> edges, int n, int start, int end, int k) //��һ�������൱��vector<Edge>�� �������ܳ���k
	{
		vector<int> dist(n, INT_MAX / 2);
		vector<int> backup(n);
		dist[start] = 0;
		
		for (int i = 0; i < k; ++i)
		{
			backup.assign(dist.begin(), dist.end()); //��Ϊ�����������Ƶģ�ÿ�α���ǰ����һ�£���ֹ���������õ��α����е�ǰ���ֵ���º����ֵ��
			for (int j = 0; j < edges.size(); ++j) //��������n�����бߣ����Ը��Ӷ�Ϊn*m
			{
				int a = edges[j][0];
				int b = edges[j][1];
				int w = edges[j][2];
				dist[b] = min(dist[b], backup[a] + w); //�˴���backup�������
			}
		}
		
		return dist[end] > INT_MAX / 4 ? -1 : dist[end]; //��Ϊ���ڸ�Ȩ�ߣ����Բ�����INT_MAX / 2
	}
}

//ԭʼ��spfa�㷨Ҫ��ͼ��һ�������ڸ�������Ϊ������ڸ��������������Ϊ�գ�
namespace spfa
{
	typedef pair<int, int> Edge;

	int Spfa(vector<vector<int>>& edges, int n, int start, int end)
	{
		vector<vector<Edge>> g(n);	//�ڽӱ�
		for (const auto& e : edges)
		{
			g[e[0]].emplace_back(e[2], e[1]);	
		}

		vector<int> dist(n, INT_MAX / 2);
		vector<bool> st(n);  //����ǵ�ǰ���Ƿ��ڶ��е��У���ֹ�����д洢�ظ��ĵ�

		queue<int> q;
		q.push(start);
		st[start] = true;

		while (!q.empty())
		{
			int t = q.front();
			q.pop();
			st[t] = false;

			for (const auto& e : g[t]) //���������ٱ�
			{
				int b = e.second, w = e.first;
				if (dist[b] > dist[t] + w) //��dist[a]��Сʱdist[b]�Ż��С������ֻ�ѱ�С����ļ������
				{
					dist[b] = dist[t] + w;
					if (!st[b])
					{
						q.push(b);
						st[b] = true;
					}
				}
			}
		}

		return dist[end] == INT_MAX / 2 ? -1 : dist[end];
	}

	bool SpfaNegativeLoop(vector<vector<int>>& edges, int n)
	{
		vector<vector<Edge>> g(n);
		for (const auto& e : edges)
		{
			g[e[0]].emplace_back(e[2], e[1]);
			
		}

		vector<int> dist(n); //��Ϊ���ж���û�и����������ʼ��Ϊ����ֵ
		vector<bool> st(n);
		vector<int> cnt(n);

		queue<int> q;
		for (int i = 0; i < n; ++i) //���ֻ����һ���㣬����©�иõ㵽���˵ĸ���
		{
			st[i] = true;
			q.push(i);
		}
	
		while (!q.empty())
		{
			int t = q.front();
			q.pop();
			st[t] = false;

			for (const auto& e : g[t])
			{
				int b = e.second, w = e.first;
				if (dist[b] > dist[t] + w)
				{
					dist[b] = dist[t] + w;
					cnt[b] = cnt[t] + 1; //����

					if (cnt[b] > n)
						return true;

					if (!st[b])
					{
						q.push(b);
						st[b] = true;
					}
				}
			}
		}

		return false;
	}

}