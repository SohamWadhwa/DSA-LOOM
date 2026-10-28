# Largest Rectangle in Histogram | Better: maintain the interval minimum as it grows
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        best = 0
        for left in range(len(heights)):
            minimum = heights[left]
            for right in range(left, len(heights)):
                minimum = min(minimum, heights[right])
                best = max(best, minimum * (right - left + 1))
        return best
