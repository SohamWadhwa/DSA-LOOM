// Reverse Linked List | Baseline: store node pointers and relink
// See ../README.md for reasoning, complexity, and ownership.
#include <vector>
using namespace std;
// LeetCode supplies ListNode.

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        vector<ListNode*> nodes;
        for (ListNode* node = head; node; node = node->next) nodes.push_back(node);
        if (nodes.empty()) return nullptr;
        for (int i = static_cast<int>(nodes.size()) - 1; i > 0; --i)
            nodes[i]->next = nodes[i - 1];
        nodes.front()->next = nullptr;
        return nodes.back();
    }
};
