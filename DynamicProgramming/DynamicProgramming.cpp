#include <iostream>
#include <vector>

using namespace std;

void NumberOfPaths()
{
	int M, N;
	cin >> M;
	cin >> N;
	int S;
	cin >> S;

	vector<vector<int>> arr_map(M, vector<int>(N)); //remember


	for (int i = 0; i < S; ++i)
	{
		int x, y;
		cin >> x;
		cin >> y;
		arr_map[x-1][y-1] = -1;
	}

	for (int i = 0; i < arr_map.size(); ++i)
		arr_map[i][0] = 1;
	for (int i = 0; i < arr_map[0].size(); ++i)
		arr_map[0][i] = 1;

	for (int i = 1; i < arr_map.size(); ++i)
	{
		for (int j = 1; j < arr_map[0].size(); ++j)
		{
			if (arr_map[i][j] != -1)
			{
				arr_map[i][j] += (arr_map[i - 1][j] == -1) ? 0 : arr_map[i-1][j];
				arr_map[i][j] += (arr_map[i][j - 1] == -1) ? 0 : arr_map[i][j - 1];
			}
		}
	}

	cout << arr_map[N - 1][M - 1];
}


int main()
{
	NumberOfPaths();
}


