#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N = 10010;


//int son[N][26], idx;
//int cnt[N]; //�ж��ٸ��Ըýڵ��β�ĵ��ʣ�ͬһ���ʣ�
////vector<vector<int>> cnt(N);
//
//void insert(const string& str)
//{
//	int p = 0;
//	for (int i = 0; str[i]; ++i)
//	{
//		int u = str[i] - 'a';
//		if (!son[p][u])
//			son[p][u] = ++idx;
//		p = son[p][u];	//pָ����һ����ĸ
//	}
//	++cnt[p];
//}
//
//int find(const string& str) 
//{
//	int p = 0;
//	for (int i = 0; str[i]; ++i)
//	{
//		int u = str[i] - 'a';
//		if (!son[p][u])
//			return 0;
//		p = son[p][u];
//	}
//	return cnt[p];
//}

int son[N][26], cnt[N], idx;

void Insert(const string& str)
{
	int p = 0;
	for (int i = 0; str[i]; ++i)
	{
		int ch = str[i] - 'a';
		if (!son[p][ch])
			son[p][ch] = idx++;
		p = son[p][ch];
	}
	++cnt[p];
}

int Find(const string& str)
{
	int p = 0;
	for (int i = 0; str[i]; ++i)
	{
		int ch = str[i] - 'a';
		if (!son[p][ch])
			son[p][ch] = idx++;
		p = son[p][ch];
	}
	return cnt[p];
}

