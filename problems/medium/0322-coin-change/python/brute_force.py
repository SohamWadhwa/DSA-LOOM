# Coin Change | Brute force: enumerate coin choices recursively
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        infinity = amount + 1

        def solve(remaining):
            if remaining == 0:
                return 0
            best = infinity
            for coin in coins:
                if coin <= remaining:
                    best = min(best, 1 + solve(remaining - coin))
            return best

        answer = solve(amount)
        return -1 if answer > amount else answer
