# Reverse Linked List | Optimal auxiliary space: iterative rewiring
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from typing import Optional

class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        previous = None
        while head:
            following = head.next
            head.next = previous
            previous = head
            head = following
        return previous
