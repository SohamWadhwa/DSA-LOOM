# Minimum Window Substring | Better: reuse counts while extending each start position
# See ../README.md for reasoning and complexity.
from collections import Counter

class Solution:
    def minWindow(self, s: str, t: str) -> str:
        if not t or len(s) < len(t):
            return ''
        need = Counter(t)
        best_start, best_length = 0, len(s) + 1
        for left in range(len(s)):
            have, missing = Counter(), len(t)
            for right in range(left, len(s)):
                char = s[right]
                if have[char] < need[char]:
                    missing -= 1
                have[char] += 1
                if missing == 0:
                    if right - left + 1 < best_length:
                        best_start, best_length = left, right - left + 1
                    break
        return '' if best_length > len(s) else s[best_start:best_start + best_length]
