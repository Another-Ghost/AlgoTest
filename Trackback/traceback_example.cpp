#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int n;

vector<vector<int>> grid(3, vector<int>(3));

vector<vector<int>> st(3, vector<int>(3));

vector<bool> used;

vector<pair<int, int>> spaces;

bool RowFull(int i)
{
	if (grid[i][0] > 0 && grid[i][1] > 0 && grid[i][2] > 0)
	{
		return true;
	}
	return false;
}

bool ColFull(int j)
{
	if (grid[0][j] > 0 && grid[1][j] > 0 && grid[2][j] > 0)
	{
		return true;
	}
	return false;
}

bool RowSum(int i)
{
	int sum = 0;
	for (int j = 0; j < n; ++j)
	{
		if (st[i][j])
			sum += grid[i][j];
	}
	return sum;
}

bool ColSum(int j)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		if (st[i][j])
			sum += grid[i][j];
	}
	return sum;
}

bool RowValid(int i)
{
	if (grid[i][0] + grid[i][1] + grid[i][2] == 15)
	{
		return true;
	}
	return false;
}



bool ColValid(int j)
{
	if (grid[0][j] + grid[1][j] + grid[2][j] == 15)
	{
		return true;
	}
	return false;
}

bool IsValid()
{
	for (int i = 0; i < n; ++i)
	{
		if (RowFull(i))
		{
			if (!RowValid(i))
			{
				return false;
			}
		}
		if (ColFull(i))
		{
			if (!ColValid(i))
			{
				return false;
			}
		}
	}
	return true;
}

bool IsFinished()
{

}


int RowFilledCount(int i)
{
	int ret = 0;
	for (int j = 0; j < n; ++j)
	{
		if (grid[i][j])
		{
			++ret;
		}
	}
	return ret;
}

int ColFilledCount(int j)
{
	int ret = 0;
	for (int i = 0; i < n; ++i)
	{
		if (grid[i][j])
		{
			++ret;
		}
	}
	return ret;
}


bool bValid = false;

void DFS(int idx)
{
	if (idx == spaces.size())
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << grid[i][j] << " ";
			}
			cout << endl;
		}
		bValid = true;
		return;
	}

	int i = spaces[idx].first;
	int j = spaces[idx].second;

	if (!grid[i][j] && !bValid)
	{
		int row_sum = RowSum(i);
		int col_sum = ColSum(j);
		if (RowFilledCount(i) == n - 1)
		{
			if (row_sum > 5)
			{
				if (used[15 - row_sum] == false)
				{
					if (ColFilledCount(j) == n - 1 && col_sum == row_sum)
					{
						grid[i][j] = 15 - row_sum;
						used[15 - row_sum] = true;
						DFS(idx + 1);
					}
					else if (ColFilledCount(j) < n - 1)
					{
						if (15 - row_sum + col_sum < 15)
						{
							grid[i][j] = 15 - row_sum;
							used[15 - row_sum] = true;
							DFS(idx + 1);
						}
					}
				}
			}
		}
		else if (RowFilledCount(i) < n - 1)
		{
			if (ColFilledCount(j) == n - 1)
			{
				if (15 - col_sum + row_sum < 15 && col_sum > 5)
				{
					grid[i][j] = 15 - col_sum;
					used[15 - col_sum] = true;
					DFS(idx + 1);
				}
			}
			else if (ColFilledCount(j) < n - 1)
			{
				for (int i = 1; i < used.size(); ++i)
				{
					if (used[i] == false && col_sum + i < 15 && row_sum + i < 15)
					{
						grid[i][j] = i;
						used[i] = true;
						DFS(idx + 1);
					}
				}
			}
		}

	}
}

int main()
{
	n = 3;

	used.resize(n + 1);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> grid[i][j];
			if (grid[i][j] != 0)
			{
				st[i][j] = 2;
				used[grid[i][j]] = true;
			}
			else
			{
				spaces.emplace_back(i, j);
			}


		}
	}
	if (!IsValid())
		cout << "not found result.";

	//for (int i = 0; i < n; ++i)
	//{
	//	for (int j = 0; j < n; ++j)
	//	{
	//		
	//	}
	//}
	DFS(0);
}