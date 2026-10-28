// Reverse Linked List | Optimal auxiliary space: iterative rewiring
// See ../README.md for reasoning, complexity, and ownership.
// LeetCode supplies ListNode.
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* previous = nullptr;
        while (head) {
            ListNode* following = head->next;
            head->next = previous;
            previous = head;
            head = following;
        }
        return previous;
    }
};
