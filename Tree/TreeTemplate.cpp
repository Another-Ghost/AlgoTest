#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int N = 10010;


int son[N][26], idx; //堆中值会默认初始化为0
int cnt[N]; //有多少个以该节点结尾的单词（同一单词）
//vector<vector<int>> cnt(N); //需根据问题变化

void insert(const string& str)
{
	int p = 0;
	for (int i = 0; str[i]; ++i)
	{
		int u = str[i] - 'a';
		if (!son[p][u])
			son[p][u] = ++idx;
		p = son[p][u];	//p指向下一个字母
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



