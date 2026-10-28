// Coin Change | Better: memoize each remaining amount
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
    int solve(vector<int>& coins, int remaining, int infinity, vector<int>& memo) {
        if (memo[remaining] != -2) return memo[remaining];
        int best = infinity;
        for (int coin : coins)
            if (coin <= remaining)
                best = min(best, 1 + solve(coins, remaining - coin, infinity, memo));
        return memo[remaining] = best;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount + 1, -2);
        memo[0] = 0;
        int answer = solve(coins, amount, amount + 1, memo);
        return answer > amount ? -1 : answer;
    }
};
