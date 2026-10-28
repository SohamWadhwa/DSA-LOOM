// Two Sum | Better: sort indexed values and use two pointers
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i)
            pairs.push_back({nums[i], i});
        sort(pairs.begin(), pairs.end());
        int left = 0, right = static_cast<int>(pairs.size()) - 1;
        while (left < right) {
            long long sum = static_cast<long long>(pairs[left].first) + pairs[right].first;
            if (sum == target) return {pairs[left].second, pairs[right].second};
            if (sum < target) ++left;
            else --right;
        }
        return {};
    }
};
