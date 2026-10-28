// Coin Change | Brute force: enumerate coin choices recursively
// See ../README.md for reasoning, complexity, and ownership.
static int solve(int* coins, int count, int remaining, int infinity) {
    if (remaining == 0) return 0;
    int best = infinity;
    for (int i = 0; i < count; ++i) {
        if (coins[i] > remaining) continue;
        int candidate = solve(coins, count, remaining - coins[i], infinity);
        if (candidate + 1 < best) best = candidate + 1;
    }
    return best;
}

int coinChange(int* coins, int coinsSize, int amount) {
    int answer = solve(coins, coinsSize, amount, amount + 1);
    return answer > amount ? -1 : answer;
}
