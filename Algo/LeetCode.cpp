#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {

	bool b_valid = false;
	int m, n;
	int dirs[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

	void DFS(const vector<vector<char>>& board, const string& word, vector<vector<bool>>& st, int y, int x, int pos)
	{
		if (pos == word.size() - 1)
		{
			b_valid = true; //是否可以改成函数返回值来返回结果    
		}


		for (int i = 0; i < 4; ++i)
		{
			int new_y = y + dirs[i][0];
			int new_x = x + dirs[i][1];
			if (!b_valid)
			{
				if (new_y >= 0 && new_y < m && new_x >= 0 && new_x < n && !st[new_y][new_x])
				{
					if (board[new_y][new_x] == word[pos + 1])
					{
						st[new_y][new_x] == true;
						//cout << word[pos + 1] << endl;
						DFS(board, word, st, new_y, new_x, pos + 1);
						st[new_y][new_x] = false;
					}
				}
			}
		}

	}

public:
	bool exist(vector<vector<char>>& board, string word) {
		m = board.size();
		n = board[0].size();

		vector<vector<bool>> st(m, vector<bool>(n));

		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (!b_valid)
				{
					if (board[i][j] == word[0])
					{
						st[i][j] = true;
						DFS(board, word, st, i, j, 0);
						st[i][j] = false;
					}
				}
			}
		}

		return b_valid;
	}
};

#ifdef LC



int main()
{
	Solution sol;

	vector<vector<char>> board = {{'A', 'B', 'C', 'E'},{'S', 'F', 'C', 'S'},{'A', 'D', 'E', 'E'}};
	
	string s = "ABCD";
	cout << sol.exist(board, s);

	return 0;
}

#endif