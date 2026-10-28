# Reverse Linked List | Alternative: recursive rewiring
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from typing import Optional

class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head is None or head.next is None:
            return head
        reversed_head = self.reverseList(head.next)
        head.next.next = head
        head.next = None
        return reversed_head
