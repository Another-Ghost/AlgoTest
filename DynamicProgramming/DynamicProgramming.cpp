#include <iostream>
#include <vector>

using namespace std;

//3/28 ByteDance 4
//题目描述
//小超桌上有一个nm的地图, 每次只能从(x, y)->(x, y + 1)或者(x, y)->(x + 1y), 如果从
//(1, 1)走到(n, m)会有多少种不同的路径, 可能这样小超觉得太简单了, 然后小超想
//在这个地图上放置q个障碍点, 这样就变成了从1走到(n, m)并且不经过q个障碍
//点会有多少种不同的路径。
//输入描述
//第一行三个整数n, m, q分别表示地图的大小和障碍点个数
//接下来q行每行两个正整数x, y表示障碍点的坐标
//输出描述
//一个整数表示有多少种不同的路径, 结果可能很大对1e9 + 7取模

void NumberOfPaths()
{
	int M, N; //数组大小
	cin >> M; 
	cin >> N;
	int S; //障碍数
	cin >> S;

	vector<vector<int>> arr_map(M, vector<int>(N)); //remember



	for (int i = 0; i < S; ++i)
	{
		int x, y; //每一个障碍的坐标
		cin >> x;
		cin >> y;
		arr_map[x-1][y-1] = -1;
	}


	for (int i = 0; i < arr_map.size(); ++i)
		if (arr_map[i][0] != -1)
			arr_map[i][0] = 1;
		else
			break; //因为此处为障碍，第一列剩下的点走不通
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

	//Notice: 需考虑起点和终点为障碍物的情况
}


int main()
{
	NumberOfPaths();
}


