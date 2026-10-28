# Reverse Linked List | Baseline: store node pointers and relink
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from typing import Optional
# LeetCode supplies ListNode.

class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        nodes = []
        while head:
            nodes.append(head)
            head = head.next
        if not nodes:
            return None
        for i in range(len(nodes) - 1, 0, -1):
            nodes[i].next = nodes[i - 1]
        nodes[0].next = None
        return nodes[-1]
