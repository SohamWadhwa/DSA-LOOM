# Binary Search | Baseline: linear search
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        for index, value in enumerate(nums):
            if value == target:
                return index
        return -1
