# Coin Change | Optimal practical DP: bottom-up tabulation
# See ../README.md for reasoning and complexity.
from typing import List

class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        dp = [amount + 1] * (amount + 1)
        dp[0] = 0
        for value in range(1, amount + 1):
            for coin in coins:
                if coin <= value:
                    dp[value] = min(dp[value], 1 + dp[value - coin])
        return -1 if dp[amount] > amount else dp[amount]
