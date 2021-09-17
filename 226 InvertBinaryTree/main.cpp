//
//  main.cpp
//  226 InvertBinaryTree
//
//  Created by Aaron on 2021/9/17.
//

#include <iostream>
#include <algorithm>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// DFS
void DFS_Invert(TreeNode* root) {
    if (root != nullptr) {
        DFS_Invert(root->left);
        DFS_Invert(root->right);
        swap(root->left, root->right);
    }
}

TreeNode* invertTree(TreeNode* root) {
    DFS_Invert(root);
    return root;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
