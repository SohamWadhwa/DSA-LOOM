# Largest Rectangle in Histogram | Brute force: recompute the minimum in every interval
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        best = 0
        for left in range(len(heights)):
            for right in range(left, len(heights)):
                minimum = min(heights[left:right + 1])
                best = max(best, minimum * (right - left + 1))
        return best
