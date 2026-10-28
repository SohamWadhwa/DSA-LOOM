// Binary Search | Baseline: linear search
// See ../README.md for reasoning, complexity, and ownership.
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        for (int i = 0; i < static_cast<int>(nums.size()); ++i)
            if (nums[i] == target) return i;
        return -1;
    }
};
