// Reverse Linked List | Alternative: recursive rewiring
// See ../README.md for reasoning, complexity, and ownership.
#include <stddef.h>
// LeetCode supplies struct ListNode.

struct ListNode* reverseList(struct ListNode* head) {
    if (!head || !head->next) return head;
    struct ListNode* reversed = reverseList(head->next);
    head->next->next = head;
    head->next = NULL; // Break the old forward link to avoid a cycle.
    return reversed;
}
