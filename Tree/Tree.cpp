#include "Tree.h"

#include "queue"



void TreeNode::DeleteChildTree(TreeNode* root)
{
	if (root == nullptr)
		return;
	if (root->left)
		DeleteChildTree(root->left);
	if (root->right)
		DeleteChildTree(root->right);

	delete root;
	root = nullptr;
	return;
}

TreeNode* TreeNode::CreateTree(const vector<int>& nodes)
{
	if (nodes.size() == 0 || nodes[0] == -1)
		return nullptr;
	TreeNode* root = new TreeNode(nodes[0]);
	int index = 0;
	queue<TreeNode*> q;
	q.push(root);
	while (index < nodes.size())
	{
		TreeNode* node = q.front();
		q.pop();
		if (node)
		{
			if (++index > nodes.size()-1)
				break;
			if (nodes[index]!= -1)
			{
				
				node->left = new TreeNode(nodes[index]);
				q.push(node->left);
			}
			else
			{
				q.push(nullptr);
			}

			if (++index > nodes.size() - 1)
				break;
			if (nodes[index] != -1)
			{
				node->right = new TreeNode(nodes[index]);
				q.push(node->right);
			}
			else
				q.push(nullptr);
		}
		else
		{
			if (++index > nodes.size() - 1)
				break;
			q.push(nullptr);
			if (++index > nodes.size() - 1)
				break;
			q.push(nullptr);
		}
	}

	return root;
}

void TreeNode::LevelOrderPrint(TreeNode* root)
{
	if (!root)
		return;

	queue<TreeNode*> q;
	q.push(root);
	cout << root->val<<' ';
	while (!q.empty())
	{
		int currentLevelSize = q.size();
		for (int i = 1; i <= currentLevelSize; ++i)
		{
			auto node = q.front();
			q.pop();
			if (node->left)
			{
				q.push(node->left);
				cout << node->left->val << ' ';
			}
			else
			{
				cout << "-1" << ' ';
			}

			if (node->right)
			{
				q.push(node->right);
				cout << node->right->val << ' ';
			}
			else
			{
				cout << "-1" << ' ';
			}
		}
	}
	cout << endl;
}

void TreeNode::LevelOrderTraverse(TreeNode* root)
{
	if (!root)
		return;
	queue<TreeNode*> q;

	q.push(root);
	

	while (!q.empty())
	{
		auto node = q.front();
		cout << node->val << " ";
		q.pop();
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
	}

	cout<<endl;
}




void ConvertToCompleteBinaryTree(TreeNode* root)
{
	if (!root)
		return;

	queue<TreeNode*> q;
	q.push(root);
	
	while (!q.empty())
	{
		//int curLevelSize = q.size();
		//bool bFindEmpty = false;
		//for (int i = 0; i < curLevelSize; ++i)
		//{
		//	auto node = q.front();
		//	q.pop();
		//	if (node->left)
		//		q.push(node->left);
		//	else
		//		bFindEmpty = true;
		//}

		bool bFindEmpty = false;

		auto node = q.front();
		q.pop();
		if (!bFindEmpty)
		{
			if (node->left && node->right)
			{
				q.push(node->left);
				q.push(node->right);
			}
			else
			{
				bFindEmpty = true;
				if (node->left == nullptr)
				{
					if (node->right) 
					{
						TreeNode::DeleteChildTree(node->right);
						node->right = nullptr;
					}
				}
				else if (node->right == nullptr)
				{
					if (node->left)
						q.push(node->left);
				}
			}
		}
		else
		{
			if (node->left)
			{
				TreeNode::DeleteChildTree(node->left);
				node->right = nullptr;
			}
			if (node->right)
			{
				TreeNode::DeleteChildTree(node->right);
				node->right = nullptr;
			}
		}
	}
}

