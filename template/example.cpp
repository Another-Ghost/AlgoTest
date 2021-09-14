#include <iostream>
#include <vector>

using namespace std;

template<class T, int row_num, int col_num>
class TMatrix
{

public:
	int num_r;
	int num_c;

	TMatrix()
	{
		num_r = row_num;
		num_c = col_num;
		mat.resize(row_num);
		for (int i = 0; i < col_num; ++i)
		{
			mat[i].resize(col_num);
		}
	}

	TMatrix(const vector<int>& nums)
	{
		if (nums.size() != row_num * col_num)
		{
			cout << "Matrix init error" << endl;
			return;
		}
		for (int i = 0; i < row_num; ++i)
		{
			for (int j = 0; j < col_num; ++j)
			{
				mat[i][j] = nums[i * col_num + j];
			}
		}
	}

	TMatrix<T, row_num, col_num> operator + (const TMatrix<T, row_num, col_num>& b)
	{
		TMatrix<T, row_num, col_num> ret;
		for (int i = 0; i < row_num; ++i)
		{
			for (int j = 0; j < col_num; ++j)
			{
				ret[i][j] = mat[i][j] + b.mat[i][j];
			}
		}
		return ret;
	}

	template<int b_col_num>
	friend TMatrix<T, row_num, b_col_num> operator * (const TMatrix<T, row_num, col_num>& a, const TMatrix<T, row_num, b_col_num>& b) const
	{
		TMatrix<T, row_num, b_col_num> ret;
		for (int i = 0; i < row_num; ++i)
		{
			for (int j = 0; j < b_col_num; ++j)
			{
				for (int d = 0; d < col_num; ++i)
				{
					ret[i][j] += a.mat[i][d] * b.mat[d][j];
				}
			}
		}
		return ret;
	}

	vector<vector<int>> mat;
};

int main()
{
	vector<int> nums_a(6);
	vector<int> nums_b(8);
	for (int i = 0; i < nums_a.size(); ++i)
	{
		cin >> nums_a[i];
	}
	for (int i = 0; i < nums_b.size(); ++i)
	{
		cin >> nums_b[i];
	}
	TMatrix<int, 2, 3> mat_a(nums_a);
	TMatrix<int, 3, 4> mat_b(nums_b);

	auto c = mat_a * mat_b;
}