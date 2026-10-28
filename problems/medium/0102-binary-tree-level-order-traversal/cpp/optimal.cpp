// Binary Tree Level Order Traversal | Optimal: breadth-first traversal with a queue
// See ../README.md for reasoning, complexity, and ownership.
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        queue<TreeNode*> pending;
        pending.push(root);
        vector<vector<int>> result;
        while (!pending.empty()) {
            int width = static_cast<int>(pending.size());
            vector<int> row;
            row.reserve(width);
            for (int i = 0; i < width; ++i) {
                TreeNode* node = pending.front();
                pending.pop();
                row.push_back(node->val);
                if (node->left) pending.push(node->left);
                if (node->right) pending.push(node->right);
            }
            result.push_back(move(row));
        }
        return result;
    }
};
