# Trapping Rain Water | Better: precompute prefix and suffix maxima
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def trap(self, height: List[int]) -> int:
        if not height:
            return 0
        left, right = height.copy(), height.copy()
        for i in range(1, len(height)):
            left[i] = max(left[i - 1], height[i])
        for i in range(len(height) - 2, -1, -1):
            right[i] = max(right[i + 1], height[i])
        return sum(min(left[i], right[i]) - height[i] for i in range(len(height)))
