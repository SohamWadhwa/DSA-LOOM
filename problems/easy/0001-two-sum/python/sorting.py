# Two Sum | Better: sort indexed values and use two pointers
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        pairs = sorted((value, index) for index, value in enumerate(nums))
        left, right = 0, len(pairs) - 1
        while left < right:
            total = pairs[left][0] + pairs[right][0]
            if total == target:
                return [pairs[left][1], pairs[right][1]]
            if total < target:
                left += 1
            else:
                right -= 1
        return []
