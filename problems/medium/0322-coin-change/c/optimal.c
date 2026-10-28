// Coin Change | Optimal practical DP: bottom-up tabulation
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>

int coinChange(int* coins, int coinsSize, int amount) {
    int* dp = malloc(((size_t)amount + 1) * sizeof(*dp));
    dp[0] = 0;
    for (int value = 1; value <= amount; ++value) {
        dp[value] = amount + 1;
        for (int i = 0; i < coinsSize; ++i) {
            if (coins[i] <= value && dp[value - coins[i]] + 1 < dp[value])
                dp[value] = dp[value - coins[i]] + 1;
        }
    }
    int answer = dp[amount] > amount ? -1 : dp[amount];
    free(dp);
    return answer;
}
