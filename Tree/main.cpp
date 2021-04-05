#include <iostream>
#include "Tree.h"

int main()
{
    vector<int> nodes = { 1, 2, 3, 4, 5,  -1, 7 };
    TreeNode* root = TreeNode::CreateTree(nodes);

    TreeNode::LevelOrderPrint(root);

    ConvertToCompleteBinaryTree(root);

    TreeNode::LevelOrderPrint(root);

    TreeNode::LevelOrderTraverse(root);
}


