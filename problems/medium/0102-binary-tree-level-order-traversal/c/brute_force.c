// Binary Tree Level Order Traversal | Baseline: repeat traversal for every depth
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>
// LeetCode supplies struct TreeNode.

static int height(struct TreeNode* root) {
    if (!root) return 0;
    int left = height(root->left), right = height(root->right);
    return 1 + (left > right ? left : right);
}
static int countAt(struct TreeNode* root, int depth) {
    if (!root) return 0;
    if (depth == 0) return 1;
    return countAt(root->left, depth - 1) + countAt(root->right, depth - 1);
}
static void collect(struct TreeNode* root, int depth, int* row, int* used) {
    if (!root) return;
    if (depth == 0) { row[(*used)++] = root->val; return; }
    collect(root->left, depth - 1, row, used);
    collect(root->right, depth - 1, row, used);
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int levels = height(root);
    *returnSize = levels;
    *returnColumnSizes = NULL;
    if (!levels) return NULL;
    int** result = malloc((size_t)levels * sizeof(*result));
    *returnColumnSizes = malloc((size_t)levels * sizeof(**returnColumnSizes));
    for (int depth = 0; depth < levels; ++depth) {
        int width = countAt(root, depth), used = 0;
        (*returnColumnSizes)[depth] = width;
        result[depth] = malloc((size_t)width * sizeof(**result));
        collect(root, depth, result[depth], &used);
    }
    return result; // Caller frees every row, result, and column sizes.
}
