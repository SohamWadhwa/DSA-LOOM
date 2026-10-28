// Trapping Rain Water | Better: precompute prefix and suffix maxima
// See ../README.md for reasoning, complexity, and ownership.
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int n = static_cast<int>(height.size());
        if (!n) return 0;
        vector<int> left(n), right(n);
        left[0] = height[0];
        for (int i = 1; i < n; ++i) left[i] = max(left[i - 1], height[i]);
        right[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) right[i] = max(right[i + 1], height[i]);
        int total = 0;
        for (int i = 0; i < n; ++i) total += min(left[i], right[i]) - height[i];
        return total;
    }
};
