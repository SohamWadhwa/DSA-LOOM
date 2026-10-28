// Reverse Linked List | Baseline: store node pointers and relink
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>
// LeetCode supplies struct ListNode { int val; struct ListNode* next; }.

struct ListNode* reverseList(struct ListNode* head) {
    int count = 0;
    for (struct ListNode* node = head; node; node = node->next) ++count;
    if (count == 0) return NULL;
    struct ListNode** nodes = malloc((size_t)count * sizeof(*nodes));
    int i = 0;
    for (struct ListNode* node = head; node; node = node->next) nodes[i++] = node;
    for (i = count - 1; i > 0; --i) nodes[i]->next = nodes[i - 1];
    nodes[0]->next = NULL;
    head = nodes[count - 1];
    free(nodes); // Nodes themselves belong to the caller.
    return head;
}
