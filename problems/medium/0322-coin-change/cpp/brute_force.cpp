// Coin Change | Brute force: enumerate coin choices recursively
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
    int solve(vector<int>& coins, int remaining, int infinity) {
        if (remaining == 0) return 0;
        int best = infinity;
        for (int coin : coins)
            if (coin <= remaining) best = min(best, 1 + solve(coins, remaining - coin, infinity));
        return best;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        int answer = solve(coins, amount, amount + 1);
        return answer > amount ? -1 : answer;
    }
};
