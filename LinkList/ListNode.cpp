#include "ListNode.h"
#include <vector>
#include <queue>
using namespace std;




vector<int> Sequence(const vector<int>& l, int s)
{
	int n = l.size();
	vector<int> seq;
	for (int i = s; i < n; ++i)
	{
		seq.push_back(l[i]);
	}
	for (int i = 0; i < n - s; ++i)
	{
		seq.push_back(l[i]);
	}
	return seq;
}

bool ASmallerThanB(vector<int>& a, vector<int> b)
{
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] < b[i])
			return true;
		else if (a[i] > b[i])
			return false;
	}
	return false;
}

ListNode* MinimalList(ListNode* S) {
	// write code here
	int num_min = INT_MAX;
	vector<int> l;

	ListNode* head = S;

	while (S != nullptr)
	{
		l.push_back(S->val);
		if (S->val < num_min)
		{
			num_min = S->val;
		}
		S = S->next;
	}

	vector<int> l_ans;
	int num = 0;
	for (int i = 0; i < l.size(); ++i)
	{
		if (l[i] == num_min)
		{
			vector<int> l_seq = Sequence(l, i);
			if (l_ans.size() == 0 || ASmallerThanB(l_seq, l_ans))
			{
				l_ans = l_seq;
				num = i;
			}
		}
	}

	for (int i = 0; i < num; ++i)
	{
		head = head->next;
	}

	return head;
}

ListNode* mergeKLists(vector<ListNode*>& lists)
{
	ListNode* head = new ListNode();
	ListNode* tail = head;
	auto cmp = [](ListNode* a, ListNode* b) {return a->val > b->val; };
	priority_queue <ListNode*, vector<ListNode*>, decltype(cmp)> heap(cmp);
	for (auto l : lists)
	{
		heap.push(l);
	}

	while (!heap.empty())
	{
		ListNode* node = heap.top();
		heap.pop();
		tail->next = node;
		if (node->next)
			heap.push(node->next);
	}

	ListNode* ans = head->next;
	delete head;
	return ans;
}
