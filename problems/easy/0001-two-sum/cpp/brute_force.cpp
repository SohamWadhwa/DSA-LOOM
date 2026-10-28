// Two Sum | Brute force: enumerate pairs
// See ../README.md for reasoning, complexity, and ownership.
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            for (int j = i + 1; j < static_cast<int>(nums.size()); ++j) {
                if (static_cast<long long>(nums[i]) + nums[j] == target)
                    return {i, j};
            }
        }
        return {};
    }
};
