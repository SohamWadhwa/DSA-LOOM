// Two Sum | Optimal expected time: one-pass hash map
// See ../README.md for reasoning, complexity, and ownership.
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            auto found = seen.find(target - nums[i]);
            if (found != seen.end()) return {found->second, i};
            seen[nums[i]] = i;
        }
        return {};
    }
};
