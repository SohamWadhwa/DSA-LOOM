# Subsets | Output-optimal alternative: backtracking
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        result, path = [], []

        def visit(start):
            result.append(path.copy())
            for index in range(start, len(nums)):
                path.append(nums[index])
                visit(index + 1)
                path.pop()

        visit(0)
        return result
