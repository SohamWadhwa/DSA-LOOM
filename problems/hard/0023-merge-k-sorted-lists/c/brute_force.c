// Merge k Sorted Lists | Brute force: scan every current list head
// See ../README.md for reasoning, complexity, and ownership.
#include <stddef.h>
// LeetCode supplies struct ListNode. Reuses nodes and advances the lists array.

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode dummy = {0, NULL};
    struct ListNode* tail = &dummy;
    while (1) {
        int best = -1;
        for (int i = 0; i < listsSize; ++i)
            if (lists[i] && (best == -1 || lists[i]->val < lists[best]->val)) best = i;
        if (best == -1) break;
        struct ListNode* node = lists[best];
        lists[best] = node->next;
        tail->next = node;
        tail = node;
    }
    tail->next = NULL;
    return dummy.next;
}
