# Valid Parentheses | Brute force: repeated pair removal
# See ../README.md for reasoning and complexity.
class Solution:
    def isValid(self, s: str) -> bool:
        while s:
            for i in range(len(s) - 1):
                if s[i:i + 2] in ("()", "[]", "{}"):
                    s = s[:i] + s[i + 2:]
                    break
            else:
                return False
        return True
