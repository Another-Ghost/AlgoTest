#pragma once
#include <string>

using namespace std;

//����Ѱַ��
//����ĳ���Ҫ������Ŀ���ݷ�Χ��2~3��
//����cheshuoһ���ĵ����׿ӷ�
//ɾ����������ͨ���ҵ�֮���һ�������ʵ��
namespace OpenAddressing
{
	const int N = 20003, null = 0x3f3f3f3f;
	int h[N];

	void Insert(int x)
	{
		int k = Search(x);
		h[k] = x;
	}


	int Search(int x)	//���x�ڹ�ϣ���д��ڵĻ��ͷ���x����λ�ã����򷵻���Ӧ�ô洢��λ��
	{
		int k = (x % N + N) % N;
		while (h[k] != null && h[k]!= x)
		{
			k++;
			if (k == N)
				k = 0;
		}
		return k;
	}

	bool Find(int x)
	{
		int k = Search(x);
		if (h[k] != null)
			return true;
		else
			return false;
	}

	void Init()
	{
		memset(h, -1, sizeof h);
	}
}


//������
const int N = 10003; //������Զ��2�Ľ׳�

int h[N], val[N], ne[N], idx;

//x�ķ�ΧΪ-10e9 ~ 10e9
void Insert(int x)
{
	int k = (x % N + N) % N; //�������������
	//C++�︺��ģ��һ�����Ǹ���������ѧ�ж��岻ͬ

	val[idx] = x, ne[idx] = h[k], h[k] = idx++;	//���µ��nextָ��ָ��h[k]�����ָ��, h[k]�ĸ��³ɵ�ǰ���ָ�루ͷ�巨��
	
}

bool Find(int x)
{
	int k = (x % N + N) % N;
	for (int i = h[k]; i != -1; i = ne[i])
	{
		if (val[i] == x)
			return true;
	}

	return false;
}

void Init()
{
	memset(h, -1, sizeof h);//��ָ����-1����ʾ
}


int lengthOfLongestSubstring(string s);
