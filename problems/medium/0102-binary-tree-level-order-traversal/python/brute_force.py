# Binary Tree Level Order Traversal | Baseline: repeat traversal for every depth
# See ../README.md for reasoning and complexity.
from __future__ import annotations
from typing import List, Optional

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        def height(node):
            return 0 if node is None else 1 + max(height(node.left), height(node.right))

        def collect(node, depth, row):
            if node is None:
                return
            if depth == 0:
                row.append(node.val)
                return
            collect(node.left, depth - 1, row)
            collect(node.right, depth - 1, row)

        result = []
        for depth in range(height(root)):
            row = []
            collect(root, depth, row)
            result.append(row)
        return result
