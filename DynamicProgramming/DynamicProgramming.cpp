#include "DynamicProgramming.h"
#include <iostream>
#include <vector>
#include <queue>

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
		arr_map[x - 1][y - 1] = -1;
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

//ByteDance 3/28 2
//题目描述
//有家自助寿司店, 把每道寿司放在传送带上送给客人选择, 但是有一个规矩,
//就是不外允许拿相邻的寿司。假如为了吃得更值, 就要拿总价最高的寿司。
//比如价格为[9, 1, 2, 4]的寿司, 拿第1道和笔4道总价最高。求出能拿到的寿司总值的最大值
//输入描述
//[1, 2, 3, 1]
//数据量范围在1~200之间
//输出描述
//求出能拿到的寿司总价值的最大值
//4
void MaxSushiTotalPrice()
{
	vector<int> prices;
	int input;
	while (cin >> input)
	{
		prices.push_back(input);
	}

	int len = prices.size();
	int ans = 0;

	if (len <= 3)
	{
		if (len == 0)
		{
			ans = 0;
		}
		else if (len == 1)
		{
			ans = prices[0];
		}
		else if (len == 2)
		{
			ans = (prices[0] > prices[1]) ? prices[0] : prices[1];
		}
		else if (len == 3)
		{
			ans = (prices[0] + prices[2] > prices[1]) ? prices[0] + prices[2] : prices[1];
		}

	}
	else {
		prices[2] += prices[0];
		for (int i = 3; i < prices.size(); ++i)
		{
			prices[i] += prices[i - 2] > prices[i - 3] ? prices[i - 2] : prices[i - 3];
		}

		ans = prices[len - 1] > prices[len - 2] ? prices[len - 1] : prices[len - 2];
	}

	cout << ans;
	return;
}

//Tencent 4/5 5

/*input 
1
5 6
1 2 3 4 12
*/
void Weights()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, m;
		cin >> n;
		cin >> m;
		vector<int> weights;
		int sum = 0;
		for (int i = 0; i < n; ++i)
		{
			int temp;
			cin >> temp;
			weights.push_back(temp);
			sum += temp;
		}


		vector<int> f(sum + 1, INT_MAX);
		f[0] = 0;
		for (int i = n - 1; i >= 0; --i)
		{
			//for (int j = sum; j >= weights[i]; --j)
			for (int j = weights[i]; j < sum; ++j)
			{
				if (f[j - weights[i]] != INT_MAX)
					f[j] = min(f[j - weights[i]] + 1, f[j]);
			}
		}

		int res = INT_MAX;
		for (int i = m; i <= sum; i = i + m)
		{
			res = min(res, f[i]);
		}

		cout << (res == INT_MAX ? -1 : res);
	}
}


//Netease 4/4
void ChangeMoneyWays()
{
	int n;
	cin >> n;
	int money;
	cin >> money;
	vector<int> arr;
	for(int i=0; i<n; ++i)
	{
		int temp;
		cin>>temp;
		arr.push_back(temp);
	}

	vector<int> f(money + 1);
	f[0] = 1;
	for (int i = 0; i < n; ++i)
	{
		for (int j = arr[i]; j <= money; ++j)
		{
			f[j] = (f[j] + f[j - arr[i]])% 1000000007;
		}
	}
	cout << f[money] << endl;
}










