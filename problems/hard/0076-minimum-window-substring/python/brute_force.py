# Minimum Window Substring | Brute force: recount every candidate substring
# See ../README.md for reasoning and complexity.
from collections import Counter

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if not t or len(s) < len(t):
            return ''
        need = Counter(t)
        best_start, best_length = 0, len(s) + 1
        for left in range(len(s)):
            for right in range(left, len(s)):
                have = Counter(s[left:right + 1])
                if all(have[ch] >= count for ch, count in need.items()):
                    if right - left + 1 < best_length:
                        best_start, best_length = left, right - left + 1
        return '' if best_length > len(s) else s[best_start:best_start + best_length]
