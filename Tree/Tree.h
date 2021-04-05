#pragma once
#include <iostream>
#include <vector>

using namespace std;
//Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

	static void DeleteChildTree(TreeNode* root);

	static TreeNode* CreateTree(const vector<int>& nodes);

	static void LevelOrderPrint(TreeNode* root);

	static void LevelOrderTraverse(TreeNode* root);
};

void ConvertToCompleteBinaryTree(TreeNode* root);

