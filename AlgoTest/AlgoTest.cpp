#include <iostream>
#include <vector>
#include <algorithm>
#include "Math.h"
#include "Sort.h"

using namespace std;


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

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	int total = nums1.size() + nums2.size();
	int a = 0, b = 0;
	int mid = 0;
	for (int i = 0; i < total; ++i)
	{
		int n1 = a < nums1.size() ? nums1[a] : INT_MAX;
		int n2 = b < nums2.size() ? nums2[b] : INT_MAX;
		int n3;
		if (n1 <= n2)
		{
			n3 = n1;
			++a;
		}
		else
		{
			n3 = n2;
			++b;
		}
		if (total % 2 == 1) {
			if (i == total / 2)
			{
				return n3;
			}
		}
		else if (total % 2 == 0)
		{
			if (i == total / 2 - 1)
			{
				mid += n3;
			}
			else if (i == total / 2)
			{
				return (mid + n3) * 1.0 / 2;
			}
		}

	}
	return 0.0;
}


int main()
{
	//vector<int> times{ 0, 1, 4, 2, 1, 3, 6 };
	////sort(times.begin(), times.end());

	//QuickSort(times, 0, times.size() - 1);
	vector<int> nums1 = { 1, 2 };
	vector<int> nums2 = { 3, 4 };
	cout << findMedianSortedArrays(nums1, nums2);

	//int ans = numIlands(grid);
	//cout << ans;
	return 0;
}

