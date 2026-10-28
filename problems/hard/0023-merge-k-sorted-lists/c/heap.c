// Merge k Sorted Lists | Optimal time: min-heap of current heads
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>
// LeetCode supplies struct ListNode.

static void push(struct ListNode** heap, int* size, struct ListNode* node) {
    int i = (*size)++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent]->val <= node->val) break;
        heap[i] = heap[parent];
        i = parent;
    }
    heap[i] = node;
}
static struct ListNode* pop(struct ListNode** heap, int* size) {
    struct ListNode* result = heap[0];
    struct ListNode* last = heap[--*size];
    int i = 0;
    while (2 * i + 1 < *size) {
        int child = 2 * i + 1;
        if (child + 1 < *size && heap[child + 1]->val < heap[child]->val) ++child;
        if (last->val <= heap[child]->val) break;
        heap[i] = heap[child];
        i = child;
    }
    if (*size) heap[i] = last;
    return result;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode** heap = malloc((size_t)(listsSize ? listsSize : 1) * sizeof(*heap));
    int size = 0;
    for (int i = 0; i < listsSize; ++i) if (lists[i]) push(heap, &size, lists[i]);
    struct ListNode dummy = {0, NULL};
    struct ListNode* tail = &dummy;
    while (size) {
        struct ListNode* node = pop(heap, &size);
        if (node->next) push(heap, &size, node->next);
        tail->next = node;
        tail = node;
    }
    tail->next = NULL;
    free(heap);
    return dummy.next;
}
