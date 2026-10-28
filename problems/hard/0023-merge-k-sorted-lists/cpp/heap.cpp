// Merge k Sorted Lists | Optimal time: min-heap of current heads
// See ../README.md for reasoning, complexity, and ownership.
#include <queue>
#include <vector>
using namespace std;

class Solution {
    struct Greater {
        bool operator()(ListNode* a, ListNode* b) const { return a->val > b->val; }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Greater> heap;
        for (ListNode* node : lists) if (node) heap.push(node);
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (!heap.empty()) {
            ListNode* node = heap.top();
            heap.pop();
            if (node->next) heap.push(node->next);
            tail->next = node;
            tail = node;
        }
        tail->next = nullptr;
        return dummy.next;
    }
};
