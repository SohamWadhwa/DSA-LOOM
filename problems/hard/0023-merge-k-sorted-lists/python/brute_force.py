# Merge k Sorted Lists | Brute force: scan every current list head
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from typing import List, Optional

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        dummy = ListNode(0)
        tail = dummy
        while True:
            best = -1
            for i, node in enumerate(lists):
                if node is not None and (best == -1 or node.val < lists[best].val):
                    best = i
            if best == -1:
                break
            node = lists[best]
            lists[best] = node.next
            tail.next = node
            tail = node
        tail.next = None
        return dummy.next
