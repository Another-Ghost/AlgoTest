#include "DynamicProgramming.h"
#include <iostream>
#include <vector>
#include <queue>

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
		arr_map[x - 1][y - 1] = -1;
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

//ByteDance 3/28 2
//��Ŀ����
//�м�������˾��, ��ÿ����˾���ڴ��ʹ����͸�����ѡ��, ������һ�����,
//���ǲ������������ڵ���˾������Ϊ�˳Եø�ֵ, ��Ҫ���ܼ���ߵ���˾��
//����۸�Ϊ[9, 1, 2, 4]����˾, �õ�1���ͱ�4���ܼ���ߡ�������õ�����˾��ֵ�����ֵ
//��������
//[1, 2, 3, 1]
//��������Χ��1~200֮��
//�������
//������õ�����˾�ܼ�ֵ�����ֵ
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

//Tencent 4/18 5/5


/*
2 2 6
1 1 
1 1

2 2 5
1 1
1 1
*/

//ͼ�Ĺ����������������� 
//״̬���У�������ģ� 


void WhacAMole()
{
	int n, m, t;
	cin >> n >> m >> t;

	vector<vector<int>> mp(n, (vector<int>)(m));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> mp[i][j];
		}
	}

	int ans = 0;

	queue<State> q;
	//��������ÿ�α����ƶ�һ���Ҳ���ԭ·���أ�����Ĭ��mp��С������2 x 2
	//��Ĭ������ڣ�0��0���������Ȱѣ�0,1������1,0�����
	q.push(State(1, 1, 0, eNorth, (1 % mp[1][0] == 0)));
	q.push(State(1, 0, 1, eEast, (1 % mp[0][1] == 0)));
	while (!q.empty())
	{
		State cur = q.front();
		q.pop();
		
		if (cur.i == n - 1 && cur.j == m - 1 && cur.t == t)	//Ĭ���յ�λ���ǣ�n-1, m -1), �ұ���tʱ�������ߵ��յ�ſ���
		{
			ans = max(ans, cur.score);
		}
		
		int t_new = cur.t + 1;
		if (t_new > t)
			continue;

		if (cur.i > 0 && cur.from != eNorth)	//�Ƿ��������
		{
			int i_new = cur.i - 1;
			int j_new = cur.j;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)	//�����ǰλ����ʣ��ʱ���ڵ��ﲻ���յ����Թ�	
			{
				q.push(State(t_new, i_new, j_new, eSouth, cur.score + (t_new % mp[i_new][j_new] == 0))); //t_new % mp[i_new][j_new]Ϊ0˵������ǰλ�ü�ʱ�ѵ�
			}
		}

		if (cur.i < n - 1 && cur.from != eSouth)
		{
			int i_new = cur.i + 1;
			int j_new = cur.j;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)
			{
				q.push(State(t_new, i_new, j_new, eNorth, cur.score + (t_new % mp[i_new][j_new] == 0)));
			}
		}

		if (cur.j > 0 && cur.from != eEast)
		{
			int i_new = cur.i;
			int j_new = cur.j - 1;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)
			{
				q.push(State(t_new, i_new, j_new, eWest, cur.score + (t_new % mp[i_new][j_new] == 0)));
			}
		}

		if (cur.j < m -1 && cur.from != eWest)
		{
			int i_new = cur.i;
			int j_new = cur.j + 1;
			if (n - 1 - i_new + m - 1 - j_new <= t - cur.t)
			{
				q.push(State(t_new, i_new, j_new, eEast, cur.score + (t_new % mp[i_new][j_new] == 0)));
			}
		}
	}
	
	cout << ans << endl;
}

