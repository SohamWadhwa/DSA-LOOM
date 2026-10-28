# Largest Rectangle in Histogram | Optimal: increasing stack of bar indices
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        stack, best = [], 0
        for i in range(len(heights) + 1):
            current = heights[i] if i < len(heights) else 0
            while stack and heights[stack[-1]] > current:
                height = heights[stack.pop()]
                left = stack[-1] if stack else -1
                best = max(best, height * (i - left - 1))
            if i < len(heights):
                stack.append(i)
        return best
