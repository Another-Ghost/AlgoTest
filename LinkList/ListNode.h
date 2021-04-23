#pragma once
#include <vector>

using namespace std;

struct ListNode {
	int val;
	struct ListNode* next;

};

//Tencent 4/18 1/5
ListNode* MinimalList(ListNode* S);

//leetcode 23
ListNode* mergeKLists(vector<ListNode*>& lists);