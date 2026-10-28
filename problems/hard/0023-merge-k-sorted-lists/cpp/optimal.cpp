// Merge k Sorted Lists | Optimal time with constant workspace: bottom-up pairwise merging
// See ../README.md for reasoning, complexity, and ownership.
#include <vector>
using namespace std;

class Solution {
    ListNode* merge(ListNode* a, ListNode* b) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (a && b) {
            if (a->val <= b->val) { tail->next = a; a = a->next; }
            else { tail->next = b; b = b->next; }
            tail = tail->next;
        }
        tail->next = a ? a : b;
        return dummy.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int k = static_cast<int>(lists.size());
        if (k == 0) return nullptr;
        for (int width = 1; width < k; width *= 2)
            for (int i = 0; i + width < k; i += 2 * width)
                lists[i] = merge(lists[i], lists[i + width]);
        return lists[0];
    }
};
