# Trapping Rain Water | Brute force: scan left and right boundaries for every bar
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def trap(self, height: List[int]) -> int:
        total = 0
        for i in range(len(height)):
            left = right = height[i]
            for j in range(i):
                left = max(left, height[j])
            for j in range(i + 1, len(height)):
                right = max(right, height[j])
            total += min(left, right) - height[i]
        return total
