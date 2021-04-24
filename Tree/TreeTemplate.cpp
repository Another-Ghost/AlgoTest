#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N = 10010;


int son[N][26], idx; //����ֵ��Ĭ�ϳ�ʼ��Ϊ0
int cnt[N]; //�ж��ٸ��Ըýڵ��β�ĵ��ʣ�ͬһ���ʣ�
//vector<vector<int>> cnt(N); //���������仯

void insert(const string& str)
{
	int p = 0;
	for (int i = 0; str[i]; ++i)
	{
		int u = str[i] - 'a';
		if (!son[p][u])
			son[p][u] = ++idx;
		p = son[p][u];	//pָ����һ����ĸ
	}
	++cnt[p];
}

int find(const string& str) 
{
	int p = 0;
	for (int i = 0; str[i]; ++i)
	{
		int u = str[i] - 'a';
		if (!son[p][u])
			return 0;
		p = son[p][u];
	}
	return cnt[p];
}



