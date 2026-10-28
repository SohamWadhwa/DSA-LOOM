// Reverse Linked List | Optimal auxiliary space: iterative rewiring
// See ../README.md for reasoning, complexity, and ownership.
#include <stddef.h>
// LeetCode supplies struct ListNode.

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* previous = NULL;
    while (head) {
        struct ListNode* following = head->next; // Save before overwriting.
        head->next = previous;
        previous = head;
        head = following;
    }
    return previous;
}
