// Coin Change | Optimal practical DP: bottom-up tabulation
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int value = 1; value <= amount; ++value)
            for (int coin : coins)
                if (coin <= value) dp[value] = min(dp[value], 1 + dp[value - coin]);
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
