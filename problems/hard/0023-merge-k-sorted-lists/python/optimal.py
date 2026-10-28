# Merge k Sorted Lists | Optimal time with constant workspace: bottom-up pairwise merging
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from typing import List, Optional

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        def merge(a, b):
            dummy = ListNode(0)
            tail = dummy
            while a is not None and b is not None:
                if a.val <= b.val:
                    tail.next, a = a, a.next
                else:
                    tail.next, b = b, b.next
                tail = tail.next
            tail.next = a if a is not None else b
            return dummy.next

        width = 1
        while width < len(lists):
            for i in range(0, len(lists) - width, 2 * width):
                lists[i] = merge(lists[i], lists[i + width])
            width *= 2
        return lists[0] if lists else None
