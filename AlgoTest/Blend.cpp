#include "Blend.h"
#include <iostream>
#include <vector>

using namespace std;


//优先队列？
void AdSending()
{
	int n, k;
	cin >> n >> k;

	vector<int> users;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		users.push_back(tmp);
	}

	vector<int> counts = users;

	int num_sent = 0;

	for (int i = 0; num_sent < k; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			--counts[j];
			if (counts[j] == 0)
			{
				cout << j + 1 << endl;
				counts[j] = users[j];
				++num_sent;
			}
		}
	}
}

void AdSending2()
{
	int n, k;
	cin >> n >> k;

	vector<int> users;
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		users.push_back(tmp);
	}

	//vector<int> counts = users;

	int num_sent = 0;
	int count = 0;
	for (int i = 0; num_sent < k; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			++count;
			if (count % users[j] == 0)
			{
				cout << j + 1 << endl;
				++num_sent;
			}
		}
	}
}