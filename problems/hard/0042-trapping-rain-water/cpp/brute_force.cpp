// Trapping Rain Water | Brute force: scan left and right boundaries for every bar
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = static_cast<int>(height.size()), total = 0;
        for (int i = 0; i < n; ++i) {
            int left = height[i], right = height[i];
            for (int j = 0; j < i; ++j) left = max(left, height[j]);
            for (int j = i + 1; j < n; ++j) right = max(right, height[j]);
            total += min(left, right) - height[i];
        }
        return total;
    }
};
