#include <iostream>
#include <vector>
#include <algorithm>
#include "Math.h"


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

void QuickSort(vector<int>& arr, int left, int right)
{
	if (left < right)
	{
		int partitionIndex = partition(arr, left, right);
		QuickSort(arr, left, partitionIndex - 1);
		QuickSort(arr, partitionIndex + 1, right);
	}
}

void QuickSortTest()
{
	vector<int> arr{ 3,1,4,3,5 };

	QuickSort(arr, 0, arr.size() - 1);

	for (auto i : arr)
	{
		cout << i << " ";
	}
	cout << endl;
}



int main()
{
	vector<int> times{ 0, 1, 4, 2, 1, 3, 6 };
	sort(times.begin(), times.end());

	for (auto t : times)
	{
		cout << t << endl;
	}

	return 0;
}

