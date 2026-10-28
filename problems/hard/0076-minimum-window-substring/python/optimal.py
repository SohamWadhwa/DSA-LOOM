# Minimum Window Substring | Optimal: expand and shrink a sliding window
# See ../README.md for reasoning and complexity.
from collections import Counter

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if not t or len(s) < len(t):
            return ''
        balance = Counter(t)
        missing, left = len(t), 0
        best_start, best_length = 0, len(s) + 1
        for right, char in enumerate(s):
            if balance[char] > 0:
                missing -= 1
            balance[char] -= 1
            while missing == 0:
                if right - left + 1 < best_length:
                    best_start, best_length = left, right - left + 1
                removed = s[left]
                balance[removed] += 1
                left += 1
                if balance[removed] > 0:
                    missing += 1
        return '' if best_length > len(s) else s[best_start:best_start + best_length]
