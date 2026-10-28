// Binary Tree Level Order Traversal | Optimal: breadth-first traversal with a queue
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>
// LeetCode supplies struct TreeNode.

typedef struct {
    struct TreeNode** data;
    int head, size, capacity;
} Queue;
static void push(Queue* q, struct TreeNode* node) {
    if (q->size == q->capacity) {
        int capacity = q->capacity ? q->capacity * 2 : 8;
        struct TreeNode** grown = malloc((size_t)capacity * sizeof(*grown));
        for (int i = 0; i < q->size; ++i)
            grown[i] = q->data[(q->head + i) % q->capacity];
        free(q->data);
        q->data = grown;
        q->head = 0;
        q->capacity = capacity;
    }
    q->data[(q->head + q->size) % q->capacity] = node;
    ++q->size;
}
static struct TreeNode* pop(Queue* q) {
    struct TreeNode* node = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    --q->size;
    return node;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (!root) return NULL;
    int capacity = 8;
    int** result = malloc((size_t)capacity * sizeof(*result));
    *returnColumnSizes = malloc((size_t)capacity * sizeof(**returnColumnSizes));
    Queue queue = {0};
    push(&queue, root);
    while (queue.size) {
        int level = *returnSize, width = queue.size;
        if (level == capacity) {
            capacity *= 2;
            result = realloc(result, (size_t)capacity * sizeof(*result));
            *returnColumnSizes = realloc(*returnColumnSizes,
                (size_t)capacity * sizeof(**returnColumnSizes));
        }
        result[level] = malloc((size_t)width * sizeof(**result));
        (*returnColumnSizes)[level] = width;
        for (int i = 0; i < width; ++i) {
            struct TreeNode* node = pop(&queue);
            result[level][i] = node->val;
            if (node->left) push(&queue, node->left);
            if (node->right) push(&queue, node->right);
        }
        ++*returnSize;
    }
    free(queue.data);
    return result;
}
