#include <iostream>
#include <vector>

using namespace std;

//3/28 ByteDance 4
//��Ŀ����
//С��������һ��nm�ĵ�ͼ, ÿ��ֻ�ܴ�(x, y)->(x, y + 1)����(x, y)->(x + 1y), �����
//(1, 1)�ߵ�(n, m)���ж����ֲ�ͬ��·��, ��������С������̫����, Ȼ��С����
//�������ͼ�Ϸ���q���ϰ���, �����ͱ���˴�1�ߵ�(n, m)���Ҳ�����q���ϰ�
//����ж����ֲ�ͬ��·����
//��������
//��һ����������n, m, q�ֱ��ʾ��ͼ�Ĵ�С���ϰ������
//������q��ÿ������������x, y��ʾ�ϰ��������
//�������
//һ��������ʾ�ж����ֲ�ͬ��·��, ������ܴܺ��1e9 + 7ȡģ

void NumberOfPaths()
{
	int M, N; //�����С
	cin >> M; 
	cin >> N;
	int S; //�ϰ���
	cin >> S;

	vector<vector<int>> arr_map(M, vector<int>(N)); //remember



	for (int i = 0; i < S; ++i)
	{
		int x, y; //ÿһ���ϰ�������
		cin >> x;
		cin >> y;
		arr_map[x-1][y-1] = -1;
	}


	for (int i = 0; i < arr_map.size(); ++i)
		if (arr_map[i][0] != -1)
			arr_map[i][0] = 1;
		else
			break; //��Ϊ�˴�Ϊ�ϰ�����һ��ʣ�µĵ��߲�ͨ
	for (int i = 0; i < arr_map[0].size(); ++i)
		if (arr_map[0][i] != -1)
			arr_map[0][i] = 1;
		else
			break;

	for (int i = 1; i < M; ++i)
	{
		for (int j = 1; j < N; ++j)
		{
			if (arr_map[i][j] != -1)
			{
				arr_map[i][j] += (arr_map[i - 1][j] == -1) ? 0 : arr_map[i - 1][j];
				arr_map[i][j] += (arr_map[i][j - 1] == -1) ? 0 : arr_map[i][j - 1];
			}
		}
	}
	int ans = (arr_map[N - 1][M - 1] > 0) ? arr_map[N - 1][M - 1] : 0;
	cout << ans;

	//Notice: �迼�������յ�Ϊ�ϰ�������
}


int main()
{
	NumberOfPaths();
}


