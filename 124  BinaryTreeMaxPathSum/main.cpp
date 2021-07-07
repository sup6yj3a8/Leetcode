//
//  main.cpp
//  124  BinaryTreeMaxPathSum
//
//  Created by Aaron on 2021/7/6.
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

int MIN = -1001;

int maxDFS(TreeNode* root, int &max){
    if (root == nullptr) {
        return 0;
    }else{
        // if subtree is negtive, discard it
        int left = std::max(0, maxDFS(root->left, max));
        int right = std::max(0, maxDFS(root->right, max));
        
        // max records max value
        max = std::max(max, left + root->val + right);
        return std::max(left, right) + root->val; // return the max value of one side
    }
}

int maxPathSum(TreeNode* root) {
    int max = MIN;
    maxDFS(root, max);
    return max;
}

int main(int argc, const char * argv[]) {
    return 0;
}
