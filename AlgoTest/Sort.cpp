#include "Sort.h"
#include <iostream>

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

//Quick Sort
int partition(vector<int>& arr, int left, int right)
{
	int pivot = left;
	int index = pivot + 1;
	for (int i = index; i <= right; i++)
	{
		if (arr[i] < arr[pivot])
		{
			swap(arr[i], arr[index]);
			index++;
		}
	}
	swap(arr[pivot], arr[index - 1]);

	return index - 1;
	//int pivot = v[up];
	//int i = low - 1;
	//for (int j = low; j < up; j++)
	//{
	//	if (v[j] <= pivot)
	//	{
	//		i++;
	//		swap(v[i], v[j]);
	//	}
	//}
}

void QuickSort1(vector<int>& arr, int left, int right)
{
	if (left < right)
	{
		int partitionIndex = partition(arr, left, right);
		QuickSort1(arr, left, partitionIndex - 1);
		QuickSort1(arr, partitionIndex + 1, right);
	}
}

void QuickSortTest()
{
	vector<int> arr{ 3,1,4,3,5 };

	QuickSort1(arr, 0, arr.size() - 1);

	for (auto i : arr)
	{
		cout << i << " ";
	}
	cout << endl;
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

//二分法另一种模板
int BinarySearch_Simple(const vector<int>& nums, int target)
{
	int l = 0, r = nums.size() - 1;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (nums[mid] == target)
			return mid;
		if (nums[mid] > target)
			r = mid - 1;
		else
			l = mid + 1;
	}

	return -1;
}

