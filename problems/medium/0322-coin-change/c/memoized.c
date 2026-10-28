// Coin Change | Better: memoize each remaining amount
// See ../README.md for reasoning, complexity, and ownership.
#include <stdlib.h>

static int solve(int* coins, int count, int remaining, int infinity, int* memo) {
    if (memo[remaining] != -2) return memo[remaining];
    int best = infinity;
    for (int i = 0; i < count; ++i) {
        if (coins[i] > remaining) continue;
        int candidate = solve(coins, count, remaining - coins[i], infinity, memo);
        if (candidate + 1 < best) best = candidate + 1;
    }
    return memo[remaining] = best;
}

int coinChange(int* coins, int coinsSize, int amount) {
    int* memo = malloc(((size_t)amount + 1) * sizeof(*memo));
    for (int i = 0; i <= amount; ++i) memo[i] = -2;
    memo[0] = 0;
    int answer = solve(coins, coinsSize, amount, amount + 1, memo);
    free(memo);
    return answer > amount ? -1 : answer;
}
