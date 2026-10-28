# Valid Parentheses | Optimal: stack of unmatched openings
# See ../README.md for reasoning and complexity.
class Solution:
    def isValid(self, s: str) -> bool:
        opening_for = {')': '(', ']': '[', '}': '{'}
        stack = []
        for char in s:
            if char in '([{':
                stack.append(char)
            elif not stack or stack.pop() != opening_for[char]:
                return False
        return not stack
