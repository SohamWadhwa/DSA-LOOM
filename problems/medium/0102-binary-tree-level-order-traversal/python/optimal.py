# Binary Tree Level Order Traversal | Optimal: breadth-first traversal with a queue
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from collections import deque
from typing import List, Optional

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root is None:
            return []
        pending = deque([root])
        result = []
        while pending:
            row = []
            for _ in range(len(pending)):  # Freeze this level's size.
                node = pending.popleft()
                row.append(node.val)
                if node.left:
                    pending.append(node.left)
                if node.right:
                    pending.append(node.right)
            result.append(row)
        return result
