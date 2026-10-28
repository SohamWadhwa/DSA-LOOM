// Merge k Sorted Lists | Brute force: scan every current list head
// See ../README.md for reasoning, complexity, and ownership.
#include <vector>
using namespace std;

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (true) {
            int best = -1;
            for (int i = 0; i < static_cast<int>(lists.size()); ++i)
                if (lists[i] && (best == -1 || lists[i]->val < lists[best]->val)) best = i;
            if (best == -1) break;
            ListNode* node = lists[best];
            lists[best] = node->next;
            tail->next = node;
            tail = node;
        }
        tail->next = nullptr;
        return dummy.next;
    }
};
