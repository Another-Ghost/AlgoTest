#include "Sort.h"

void QuickSort(vector<int>& nums, int l, int r)
{
	if (l >= r)
		return;
	int i = l - 1;
	int j = r + 1;
	int x = nums[l + r >> 1];
	while (i < j)
	{
		do 
		{
			++i;
		} while (nums[i] < x);
		do 
		{
			--j;
		} while (nums[j] > x);
		if(i < j)
			swap(nums[i], nums[j]);
	}

	QuickSort(nums, l, j);
	QuickSort(nums, j + 1, r);
}

void MergeSort(vector<int>& q, int l, int r)
{
	if (l >= r)
		return;
	int mid = l + r >> 1;
	MergeSort(q, l, mid);
	MergeSort(q, mid + 1, r);
	vector<int> tmp;
	int i = l, j = mid + 1;
	while (i <= mid && j <= r)
	{
		if (q[i] <= q[j]) //<=可以保证稳定性
			tmp.push_back(q[i++]);
		else
			tmp.push_back(q[j++]);
	}
	while (i <= mid)
		tmp.push_back(q[i++]);
	while(j <= r)
		tmp.push_back(q[j++]);

	for (int i = l, j = 0; i <= r ; ++i, ++j)
		q[i] = tmp[j];
}
