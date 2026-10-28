# Merge k Sorted Lists | Optimal time: min-heap of current heads
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from heapq import heappop, heappush
from itertools import count
from typing import List, Optional

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        serial = count()  # Break ties without comparing ListNode objects.
        heap = []
        for node in lists:
            if node is not None:
                heappush(heap, (node.val, next(serial), node))
        dummy = ListNode(0)
        tail = dummy
        while heap:
            _, _, node = heappop(heap)
            if node.next is not None:
                heappush(heap, (node.next.val, next(serial), node.next))
            tail.next = node
            tail = node
        tail.next = None
        return dummy.next
