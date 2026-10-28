// Binary Tree Level Order Traversal | Baseline: repeat traversal for every depth
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;
// LeetCode supplies TreeNode.

class Solution {
    int height(TreeNode* root) {
        return root ? 1 + max(height(root->left), height(root->right)) : 0;
    }
    void collect(TreeNode* root, int depth, vector<int>& row) {
        if (!root) return;
        if (depth == 0) { row.push_back(root->val); return; }
        collect(root->left, depth - 1, row);
        collect(root->right, depth - 1, row);
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        int levels = height(root);
        for (int depth = 0; depth < levels; ++depth) {
            result.push_back({});
            collect(root, depth, result.back());
        }
        return result;
    }
};
