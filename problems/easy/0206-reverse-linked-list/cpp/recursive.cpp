// Reverse Linked List | Alternative: recursive rewiring
// See ../README.md for reasoning, complexity, and ownership.
// LeetCode supplies ListNode.
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* reversed = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return reversed;
    }
};
