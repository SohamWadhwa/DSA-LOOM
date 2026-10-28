// Subsets | Enumeration: interpret a bitmask as a subset
// See ../README.md for reasoning, complexity, and ownership.
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        int n = static_cast<int>(nums.size());
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<int> subset;
            for (int bit = 0; bit < n; ++bit)
                if (mask & (1 << bit)) subset.push_back(nums[bit]);
            result.push_back(move(subset));
        }
        return result;
    }
};
