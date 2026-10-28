# Subsets | Enumeration: interpret a bitmask as a subset
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        result = []
        for mask in range(1 << len(nums)):
            result.append([nums[bit] for bit in range(len(nums)) if mask & (1 << bit)])
        return result
