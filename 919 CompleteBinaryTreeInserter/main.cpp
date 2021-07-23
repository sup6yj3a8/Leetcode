//
//  main.cpp
//  919 CompleteBinaryTreeInserter
//
//  Created by Aaron on 2021/7/12.
//

#include <iostream>
#include <queue>
using namespace std;

// Definition for a binary tree node.
typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
} TreeNode;


class CBTInserter {
public:
    TreeNode* root;
    
    CBTInserter(TreeNode* root): root(root) {}
    
    int insert(int v) {
        if (root == nullptr) {
            root = new TreeNode(v);
            return -1;
        }else{
            TreeNode* curr = root;
            return insertToBT(curr, v);
        }
    }
    
    int insertToBT(TreeNode* root, int val){
        queue<TreeNode*> q;
        q.push(root);
        
        // BFS (Breath first search) travel
        while (!q.empty()) {
            int size = static_cast<int>(q.size());
            while (size--) {
                // 1. Get the front element from queue.
                TreeNode* temp = q.front();
                q.pop();
                
                // 2. Check if the left node of temp is nullptr.
                if (temp->left != nullptr) {
                    q.push(temp->left);
                }else{
                    temp->left = new TreeNode(val);
                    return temp->val;
                }
                
                // 3. Check if the right node of temp is nullptr.
                if (temp->right != nullptr) {
                    q.push(temp->right);
                }else{
                    temp->right = new TreeNode(val);
                    return temp->val;
                }
            }
        }
        
        delete root;
        root = nullptr;
        return -1;
    }
    
    TreeNode* get_root() {return root;}
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
