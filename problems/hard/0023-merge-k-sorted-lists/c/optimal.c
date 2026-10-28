// Merge k Sorted Lists | Optimal time with constant workspace: bottom-up pairwise merging
// See ../README.md for reasoning, complexity, and ownership.
#include <stddef.h>
// LeetCode supplies struct ListNode. Mutates the input head-pointer array.

static struct ListNode* merge(struct ListNode* a, struct ListNode* b) {
    struct ListNode dummy = {0, NULL};
    struct ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (!listsSize) return NULL;
    for (int width = 1; width < listsSize; width *= 2)
        for (int i = 0; i + width < listsSize; i += 2 * width)
            lists[i] = merge(lists[i], lists[i + width]);
    return lists[0];
}
